
#include "FBXLoader.h"

CFBXLoader::CFBXLoader() :
	m_Manager(nullptr),
	m_Scene(nullptr)
{
}

CFBXLoader::~CFBXLoader()
{
	m_Scene->Clear();
	m_Scene->Destroy();
	m_Manager->Destroy();
}

bool CFBXLoader::LoadFBX(const char* FullPath, bool Static)
{
	// FbxManager ��ü�� �����Ѵ�.
	m_Manager = FbxManager::Create();

	// IOSetting�� �����Ѵ�.
	FbxIOSettings* Ios = FbxIOSettings::Create(m_Manager, IOSROOT);

	// FbxManager�� �����Ѵ�.
	m_Manager->SetIOSettings(Ios);

	// FbxScene�� �����Ѵ�.
	m_Scene = FbxScene::Create(m_Manager, "");

	// FbxImporter �� �̿��ؼ� fbx ���Ϸκ��� �޽� ������ �о�´�.
	FbxImporter* Importer = FbxImporter::Create(m_Manager, "");

	// �ش� ��ο� �ִ� fbx ������ �о���� ������ ������.
	Importer->Initialize(FullPath, -1, m_Manager->GetIOSettings());

	// ������ ���� ������ FbxScene�� ��带 �����Ѵ�.
	Importer->Import(m_Scene);

	if (m_Scene->GetGlobalSettings().GetAxisSystem() != FbxAxisSystem::Max)
		m_Scene->GetGlobalSettings().SetAxisSystem(FbxAxisSystem::Max);

	//if (!Static)
	//{
	//	m_Scene->FillAnimStackNameArray(m_NameArr);

	//	if (m_NameArr.GetCount() > 0)
	//	{
	//		LoadAnimationClip();

	//		// �� ������ �о�´�.
	//		LoadBone(m_pScene->GetRootNode());

	//		// Ŭ���� ������ �ִ� �������� �� ������ŭ resize ���ش�.
	//		// ���� Animation Clip���� �ϴ����̴�.
	//		for (size_t i = 0; i < m_vecClip.size(); ++i)
	//		{
	//			m_vecClip[i]->vecBoneKeyFrame.resize(m_vecBones.size());
	//		}
	//	}
	//}

	Triangulate(m_Scene->GetRootNode());

	LoadMesh(m_Scene->GetRootNode(), Static);

	Importer->Destroy();

	return true;
}

void CFBXLoader::Triangulate(FbxNode* pNode)
{
	// FbxNodeAttribute : FbxNode �Ӽ��� ��Ÿ���� �������̽��̴�.
	// ���κ��� ���� �� �ִ�.
	FbxNodeAttribute* pAttr = pNode->GetNodeAttribute();

	if (pAttr && (pAttr->GetAttributeType() == FbxNodeAttribute::eMesh ||
		pAttr->GetAttributeType() == FbxNodeAttribute::eNurbs ||
		pAttr->GetAttributeType() == FbxNodeAttribute::eNurbsSurface))
	{
		FbxGeometryConverter	converter(m_Manager);

		converter.Triangulate(pAttr, true);
	}

	// ���������� �д´�.
	int	iMtrlCount = pNode->GetMaterialCount();

	if (iMtrlCount > 0)
	{
		std::vector<PFBXMATERIAL>	vecMtrl;

		m_vecMaterials.push_back(vecMtrl);

		for (int i = 0; i < iMtrlCount; ++i)
		{
			// FbxSurfaceMaterial : Fbx �� ������ �ִ� ���� ������
			// ����ִ�.
			FbxSurfaceMaterial* pMtrl = pNode->GetMaterial(i);

			if (!pMtrl)
				continue;

			LoadMaterial(pMtrl);
		}
	}

	// ���� ����� �ڽĳ�� ���� ���´�.
	int	iChildCount = pNode->GetChildCount();

	for (int i = 0; i < iChildCount; ++i)
	{
		Triangulate(pNode->GetChild(i));
	}
}

void CFBXLoader::LoadMaterial(FbxSurfaceMaterial* pMtrl)
{
	// ���� ������ ������ ����ü�� �����Ѵ�.
	PFBXMATERIAL	pMtrlInfo = new FBXMATERIAL;

	// ���� ������ �����̳ʿ� ���� ������ �߰��Ѵ�.
	m_vecMaterials[m_vecMaterials.size() - 1].push_back(pMtrlInfo);

	// Diffuse ������ �о�´�.
	pMtrlInfo->Dif = GetMaterialColor(pMtrl, FbxSurfaceMaterial::sDiffuse,
		FbxSurfaceMaterial::sDiffuseFactor);

	pMtrlInfo->Amb = GetMaterialColor(pMtrl, FbxSurfaceMaterial::sAmbient,
		FbxSurfaceMaterial::sAmbientFactor);

	pMtrlInfo->Spc = GetMaterialColor(pMtrl, FbxSurfaceMaterial::sSpecular,
		FbxSurfaceMaterial::sSpecularFactor);

	pMtrlInfo->Emv = GetMaterialColor(pMtrl, FbxSurfaceMaterial::sEmissive,
		FbxSurfaceMaterial::sEmissiveFactor);

	pMtrlInfo->SpecularPower = GetMaterialFactor(pMtrl, FbxSurfaceMaterial::sSpecularFactor);
	pMtrlInfo->Shininess = GetMaterialFactor(pMtrl, FbxSurfaceMaterial::sShininess);
	pMtrlInfo->TransparencyFactor = GetMaterialFactor(pMtrl, FbxSurfaceMaterial::sTransparencyFactor);

	pMtrlInfo->DifTex = GetMaterialTexture(pMtrl, FbxSurfaceMaterial::sDiffuse);
	pMtrlInfo->BumpTex = GetMaterialTexture(pMtrl, FbxSurfaceMaterial::sNormalMap);

	if (pMtrlInfo->BumpTex.empty())
		pMtrlInfo->BumpTex = GetMaterialTexture(pMtrl, FbxSurfaceMaterial::sBump);

	pMtrlInfo->SpcTex = GetMaterialTexture(pMtrl, FbxSurfaceMaterial::sSpecular);
}

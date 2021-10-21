
#include "Material.h"
#include "ShaderManager.h"
#include "MaterialConstantBuffer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "ResourceManager.h"
#include "../Render/RenderState.h"
#include "../Render/RenderStateManager.h"

CMaterial::CMaterial()  :
	m_bTransparency(false),
	m_pCBuffer(nullptr),
	m_pScene(nullptr),
	m_BaseColor(1.f, 1.f, 1.f, 1.f),
	m_EmissiveColor(0.f, 0.f, 0.f, 0.f),
	m_RenderState{},
	m_Opacity(1.f)
{
}

CMaterial::CMaterial(const CMaterial& material)
{
	*this = material;

	m_RefCount = 1;

	m_pCBuffer = material.m_pCBuffer->Clone();

	m_vecTexture.clear();

	size_t  Size = material.m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		MaterialTextureInfo* pInfo = new MaterialTextureInfo;

		m_vecTexture.push_back(pInfo);

		pInfo->Name = material.m_vecTexture[i]->Name;
		pInfo->Link = material.m_vecTexture[i]->Link;
		pInfo->pTexture = material.m_vecTexture[i]->pTexture;
		pInfo->Register = material.m_vecTexture[i]->Register;
		pInfo->ShaderType = material.m_vecTexture[i]->ShaderType;
	}

	m_SetMaterialList.clear();
	m_ResetMaterialList.clear();
}

CMaterial::~CMaterial()
{
	{
		auto	iter = m_SetMaterialList.begin();
		auto	iterEnd = m_SetMaterialList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE((*iter));
		}
	}

	{
		auto	iter = m_ResetMaterialList.begin();
		auto	iterEnd = m_ResetMaterialList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_DELETE((*iter));
		}
	}

	size_t  Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(m_vecTexture[i]);
	}

	SAFE_DELETE(m_pCBuffer);
}

void CMaterial::SetTransparency(bool bTransparency)
{
	m_bTransparency = bTransparency;

	if (!m_bTransparency)
		m_RenderState[RST_Blend] = nullptr;

	else
		m_RenderState[RST_Blend] = CRenderStateManager::GetInst()->FindRenderState("AlphaBlend");
}

void CMaterial::SetBaseColor(const Vector4& Color)
{
	m_BaseColor = Color;

	m_pCBuffer->SetBaseColor(m_BaseColor);
}

void CMaterial::SetBaseColor(float r, float g, float b, float a)
{
	m_BaseColor = Vector4(r, g, b, a);

	m_pCBuffer->SetBaseColor(m_BaseColor);
}

void CMaterial::SetBaseColor(unsigned char r, unsigned char g, 
	unsigned char b, unsigned char a)
{
	m_BaseColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_pCBuffer->SetBaseColor(m_BaseColor);
}

void CMaterial::SetEmissiveColor(const Vector4& Color)
{
	m_EmissiveColor = Color;

	m_pCBuffer->SetEmissiveColor(m_EmissiveColor);
}

void CMaterial::SetEmissiveColor(float r, float g, float b, float a)
{
	m_EmissiveColor = Vector4(r, g, b, a);

	m_pCBuffer->SetEmissiveColor(m_EmissiveColor);
}

void CMaterial::SetEmissiveColor(unsigned char r, unsigned char g, 
	unsigned char b, unsigned char a)
{
	m_EmissiveColor = Vector4(r / 255.f, g / 255.f, b / 255.f, a / 255.f);

	m_pCBuffer->SetEmissiveColor(m_EmissiveColor);
}

bool CMaterial::AddTexture(const std::string& Name, CTexture* Texture)
{
	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = Texture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::AddTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTexture(Name, FileName, PathName);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = pTexture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::AddTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureFullPath(Name, FullPath);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = pTexture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::AddTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTexture(Name, vecFileName, PathName);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = pTexture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::AddTextureFullPath(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureFullPath(Name, vecFullPath);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = pTexture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::AddTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureArray(Name, vecFileName, PathName);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureArray(Name, vecFileName, PathName);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = pTexture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::AddTextureArrayFullPath(const std::string& Name, const std::vector<const TCHAR*>& vecFullPath)
{
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureArrayFullPath(Name, vecFullPath);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureArrayFullPath(Name, vecFullPath);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	MaterialTextureInfo* pInfo = new MaterialTextureInfo;

	pInfo->Name = Name;
	pInfo->pTexture = pTexture;

	m_vecTexture.push_back(pInfo);

	return true;
}

bool CMaterial::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTexture(Name, FileName, PathName);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	pInfo->pTexture = pTexture;

	return true;
}

bool CMaterial::SetTexture(const std::string& Name, CTexture* Texture)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	pInfo->pTexture = Texture;

	return true;
}

bool CMaterial::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureFullPath(Name, FullPath);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, FullPath);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	pInfo->pTexture = pTexture;

	return true;
}

bool CMaterial::SetTexture(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTexture(Name, vecFileName, PathName);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, vecFileName, PathName);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	pInfo->pTexture = pTexture;

	return true;
}

bool CMaterial::SetTextureFullPath(const std::string& Name, 
	const std::vector<const TCHAR*>& vecFullPath)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureFullPath(Name, vecFullPath);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureFullPath(Name, vecFullPath);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	pInfo->pTexture = pTexture;

	return true;
}

bool CMaterial::SetTextureArray(const std::string& Name, const std::vector<const TCHAR*>& vecFileName, const std::string& PathName)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureArray(Name, vecFileName, PathName);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureArray(Name, vecFileName, PathName);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	pInfo->pTexture = pTexture;

	return true;
}

bool CMaterial::SetTextureArrayFullPath(const std::string& Name,
	const std::vector<const TCHAR*>& vecFullPath)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTextureArrayFullPath(Name, vecFullPath);

		pTexture = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTextureArrayFullPath(Name, vecFullPath);

		pTexture = CResourceManager::GetInst()->FindTexture(Name);
	}

	pInfo->pTexture = pTexture;

	return true;
}

bool CMaterial::SetTextureLink(const std::string& Name, Texture_Link Link)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	pInfo->Link = Link;

	if (Link == Texture_Link::BaseTexture)
		pInfo->Register = 0;

	else if (Link == Texture_Link::EmissiveTexture)
		pInfo->Register = 1;

	return true;
}

bool CMaterial::SetTextureRegister(const std::string& Name, int Register)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	pInfo->Register = Register;

	if (Register == 0)
		pInfo->Link = Texture_Link::BaseTexture;

	else if (Register == 1)
		pInfo->Link = Texture_Link::EmissiveTexture;

	else
		pInfo->Link = Texture_Link::CustomTexture;

	return true;
}

bool CMaterial::SetTextureShaderType(const std::string& Name, int ShaderType)
{
	MaterialTextureInfo* pInfo = nullptr;

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecTexture[i]->Name == Name)
		{
			pInfo = m_vecTexture[i];
			break;
		}
	}

	if (!pInfo)
		return false;

	pInfo->ShaderType = ShaderType;

	return true;
}

void CMaterial::PaperBurnEnable(bool Enable)
{
	m_pCBuffer->PaperBurnEnable(Enable);
}

void CMaterial::DistortionEnable(bool Enable)
{
	m_pCBuffer->DistortionEnable(Enable);
}

bool CMaterial::Init()
{
	m_pCBuffer = new CMaterialConstantBuffer;

	m_pCBuffer->Init();

	SetShader("Standard2DTextureShader");

	return true;
}

void CMaterial::SetShader(const std::string& Name)
{
	m_pShader = CShaderManager::GetInst()->FindShader(Name);
}

void CMaterial::SetMaterial()
{
	m_pCBuffer->SetBaseColor(m_BaseColor);
	m_pCBuffer->SetEmissiveColor(m_EmissiveColor);
	m_pCBuffer->SetOpacity(m_Opacity);
	
	m_pCBuffer->UpdateCBuffer();

	for (int i = 0; i < RST_End; ++i)
	{
		if (m_RenderState[i])
			m_RenderState[i]->SetState();
	}

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTexture[i]->pTexture->SetShader(m_vecTexture[i]->Register,
			m_vecTexture[i]->ShaderType);
	}

	auto	iter = m_SetMaterialList.begin();
	auto	iterEnd = m_SetMaterialList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Func();
	}

	m_pShader->SetShader();
}

void CMaterial::ResetMaterial()
{
	for (int i = 0; i < RST_End; ++i)
	{
		if (m_RenderState[i])
			m_RenderState[i]->ResetState();
	}

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTexture[i]->pTexture->ResetShader(m_vecTexture[i]->Register,
			m_vecTexture[i]->ShaderType);
	}

	auto	iter = m_ResetMaterialList.begin();
	auto	iterEnd = m_ResetMaterialList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Func();
	}
}

void CMaterial::SetMaterialEmptyShader()
{
	m_pCBuffer->SetBaseColor(m_BaseColor);
	m_pCBuffer->SetEmissiveColor(m_EmissiveColor);
	m_pCBuffer->SetOpacity(m_Opacity);
	m_pCBuffer->UpdateCBuffer();

	for (int i = 0; i < RST_End; ++i)
	{
		if (m_RenderState[i])
			m_RenderState[i]->SetState();
	}

	size_t	Size = m_vecTexture.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTexture[i]->pTexture->SetShader(m_vecTexture[i]->Register,
			m_vecTexture[i]->ShaderType);
	}

	auto	iter = m_SetMaterialList.begin();
	auto	iterEnd = m_SetMaterialList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Func();
	}

	m_pShader->SetShader();
}

void CMaterial::ResetMaterialEmptyShader()
{
	for (int i = 0; i < RST_End; ++i)
	{
		if (m_RenderState[i])
			m_RenderState[i]->ResetState();
	}

	auto	iter = m_ResetMaterialList.begin();
	auto	iterEnd = m_ResetMaterialList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Func();
	}
}

CMaterial* CMaterial::Clone()
{
	return new CMaterial(*this);
}


#include "TileMapComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/CameraManager.h"
#include "Camera.h"
#include "../Resource/StructuredBuffer.h"
#include "../Resource/Material.h"
#include "Transform.h"

CTileMapComponent::CTileMapComponent() :
	m_WorldBuffer(nullptr),
	m_CBuffer(nullptr),
	m_FrameMaxX(1),
	m_FrameMaxY(1)
{
	m_PrimitiveType = PrimitiveComponent_Type::Primitive2D;
	m_2DType = RT2D_Back;
	m_3DType = RT3D_Default;
}

CTileMapComponent::CTileMapComponent(const CTileMapComponent& com) :
	CPrimitiveComponent(com)
{
}

CTileMapComponent::~CTileMapComponent()
{
	SAFE_DELETE(m_WorldBuffer);
	SAFE_DELETE(m_CBuffer);

	auto	iter = m_vecTile.begin();
	auto	iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE((*iter));
	}

	m_vecTile.clear();
}

CMesh* CTileMapComponent::GetMesh() const
{
	return (CMesh*)m_Mesh.Get();
}

void CTileMapComponent::SetMesh(CMesh* pMesh)
{
	m_Mesh = (CSpriteMesh*)pMesh;

	Vector3 Min = m_Mesh->GetMin();
	Vector3 Max = m_Mesh->GetMax();

	m_pTransform->SetMeshSize(Max - Min);

	m_vecMaterialSlot.clear();

	const std::vector<CSharedPtr<CMaterial>>* pMaterialSlots =
		m_Mesh->GetMaterialSlots();

	auto    iter = pMaterialSlots->begin();
	auto    iterEnd = pMaterialSlots->end();

	for (; iter != iterEnd; ++iter)
	{
		CMaterial* pClone = (*iter)->Clone();

		pClone->SetScene(m_pScene);
		m_vecMaterialSlot.push_back(pClone);

		SAFE_RELEASE(pClone);
	}
}

void CTileMapComponent::SetMesh(const std::string& Name)
{
	m_Mesh = (CSpriteMesh*)m_pScene->GetResource()->FindMesh(Name);

	Vector3 Min = m_Mesh->GetMin();
	Vector3 Max = m_Mesh->GetMax();

	m_pTransform->SetMeshSize(Max - Min);

	m_vecMaterialSlot.clear();

	const std::vector<CSharedPtr<CMaterial>>* pMaterialSlots =
		m_Mesh->GetMaterialSlots();

	auto    iter = pMaterialSlots->begin();
	auto    iterEnd = pMaterialSlots->end();

	for (; iter != iterEnd; ++iter)
	{
		CMaterial* pClone = (*iter)->Clone();

		pClone->SetScene(m_pScene);
		m_vecMaterialSlot.push_back(pClone);

		SAFE_RELEASE(pClone);
	}
}

void CTileMapComponent::SetFrameMax(int x, int y)
{
	m_FrameMaxX = x;
	m_FrameMaxY = y;

	m_TileImageFrameSize.x = m_TileImageSize.x / m_FrameMaxX;
	m_TileImageFrameSize.y = m_TileImageSize.y / m_FrameMaxY;
}

void CTileMapComponent::SetTileDefaultFrame(int x, int y)
{
	auto	iter = m_vecTile.begin();
	auto	iterEnd = m_vecTile.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetFrameStart(m_TileImageFrameSize * Vector2((float)x, (float)y));
		(*iter)->SetFrameEnd(m_TileImageFrameSize * Vector2((float)(x + 1), (float)(y + 1)));
	}
}

void CTileMapComponent::SetTileFrame(int TileIndex, int x, int y)
{
	m_vecTile[TileIndex]->SetFrameStart(m_TileImageFrameSize * Vector2((float)x, (float)y));
	m_vecTile[TileIndex]->SetFrameEnd(m_TileImageFrameSize * Vector2((float)(x + 1), (float)(y + 1)));
}

void CTileMapComponent::SetMaterial(int SlotIndex, CMaterial* pMaterial)
{
	CPrimitiveComponent::SetMaterial(SlotIndex, pMaterial);

	const MaterialTextureInfo* pInfo = pMaterial->GetMaterialTextureInfo();

	if (pInfo)
	{
		m_TileImageSize.x = (float)pInfo->pTexture->GetWidth();
		m_TileImageSize.y = (float)pInfo->pTexture->GetHeight();

		m_CBuffer->SetTileImageSize(m_TileImageSize);

		m_TileImageFrameSize.x = m_TileImageSize.x / m_FrameMaxX;
		m_TileImageFrameSize.y = m_TileImageSize.y / m_FrameMaxY;
	}
}

void CTileMapComponent::SetMaterial(int SlotIndex, const std::string& Name)
{
	CPrimitiveComponent::SetMaterial(SlotIndex, Name);

	const MaterialTextureInfo* pInfo = m_vecMaterialSlot[SlotIndex]->GetMaterialTextureInfo();

	if (pInfo)
	{
		m_TileImageSize.x = (float)pInfo->pTexture->GetWidth();
		m_TileImageSize.y = (float)pInfo->pTexture->GetHeight();

		m_CBuffer->SetTileImageSize(m_TileImageSize);

		m_TileImageFrameSize.x = m_TileImageSize.x / m_FrameMaxX;
		m_TileImageFrameSize.y = m_TileImageSize.y / m_FrameMaxY;
	}
}

void CTileMapComponent::AddMaterial(CMaterial* pMaterial)
{
	CPrimitiveComponent::AddMaterial(pMaterial);

	const MaterialTextureInfo* pInfo = pMaterial->GetMaterialTextureInfo();

	if (pInfo)
	{
		m_TileImageSize.x = (float)pInfo->pTexture->GetWidth();
		m_TileImageSize.y = (float)pInfo->pTexture->GetHeight();

		m_CBuffer->SetTileImageSize(m_TileImageSize);

		m_TileImageFrameSize.x = m_TileImageSize.x / m_FrameMaxX;
		m_TileImageFrameSize.y = m_TileImageSize.y / m_FrameMaxY;
	}
}

void CTileMapComponent::AddMaterial(const std::string& Name)
{
	CPrimitiveComponent::AddMaterial(Name);

	const MaterialTextureInfo* pInfo = m_vecMaterialSlot[0]->GetMaterialTextureInfo();

	if (pInfo)
	{
		m_TileImageSize.x = (float)pInfo->pTexture->GetWidth();
		m_TileImageSize.y = (float)pInfo->pTexture->GetHeight();

		m_CBuffer->SetTileImageSize(m_TileImageSize);

		m_TileImageFrameSize.x = m_TileImageSize.x / m_FrameMaxX;
		m_TileImageFrameSize.y = m_TileImageSize.y / m_FrameMaxY;
	}
}

void CTileMapComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CTileMapComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;

	SetMesh("TextureRect");

	// 상수버퍼 생성
	m_CBuffer = new CTileMapCBuffer;

	m_CBuffer->Init();

	return true;
}

void CTileMapComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	size_t Size = m_vecTile.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->Update(DeltaTime);
	}
}

void CTileMapComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);

	Matrix	matView, matProj;
	matView = m_pScene->GetCameraManager()->GetCurrentCamera()->GetViewMatrix();
	matProj = m_pScene->GetCameraManager()->GetCurrentCamera()->GetProjMatrix();

	// 테스트로 전체 다 돌려서 출력하는 구조를 잡아본다.
	size_t Size = m_vecTile.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->PostUpdate(DeltaTime);

		m_vecTileInfo[i].FrameStart = m_vecTile[i]->GetFrameStart();
		m_vecTileInfo[i].FrameEnd = m_vecTile[i]->GetFrameEnd();
		m_vecTileInfo[i].matWVP = m_vecTile[i]->GetWorldMatrix() * matView * matProj;
		m_vecTileInfo[i].matWVP.Transpose();
	}

	m_WorldBuffer->UpdateBuffer(&m_vecTileInfo[0], sizeof(TileInfo) * (int)m_vecTileInfo.size());
}

void CTileMapComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CTileMapComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);

	m_WorldBuffer->SetShader(30, CBT_VERTEX);

	m_CBuffer->UpdateCBuffer();

	if (!m_vecMaterialSlot.empty())
		m_vecMaterialSlot[0]->SetMaterial();

	m_Mesh->RenderInstancing((unsigned int)m_vecTile.size());

	m_WorldBuffer->ResetShader(30, CBT_VERTEX);

	if (!m_vecMaterialSlot.empty())
		m_vecMaterialSlot[0]->ResetMaterial();
}

CTileMapComponent* CTileMapComponent::Clone()
{
	return new CTileMapComponent(*this);
}

void CTileMapComponent::SetWorldInfo()
{
	m_WorldBuffer = new CStructuredBuffer;

	if (!m_WorldBuffer->Init("TileMapBuffer", sizeof(TileInfo),
		(unsigned int)m_vecTile.size(), 30, true, CBT_VERTEX))
	{
		SAFE_DELETE(m_WorldBuffer);
		return;
	}
}

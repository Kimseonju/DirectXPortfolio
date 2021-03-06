
#include "RenderManager.h"
#include "../Component/PrimitiveComponent.h"
#include "RenderStateManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/CameraManager.h"
#include "../Component/Camera.h"
#include "../Device.h"
#include "RenderState.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/PostProcessCBuffer.h"
#include "../Resource/DistortionCBuffer.h"
#include "../Resource/PaperBurnCBuffer.h"
#include "../Scene/Viewport.h"
#include "../Resource/StructuredBuffer.h"

DEFINITION_SINGLE(CRenderManager)

CRenderManager::CRenderManager()	:
	m_PostProcessCBuffer(nullptr),
	m_DistortionCBuffer(nullptr),
	m_PaperBurnCBuffer(nullptr),
	m_PaperBurnTimeMax(10.f),
	m_PaperBurnTime(0.f),
	m_TouchCount(0)
{
	m_RenderSpace = Render_Space::Render2D;

	for (int i = 0; i < RT2D_End; ++i)
	{
		m_RenderList2DCount[i] = 0;
		m_RenderList2DCapacity[i] = 0;
		m_pRenderList2D[i] = nullptr;
	}

	for (int i = 0; i < RT3D_End; ++i)
	{
		m_RenderList3DCount[i] = 0;
		m_RenderList3DCapacity[i] = 0;
		m_pRenderList3D[i] = nullptr;
	}

	m_RenderListDistortionCount = 0;
	m_RenderListDistortionCapacity = 0;
	m_pRenderListDistortion = nullptr;

	memset(m_WorldState, 0, sizeof(CRenderState*) * RST_End);
}

CRenderManager::~CRenderManager()
{
	SAFE_DELETE(m_PostProcessCBuffer);
	SAFE_DELETE(m_DistortionCBuffer);
	SAFE_DELETE(m_PaperBurnCBuffer);

	SAFE_DELETE_ARRAY(m_pRenderListDistortion);
	SAFE_DELETE(m_TorchCBuffer);

	for (int i = 0; i < RT2D_End; ++i)
	{
		SAFE_DELETE_ARRAY(m_pRenderList2D[i]);
	}

	for (int i = 0; i < RT3D_End; ++i)
	{
		SAFE_DELETE_ARRAY(m_pRenderList3D[i]);
	}

	CRenderStateManager::DestroyInst();
}

void CRenderManager::SetWorldRenderState(const std::string& Name)
{
	CRenderState* State = CRenderStateManager::GetInst()->FindRenderState(Name);

	if (!State)
		return;

	m_WorldState[State->GetType()] = State;
}

void CRenderManager::SetBlur(bool Enable)
{
	m_PostProcessCBuffer->SetBlur(Enable);
}

void CRenderManager::SetDistortion(bool Enable)
{
	m_PostProcessCBuffer->SetDistortion(Enable);
}

void CRenderManager::SetDistortionWeight(float Weight)
{
	m_DistortionCBuffer->SetWeight(Weight);
}

void CRenderManager::SetDistortionSpeed(float Speed)
{
	m_DistortionCBuffer->SetSpeed(Speed);
}

void CRenderManager::SetPaperBurn(bool Enable)
{
	m_PaperBurnCBuffer->SetBurn(Enable);
}

bool CRenderManager::Init()
{
	// ?????? ???? ?????? ??????
	if (!CRenderStateManager::GetInst()->Init())
		return false;

	m_DepthDisable = CRenderStateManager::GetInst()->FindRenderState("DepthDisable");
	m_AlphaBlend = CRenderStateManager::GetInst()->FindRenderState("AlphaBlend2");
	m_UIAlphaBlend = CRenderStateManager::GetInst()->FindRenderState("UIAlphaBlend");


	m_TorchCBuffer = new CStructuredBuffer;
	m_vecTorchInfo.resize(100);
	for (size_t i = 0; i < m_vecTorchInfo.size(); ++i)
	{
		m_vecTorchInfo[i].Enable = 0;
	}
	if (!m_TorchCBuffer->Init("TorchBuffer", sizeof(TorchInfo),
		(unsigned int)m_vecTorchInfo.size(), 40, true, CBT_ALL))
	{
		SAFE_DELETE(m_TorchCBuffer);
	}


	return true;
}

void CRenderManager::SetDefaultTarget()
{
	m_DiffuseTarget = (CRenderTarget*)CResourceManager::GetInst()->FindTexture("DiffuseTarget");
	m_DistortionTarget = (CRenderTarget*)CResourceManager::GetInst()->FindTexture("DistortionTarget");

	CDevice::GetInst()->CreateWorld2DTarget(m_DiffuseTarget->GetSurface());

	CResourceManager::GetInst()->CreateMaterial("DiffuseTargetMtrl");
	CResourceManager::GetInst()->AddMaterialTexture("DiffuseTargetMtrl",
		"DiffuseTarget");
	CResourceManager::GetInst()->SetMaterialShader("DiffuseTargetMtrl",
		"FullScreenShader");

	CResourceManager::GetInst()->CreateMaterial("DistortionTargetMtrl");
	CResourceManager::GetInst()->AddMaterialTexture("DistortionTargetMtrl",
		"DistortionTarget");
	CResourceManager::GetInst()->SetMaterialShader("DistortionTargetMtrl",
		"FullScreenDistortionShader");

	m_DiffuseTargetMaterial = CResourceManager::GetInst()->FindMaterial("DiffuseTargetMtrl");

	m_DistortionTargetMaterial = CResourceManager::GetInst()->FindMaterial("DistortionTargetMtrl");

	m_PostProcessCBuffer = new CPostProcessCBuffer;

	m_PostProcessCBuffer->Init();

	m_DistortionCBuffer = new CDistortionCBuffer;

	m_DistortionCBuffer->Init();

	m_PaperBurnCBuffer = new CPaperBurnCBuffer;
	
	m_PaperBurnCBuffer->Init();

	m_DistortionCBuffer->SetWeight(0.05f);

	SetBlur(false);
	SetDistortion(false);
}

void CRenderManager::Render(float DeltaTime)
{

	m_TorchCBuffer->UpdateBuffer(&m_vecTorchInfo[0], sizeof(TorchInfo) * 100);
	
	m_TorchCBuffer->SetShader(40, CBT_ALL);
	m_PostProcessCBuffer->UpdateCBuffer();


	// ?????????? ?????????? ?????? ???????? DiffuseTarget???? ?????? ????.
	// ?????????? nullptr?? ?????????? ?????? ?????? ???????? ??????????
	// ?????? ???????? ????.
	m_DiffuseTarget->ClearTarget();
	m_DiffuseTarget->SetTarget(nullptr);

	for (int i = 0; i < RST_End; ++i)
	{
		if (m_WorldState[i])
			m_WorldState[i]->SetState();
	}

	Render3D(DeltaTime);

	Render2D(DeltaTime);

	for (int i = 0; i < RST_End; ++i)
	{
		if (m_WorldState[i])
			m_WorldState[i]->ResetState();
	}

	// ?????? ???????? ?????? ???????? ??????????.
	m_DiffuseTarget->ResetTarget();

	// ???????? Diffuse Target?? Distortion Target?? ????????.
	// ???? ?????????? ?????? ???? ?????? ?????? ??????.
	m_DistortionTarget->ClearTarget();
	m_DistortionTarget->SetTarget(nullptr);

	m_DepthDisable->SetState();
	m_AlphaBlend->SetState();

	m_DiffuseTargetMaterial->SetMaterial();

	CONTEXT->IASetInputLayout(nullptr);

	UINT	Offset = 0;
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CONTEXT->IASetVertexBuffers(0, 0, nullptr, nullptr, &Offset);
	CONTEXT->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

	CONTEXT->Draw(4, 0);

	m_DiffuseTargetMaterial->ResetMaterial();


	m_AlphaBlend->ResetState();
	m_DepthDisable->ResetState();



	//Diff?? ???????? ???????? ??????.
	m_DiffuseTarget->SetShader(104, TST_PIXEL);

	// ???? Distortion ???????? ?? ???? ????????.
	for (int i = 0; i < m_RenderListDistortionCount; ++i)
	{
		m_pRenderListDistortion[i]->Render(DeltaTime);
	}

	m_RenderListDistortionCount = 0;

	m_DiffuseTarget->ResetShader(104, TST_PIXEL);

	m_DistortionTarget->ResetTarget();

	// ???????? ???? ?????? ???????? ????????.
	
	// ???????? ???? ?????? ???????? ????????.
	m_DiffuseTargetMaterial->PaperBurnEnable(true);
	m_DiffuseTargetMaterial->SetMaterial();
	m_PaperBurnEnable = true;
	if (m_PaperBurnEnable)
	{
		bool	End = false;
	
		m_PaperBurnTime += DeltaTime;
	
		if (m_PaperBurnTime >= m_PaperBurnTimeMax)
		{
			End = true;
			m_PaperBurnTime = m_PaperBurnTimeMax;
		}
	
		m_PaperBurnCBuffer->SetBurn(m_PaperBurnTime / m_PaperBurnTimeMax);
	
	}
	m_DiffuseTargetMaterial->ResetMaterial();

	m_DistortionTargetMaterial->PaperBurnEnable(true);
	m_DistortionTargetMaterial->SetMaterial();
	m_DistortionCBuffer->UpdateCBuffer();
	m_PaperBurnCBuffer->UpdateCBuffer();
	CONTEXT->IASetInputLayout(nullptr);
	
	Offset = 0;
	CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CONTEXT->IASetVertexBuffers(0, 0, nullptr, nullptr, &Offset);
	CONTEXT->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);

	CONTEXT->Draw(4, 0);

	m_DistortionTargetMaterial->ResetMaterial();

	// UI?? ????????.
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	CViewport* Viewport = Scene->GetViewport();

	m_DepthDisable->SetState();
	m_UIAlphaBlend->SetState();

	Viewport->Render();

	if (m_MouseWidget)
		m_MouseWidget->Render();

	m_DepthDisable->ResetState();
	m_UIAlphaBlend->ResetState();
	m_TorchCBuffer->ResetShader(40, CBT_ALL);
	TouchLightClear();
}

void CRenderManager::Render2D(float DeltaTime)
{
	std::sort(m_pRenderList2D[RT2D_MAP], m_pRenderList2D[RT2D_MAP] + m_RenderList2DCount[RT2D_MAP],
		CRenderManager::Sort2DObject);

	m_DepthDisable->SetState();

	for (int j = 0; j < m_RenderList2DCount[RT2D_MAP]; ++j)
	{
		m_pRenderList2D[RT2D_MAP][j]->Render(DeltaTime);
	}

	m_DepthDisable->ResetState();


	for (int i = RT2D_Back1; i < RT2D_End; ++i)
	{
		std::sort(m_pRenderList2D[i], m_pRenderList2D[i] + m_RenderList2DCount[i],
			CRenderManager::Sort2DObject);

		for (int j = 0; j < m_RenderList2DCount[i]; ++j)
		{
			m_pRenderList2D[i][j]->Render(DeltaTime);
		}
	}


	for (int i = 0; i < RT2D_End; ++i)
	{
		m_RenderList2DCount[i] = 0;
	}
}

void CRenderManager::Render3D(float DeltaTime)
{
}
void CRenderManager::AddPrimitiveComponent(CPrimitiveComponent* pPrimitive)
{
	if (pPrimitive->GetPrimitiveType() == PrimitiveComponent_Type::Primitive2D)
	{
		// ?????? ???????? ?????? ????????.
		CScene* Scene = CSceneManager::GetInst()->GetScene();

		if (pPrimitive->GetRender2DType() != RT2D_MAP)
		{
			CCamera* Camera = Scene->GetCameraManager()->GetCurrentCamera();

			Resolution	RS = CDevice::GetInst()->GetResolution();

			Vector3	CameraLB = Camera->GetWorldPos();
			Vector3	CameraRT = CameraLB + Vector3((float)RS.Width, (float)RS.Height, 0.f);

			Vector3	PrimitiveLB = pPrimitive->GetWorldPos() - pPrimitive->GetPivot() * pPrimitive->GetWorldScale();
			Vector3	PrimitiveRT = PrimitiveLB + pPrimitive->GetWorldScale();

			if (CameraLB.x >= PrimitiveRT.x)
				return;

			else if (CameraRT.x <= PrimitiveLB.x)
				return;

			else if (CameraLB.y >= PrimitiveRT.y)
				return;

			else if (CameraRT.y <= PrimitiveLB.y)
				return;
		}

		if (pPrimitive->GetDistortionEnable())
		{
			if (m_RenderListDistortionCapacity == 0)
			{
				m_RenderListDistortionCapacity = 16;
				m_pRenderListDistortion = new CPrimitiveComponent * [m_RenderListDistortionCapacity];

				memset(m_pRenderListDistortion, 0, sizeof(CPrimitiveComponent*) * m_RenderListDistortionCapacity);
			}

			else if (m_RenderListDistortionCapacity == m_RenderListDistortionCount)
			{
				m_RenderListDistortionCapacity *= 2;

				CPrimitiveComponent** pArray = new CPrimitiveComponent * [m_RenderListDistortionCapacity];

				memset(pArray, 0, sizeof(CPrimitiveComponent*) * m_RenderListDistortionCapacity);

				memcpy(pArray, m_pRenderListDistortion, sizeof(CPrimitiveComponent*) * m_RenderListDistortionCount);

				SAFE_DELETE_ARRAY(m_pRenderListDistortion);

				m_pRenderListDistortion = pArray;
			}

			m_pRenderListDistortion[m_RenderListDistortionCount] = pPrimitive;
			++m_RenderListDistortionCount;
		}

		else
		{
			Render_Type_2D  Type2D = pPrimitive->GetRender2DType();

			if (m_RenderList2DCapacity[Type2D] == 0)
			{
				m_RenderList2DCapacity[Type2D] = 16;
				m_pRenderList2D[Type2D] = new CPrimitiveComponent * [m_RenderList2DCapacity[Type2D]];

				memset(m_pRenderList2D[Type2D], 0, sizeof(CPrimitiveComponent*) * m_RenderList2DCapacity[Type2D]);
			}

			else if (m_RenderList2DCapacity[Type2D] == m_RenderList2DCount[Type2D])
			{
				m_RenderList2DCapacity[Type2D] *= 2;

				CPrimitiveComponent** pArray = new CPrimitiveComponent * [m_RenderList2DCapacity[Type2D]];

				memset(pArray, 0, sizeof(CPrimitiveComponent*) * m_RenderList2DCapacity[Type2D]);

				memcpy(pArray, m_pRenderList2D[Type2D], sizeof(CPrimitiveComponent*) * m_RenderList2DCount[Type2D]);

				SAFE_DELETE_ARRAY(m_pRenderList2D[Type2D]);

				m_pRenderList2D[Type2D] = pArray;
			}

			m_pRenderList2D[Type2D][m_RenderList2DCount[Type2D]] = pPrimitive;
			++m_RenderList2DCount[Type2D];
		}
	}

	else if (pPrimitive->GetPrimitiveType() == PrimitiveComponent_Type::Primitive3D)
	{
	}

	// Widget?? ????
	else
	{
		if (m_RenderSpace == Render_Space::Render2D)
		{
			// ?????? ???????? ?????? ????????.
			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CCamera* Camera = Scene->GetCameraManager()->GetCurrentCamera();

			Resolution	RS = CDevice::GetInst()->GetResolution();

			Vector3	CameraLB = Camera->GetWorldPos();
			Vector3	CameraRT = CameraLB + Vector3((float)RS.Width, (float)RS.Height, 0.f);

			Vector3	PrimitiveLB = pPrimitive->GetWorldPos() - pPrimitive->GetPivot() * pPrimitive->GetWorldScale();
			Vector3	PrimitiveRT = PrimitiveLB + pPrimitive->GetWorldScale();

			if (CameraLB.x >= PrimitiveRT.x)
				return;

			else if (CameraRT.x <= PrimitiveLB.x)
				return;

			else if (CameraLB.y >= PrimitiveRT.y)
				return;

			else if (CameraRT.y <= PrimitiveLB.y)
				return;

			if (pPrimitive->GetDistortionEnable())
			{
				if (m_RenderListDistortionCapacity == 0)
				{
					m_RenderListDistortionCapacity = 16;
					m_pRenderListDistortion = new CPrimitiveComponent * [m_RenderListDistortionCapacity];

					memset(m_pRenderListDistortion, 0, sizeof(CPrimitiveComponent*) * m_RenderListDistortionCapacity);
				}

				else if (m_RenderListDistortionCapacity == m_RenderListDistortionCount)
				{
					m_RenderListDistortionCapacity *= 2;

					CPrimitiveComponent** pArray = new CPrimitiveComponent * [m_RenderListDistortionCapacity];

					memset(pArray, 0, sizeof(CPrimitiveComponent*) * m_RenderListDistortionCapacity);

					memcpy(pArray, m_pRenderListDistortion, sizeof(CPrimitiveComponent*) * m_RenderListDistortionCount);

					SAFE_DELETE_ARRAY(m_pRenderListDistortion);

					m_pRenderListDistortion = pArray;
				}

				m_pRenderListDistortion[m_RenderListDistortionCount] = pPrimitive;
				++m_RenderListDistortionCount;
			}

			else
			{
				Render_Type_2D  Type2D = pPrimitive->GetRender2DType();

				if (m_RenderList2DCapacity[Type2D] == 0)
				{
					m_RenderList2DCapacity[Type2D] = 16;
					m_pRenderList2D[Type2D] = new CPrimitiveComponent * [m_RenderList2DCapacity[Type2D]];

					memset(m_pRenderList2D[Type2D], 0, sizeof(CPrimitiveComponent*) * m_RenderList2DCapacity[Type2D]);
				}

				else if (m_RenderList2DCapacity[Type2D] == m_RenderList2DCount[Type2D])
				{
					m_RenderList2DCapacity[Type2D] *= 2;

					CPrimitiveComponent** pArray = new CPrimitiveComponent * [m_RenderList2DCapacity[Type2D]];

					memset(pArray, 0, sizeof(CPrimitiveComponent*) * m_RenderList2DCapacity[Type2D]);

					memcpy(pArray, m_pRenderList2D[Type2D], sizeof(CPrimitiveComponent*) * m_RenderList2DCount[Type2D]);

					SAFE_DELETE_ARRAY(m_pRenderList2D[Type2D]);

					m_pRenderList2D[Type2D] = pArray;
				}

				m_pRenderList2D[Type2D][m_RenderList2DCount[Type2D]] = pPrimitive;
				++m_RenderList2DCount[Type2D];
			}
		}

		else
		{
		}
	}
}

void CRenderManager::AddTouchLight(Vector3 Pos,Matrix matWVP, Vector4 Color, bool bEnable)
{
	if (m_TouchCount < 100)
	{
		m_vecTorchInfo[m_TouchCount].Pos = Pos;
		m_vecTorchInfo[m_TouchCount].matWVP = matWVP;
		m_vecTorchInfo[m_TouchCount].Color = Color;
		m_vecTorchInfo[m_TouchCount].Enable = bEnable? 1:0;
		m_TouchCount++;
	}
}

void CRenderManager::TouchLightClear()
{
	for (int i = 0; i < m_TouchCount; ++i)
	{
		m_vecTorchInfo[i].Enable = 0;
	}
	m_TouchCount = 0;
}

bool CRenderManager::Sort2DObject(CPrimitiveComponent* Src,
	CPrimitiveComponent* Dest)
{
	float	SrcY = Src->GetWorldPos().y - Src->GetPivot().y * Src->GetWorldScale().y;
	float	DestY = Dest->GetWorldPos().y - Dest->GetPivot().y * Dest->GetWorldScale().y;

	return SrcY > DestY;
}
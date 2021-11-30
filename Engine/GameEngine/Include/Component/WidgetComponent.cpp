#include "WidgetComponent.h"
#include "Camera.h"
#include "../Scene/CameraManager.h"
#include "../Render/RenderStateManager.h"
#include "../Render/RenderState.h"
#include "../Device.h"
CWidgetComponent::CWidgetComponent()
{
	m_PrimitiveType = PrimitiveComponent_Type::PrimitiveWidget;
	SetRender2DType(RT2D_Default);
	m_3DType = RT3D_Default;
	m_Space = WidgetComponent_Space::Space2D;
	m_ComponentClassType = Component_Class_Type::Widget;
	m_AlphaBlend = nullptr;
}

CWidgetComponent::CWidgetComponent(const CWidgetComponent& com) :
	CPrimitiveComponent(com)
{
	m_Space = com.m_Space;
	if (com.m_WidgetWindow)
		m_WidgetWindow = com.m_WidgetWindow->Clone();
	m_AlphaBlend = com.m_AlphaBlend;
}

CWidgetComponent::~CWidgetComponent()
{
}

void CWidgetComponent::Start()
{
	CPrimitiveComponent::Start();
}

bool CWidgetComponent::Init()
{
	if (!CPrimitiveComponent::Init())
		return false;
	m_AlphaBlend = CRenderStateManager::GetInst()->FindRenderState("AlphaBlend");

	SetUpdatePosZ(true);

	SetInheritRotX(false);
	SetInheritRotY(false);
	SetInheritRotZ(false);
	return true;
}

void CWidgetComponent::Update(float DeltaTime)
{
	CPrimitiveComponent::Update(DeltaTime);

	if (m_WidgetWindow)
	{
		m_WidgetWindow->Update(DeltaTime);
	}
}

void CWidgetComponent::PostUpdate(float DeltaTime)
{
	CPrimitiveComponent::PostUpdate(DeltaTime);
	m_WidgetWindow->PostUpdate(DeltaTime);

}

void CWidgetComponent::PrevRender(float DeltaTime)
{
	CPrimitiveComponent::PrevRender(DeltaTime);
	if (m_WidgetWindow)
	{
		if (m_Space == WidgetComponent_Space::Space2D)
		{
			Vector2	WidgetPos = Vector2(GetWorldPos().x, GetWorldPos().y);
			// 2D 에서는 카메라의 위치를 빼서 윈도우 상에서의 위치를 구해준다.
			CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

			Vector2	CameraPos = Vector2(Camera->GetWorldPos().x, Camera->GetWorldPos().y);
			if (CameraPos.x < Camera->GetMin().x)
			{
				CameraPos.x = Camera->GetMin().x;
			}
			if (CameraPos.x > Camera->GetMax().x)
			{
				CameraPos.x = Camera->GetMax().x;
			}
			if (CameraPos.y < Camera->GetMin().y)
			{
				CameraPos.y = Camera->GetMin().y;
			}
			if (CameraPos.y > Camera->GetMax().y)
			{
				CameraPos.y = Camera->GetMax().y;
			}

			Vector2	CameraZoomSize = Camera->GetCameraZoomSize();
			float Zoom = Camera->GetCameraZoom();
			Vector2 VRS = Camera->GetVRS();
			Vector2 Size = { VRS.x / 2.f, VRS.y / 2.f };
			Size.x = Size.x / Zoom - Size.x;
			Size.y = Size.y / Zoom - Size.y;

			CameraPos += (VRS + Size) / 2.f;

			WidgetPos -= CameraPos;
			WidgetPos /= CameraZoomSize;

			WidgetPos *= VRS;
			m_WidgetWindow->SetPos(WidgetPos);
		}

		else
		{
		}

		m_WidgetWindow->PrevRender(DeltaTime);
	}
}

void CWidgetComponent::Collision(float DeltaTime)
{
	CPrimitiveComponent::Collision(DeltaTime);
}

void CWidgetComponent::Render(float DeltaTime)
{
	CPrimitiveComponent::Render(DeltaTime);

	m_AlphaBlend->SetState();

	m_WidgetWindow->Render();

	m_AlphaBlend->ResetState();
}

CWidgetComponent* CWidgetComponent::Clone()
{
	return new CWidgetComponent(*this);
}

#include "GateButton.h"
#include "Resource/UITransformConstantBuffer.h"
#include "../GlobalValue.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Scene/Viewport.h>
#include "ResturantInfoWidget.h"
#include "../Object/Player.h"
CGateButton::CGateButton() 
{
}

CGateButton::~CGateButton()
{
}

void CGateButton::Active(bool bActive)
{
	CButton::Active(bActive);
}

void CGateButton::Start()
{
	CButton::Start();
}

bool CGateButton::Init()
{
	CButton::Init();

	return true;
}

void CGateButton::Update(float DeltaTime)
{
	CButton::Update(DeltaTime);
}

void CGateButton::PostUpdate(float DeltaTime)
{
	CButton::PostUpdate(DeltaTime);
}

void CGateButton::Render()
{
	m_TintCBuffer->SetTint(m_ButtonState[(int)m_State].Tint);

	if (m_ButtonState[(int)m_State].Texture)
		m_TransformCBuffer->SetTextureEnable(true);

	else
		m_TransformCBuffer->SetTextureEnable(false);

	CWidget::Render();

	if (m_ButtonState[(int)m_State].Texture)
		m_ButtonState[(int)m_State].Texture->SetShader(0, TST_PIXEL);

	m_Mesh->Render();

	if (m_ButtonState[(int)m_State].Texture)
		m_ButtonState[(int)m_State].Texture->ResetShader(0, TST_PIXEL);
}

CGateButton* CGateButton::Clone()
{
	return new CGateButton(*this);
}

void CGateButton::CollisionMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
	{
		m_State = Button_State::MouseOn;
	}
	//여기에서 현재 게이트위치랑 여기 충돌된위치길이만큼 직선을 그려줘야한다.
}

void CGateButton::CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionUpdateMouse(MousePos, DeltaTime);
}

void CGateButton::CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionReleaseMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
		m_State = Button_State::Normal;
	m_MouseOutCallback();
}

bool CGateButton::IsClick()
{
	if (m_State == Button_State::Click)
	{
		return true;
	}
	return false;
}

bool CGateButton::IsMouseOn()
{
	if (m_State == Button_State::MouseOn)
	{
		return true;
	}
	return false;
}

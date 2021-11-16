
#include "BossDieUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
#include <Input.h>
CBossDieUI::CBossDieUI() :
	m_Alpha(1.f)

{
}

CBossDieUI::CBossDieUI(const CBossDieUI& widget) :
	CWidgetWindow(widget)
{
}

CBossDieUI::~CBossDieUI()
{
}

bool CBossDieUI::Init()
{
	CWidgetWindow::Init();

	SetZOrder(UI_ZOrder::BossSpawnUI);

	m_Image = CreateWidget<CImage>("BossUpImage");
	m_Image->SetSize(1280.f, 720.f);
	m_Image->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_Image->SetPos(0.f, 0.f);
	m_Image->SetCollision(false);
	Enable(false);
	return true;
}

void CBossDieUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (IsEnable())
	{
		m_Alpha -= DeltaTime;
		m_Image->SetColorTint(0.f, 0.f, 0.f, m_Alpha);

		if (m_Alpha < 0.f)
		{
			Enable(false);
			m_Alpha = 1.f;
		}
	}
}

void CBossDieUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBossDieUI::PrevRender(float DeltaTime)
{
	CWidgetWindow::PrevRender(DeltaTime);
}

void CBossDieUI::Render()
{
	CWidgetWindow::Render();
}

CBossDieUI* CBossDieUI::Clone()
{
	return new CBossDieUI(*this);
}



#include "FadeInOut_White.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include "BossUI.h"
#include "WeaponUI.h"
#include "../Stage/StageManager.h"
#include <Engine.h>
#include <Input.h>
#include "UIManager.h"
#include "MiniMap.h"
CFadeInOut_White::CFadeInOut_White() :
	m_FadeOut(false),
	m_FadeIn(false),
	m_Alpha(0.f)
{
}

CFadeInOut_White::~CFadeInOut_White()
{
}

bool CFadeInOut_White::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	
	m_FadeImage = CreateWidget<CImage>("FadeImage2");
	m_FadeImage->SetSize((float)RS.Width, (float)RS.Height);
	m_FadeImage->SetColorTint(1.f, 1.f, 1.f, 0.f);
	m_FadeImage->SetPos(0.f, 0.f);
	m_FadeImage->SetCollision(false);

	return true;
}

void CFadeInOut_White::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_FadeOut)
	{
		m_Alpha += DeltaTime;
		m_FadeImage->SetColorTint(1.f, 1.f, 1.f, m_Alpha);
		if (m_Alpha >= 1.f)
		{
			m_FadeOut = false;
		}
	}
	else if (m_FadeIn)
	{
		m_Alpha -= DeltaTime;
		m_FadeImage->SetColorTint(1.f, 1.f, 1.f, m_Alpha);
		if (m_Alpha <= 0.f)
		{
			m_FadeIn = false;
		}
	}
}

void CFadeInOut_White::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CFadeInOut_White::Render()
{
	CWidgetWindow::Render();
}

CFadeInOut_White* CFadeInOut_White::Clone()
{
	return new CFadeInOut_White(*this);
}


void CFadeInOut_White::SetFadeIn()
{
	m_Alpha = 1.f;
	m_FadeIn = true;
}

void CFadeInOut_White::SetFadeOut()
{
	m_Alpha = 0.f;
	m_FadeOut = true;
}

bool CFadeInOut_White::IsFadeIn()
{
	return false;
}

bool CFadeInOut_White::IsFadeOut()
{
	return false;
}

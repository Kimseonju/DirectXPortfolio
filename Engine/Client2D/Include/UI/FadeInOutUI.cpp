
#include "FadeInOutUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include "BossUI.h"
#include "WeaponUI.h"
CFadeInOutUI::CFadeInOutUI()
{
}

CFadeInOutUI::~CFadeInOutUI()
{
}

bool CFadeInOutUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	m_FadeImage = CreateWidget<CImage>("FadeImage");
	m_FadeImage->SetSize(RS.Width, RS.Height);
	m_FadeImage->SetColorTint(1.f,1.f,1.f, 1.f);
	m_FadeImage->SetPos(RS.Width,RS.Height);
	m_FadeImage->SetCollision(false);

	return true;
}

void CFadeInOutUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CFadeInOutUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CFadeInOutUI::Render()
{
	CWidgetWindow::Render();
}

CFadeInOutUI* CFadeInOutUI::Clone()
{
	return new CFadeInOutUI(*this);
}

void CFadeInOutUI::SetPadeIn()
{
}

void CFadeInOutUI::SetPadeOut()
{
}

bool CFadeInOutUI::IsFadeIn()
{
	return false;
}

bool CFadeInOutUI::IsFadeOut()
{
	return false;
}

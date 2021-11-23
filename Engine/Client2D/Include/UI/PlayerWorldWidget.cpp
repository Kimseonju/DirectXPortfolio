#include "PlayerWorldWidget.h"

CPlayerWorldWidget::CPlayerWorldWidget()
{
}

CPlayerWorldWidget::CPlayerWorldWidget(const CPlayerWorldWidget& widget) :
	CWidgetWindow(widget)
{
}

CPlayerWorldWidget::~CPlayerWorldWidget()
{
}


bool CPlayerWorldWidget::Init()
{
	CWidgetWindow::Init();

	m_ReloadBase = CreateWidget<CImage>("ReloadBase");
	m_ReloadBase->SetPos(0.f, 0.f);
	m_ReloadBase->SetSize(92.f, 4.f);
	m_ReloadBase->SetTexture("ReloadBase", TEXT("Weapon/Range/ReloadBase.png"));
	m_ReloadBase->SetCollision(false);

	m_ReloadBar = CreateWidget<CImage>("ReloadBar");
	m_ReloadBar->SetPos(0.f, 0.f);
	m_ReloadBar->SetSize(8.f, 12.f);
	m_ReloadBar->SetTexture("ReloadBar", TEXT("Weapon/Range/ReloadBar.png"));
	m_ReloadBar->SetCollision(false);


	m_ReloadEffect = CreateWidget<CImage>("ReloadEffect");
	m_ReloadEffect->SetPos(0.f, -4.f);
	m_ReloadEffect->SetSize(108.f, 36.f);
	m_ReloadEffect->CreateAnimation2D<CAnimation2D>();
	CAnimation2D* Animation = m_ReloadEffect->GetAnimation2D();
	Animation->AddAnimationSequence2D("ReloadEffect", false);
	Animation->SetSequencePlayRate("ReloadEffect", 2.f);
	Animation->SetFrameEndFunction<CPlayerWorldWidget>(this, &CPlayerWorldWidget::AnimationFrameEnd);
	m_ReloadEffect->SetCollision(false);
	m_ReloadEffect->Enable(false);
	m_ReloadBase->Enable(false);
	m_ReloadBar->Enable(false);

	return true;
}

void CPlayerWorldWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CPlayerWorldWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerWorldWidget::Render()
{
	CWidgetWindow::Render();
}

CPlayerWorldWidget* CPlayerWorldWidget::Clone()
{
	return new CPlayerWorldWidget(*this);
}

void CPlayerWorldWidget::SetPercentBar(float Percent)
{
	m_ReloadBar->SetPos(92.f * Percent, -4.f);
	m_ReloadBase->Enable(true);
	m_ReloadBar->Enable(true);
}

void CPlayerWorldWidget::AnimationFrameEnd(const std::string& Name)
{
	m_ReloadEffect->Enable(false);

}

void CPlayerWorldWidget::EffectStart()
{
	m_ReloadEffect->Enable(true);
	m_ReloadBase->Enable(false);
	m_ReloadBar->Enable(false);

	CAnimation2D* Animation = m_ReloadEffect->GetAnimation2D();
	Animation->Animation2DRestart();
}

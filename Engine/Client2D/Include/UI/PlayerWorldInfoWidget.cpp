
#include "PlayerWorldInfoWidget.h"

CPlayerWorldInfoWidget::CPlayerWorldInfoWidget()
{
}

CPlayerWorldInfoWidget::CPlayerWorldInfoWidget(const CPlayerWorldInfoWidget& widget) :
	CWidgetWindow(widget)
{
}

CPlayerWorldInfoWidget::~CPlayerWorldInfoWidget()
{
}

bool CPlayerWorldInfoWidget::Init()
{
	CWidgetWindow::Init();

	m_NameText = CreateWidget<CText>("Name");

	m_NameText->SetText(TEXT("Test"));
	m_NameText->SetPos(0.f, 20.f);
	m_NameText->SetSize(200.f, 50.f);
	m_NameText->SetFontSize(30.f);
	m_NameText->SetShadowEnable(true);
	m_NameText->SetShadowColor(1.f, 1.f, 0.f);
	m_NameText->SetShadowAlphaEnable(true);
	m_NameText->SetShadowOpacity(0.5f);
	m_NameText->SetAlignH(TEXT_ALIGN_H::Center);
	m_NameText->SetAlignV(TEXT_ALIGN_V::Bottom);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetPos(50.f, 0.f);
	m_HPBar->SetSize(100.f, 20.f);
	//m_HPBar->SetTint(1.f, 1.f, 1.f, 0.6f);
	m_HPBar->SetTexture("HPBar", TEXT("HPBar.png"));
	m_HPBar->SetBlind(false);
	return true;
}

void CPlayerWorldInfoWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CPlayerWorldInfoWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerWorldInfoWidget::Render()
{
	CWidgetWindow::Render();
}

CPlayerWorldInfoWidget* CPlayerWorldInfoWidget::Clone()
{
	return new CPlayerWorldInfoWidget(*this);
}

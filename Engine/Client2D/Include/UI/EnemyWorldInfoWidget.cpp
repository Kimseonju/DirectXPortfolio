#include "EnemyWorldInfoWidget.h"

CEnemyWorldInfoWidget::CEnemyWorldInfoWidget()
{
}

CEnemyWorldInfoWidget::CEnemyWorldInfoWidget(const CEnemyWorldInfoWidget& widget) :
	CWidgetWindow(widget)
{
}

CEnemyWorldInfoWidget::~CEnemyWorldInfoWidget()
{
}

bool CEnemyWorldInfoWidget::Init()
{
	CWidgetWindow::Init();

	m_NameText = CreateWidget<CText>("Name");
	m_NameText->SetText(TEXT(""));
	m_NameText->SetPos(0.f, 25.f);
	m_NameText->SetSize(200.f, 50.f);
	m_NameText->SetFontSize(15.f);
	m_NameText->SetShadowEnable(true);
	m_NameText->SetShadowColor(1.f, 1.f, 0.f);
	m_NameText->SetShadowAlphaEnable(true);
	m_NameText->SetShadowOpacity(0.5f);

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetPos(50.f, 0.f);
	m_HPBar->SetSize(100.f, 20.f);
	m_HPBar->SetTexture("HPBar", TEXT("HPBar.png"));

	return true;
}

void CEnemyWorldInfoWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CEnemyWorldInfoWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CEnemyWorldInfoWidget::Render()
{
	CWidgetWindow::Render();
}

CEnemyWorldInfoWidget* CEnemyWorldInfoWidget::Clone()
{
	return new CEnemyWorldInfoWidget(*this);
}

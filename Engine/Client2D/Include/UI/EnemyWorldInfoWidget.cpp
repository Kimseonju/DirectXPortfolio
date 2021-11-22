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

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetPos(0.f, 0.f);
	m_HPBar->SetSize(70.f, 20.f);
	m_HPBar->SetTexture("HPBar", TEXT("HPBar.png"));
	m_HPBar->SetCollision(false);

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

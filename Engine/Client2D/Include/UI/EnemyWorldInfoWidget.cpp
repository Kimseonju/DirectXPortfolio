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

void CEnemyWorldInfoWidget::Active(bool bActive)
{
	CWidgetWindow::Active(bActive);
	m_HPBar->Active(bActive);
}

bool CEnemyWorldInfoWidget::Init()
{
	CWidgetWindow::Init();

	m_HPBar = CreateWidget<CProgressBar>("HPBar");

	m_HPBar->SetPos(0.f, 0.f);
	m_HPBar->SetSize(70.f, 20.f);
	
	m_HPBar->SetBackTint(0.f, 0.f, 0.f, 1.f);
	m_HPBar->SetBaseTint(1.f, 0.f, 0.f, 1.f);
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

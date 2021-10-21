
#include "MainHUDWidget.h"
#include "../Object/Player.h"
CMainHUDWidget::CMainHUDWidget() :
	m_Player(nullptr)
{
}

CMainHUDWidget::CMainHUDWidget(const CMainHUDWidget& widget) :
	CWidgetWindow(widget)
{
}

CMainHUDWidget::~CMainHUDWidget()
{
}

bool CMainHUDWidget::Init()
{
	CWidgetWindow::Init();

	m_Text = CreateWidget<CText>("Text");

	m_Text->SetText(TEXT(""));
	m_Text->SetPos(100.f, 400.f);
	m_Text->SetSize(300.f, 50.f);
	m_Text->SetFontSize(10.f);
	m_Text->SetShadowEnable(true);
	m_Text->SetShadowColor(1.f, 1.f, 0.f);
	m_Text->SetShadowAlphaEnable(true);
	m_Text->SetShadowOpacity(0.5f);
	
	m_Time = 0.f;
	m_Index = 0;

	m_ProgressBar = CreateWidget<CProgressBar>("ProgressBar");

	m_ProgressBar->SetPos(50.f, 630.f);
	m_ProgressBar->SetSize(300.f, 50.f);
	//m_ProgressBar->SetTint(1.f, 1.f, 1.f, 0.5f);
	m_ProgressBar->SetTexture("HPBar", TEXT("HPBar.png"));

	return true;
}

void CMainHUDWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_Player)
	{
		std::string str = "PlayerPos.x " + std::to_string(m_Player->GetWorldPos().x) +
			"\nPlayerPos.y " + std::to_string(m_Player->GetWorldPos().y) + "\nAngle "+
			std::to_string(m_Player->GetAngle()) + "\nForce "+
			std::to_string(m_Player->GetForce().x)+ "     "+std::to_string(m_Player->GetForce().y);
		m_Text->SetText(CA2T(str.c_str()));

	}
	
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_TestPercent += 0.5f * DeltaTime;

		if (m_TestPercent > 1.f)
			m_TestPercent = 1.f;

		m_ProgressBar->SetPercent(m_TestPercent);
	}


	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_TestPercent -= 0.5f * DeltaTime;

		if (m_TestPercent < 0.f)
			m_TestPercent = 0.f;

		m_ProgressBar->SetPercent(m_TestPercent);
	}
}

void CMainHUDWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMainHUDWidget::Render()
{
	CWidgetWindow::Render();
}

CMainHUDWidget* CMainHUDWidget::Clone()
{
	return new CMainHUDWidget(*this);
}

void CMainHUDWidget::StartClick()
{
}

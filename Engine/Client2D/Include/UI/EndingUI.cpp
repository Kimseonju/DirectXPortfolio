
#include "EndingUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include <UI/Text.h>
CEndingUI::CEndingUI()
{
}


CEndingUI::~CEndingUI()
{
}

bool CEndingUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	m_MapBase = CreateWidget<CImage>("MapBase");
	m_MapBase->SetPos((float)RS.Width/2.f, 0.f);
	m_MapBase->SetSize((float)RS.Width / 2.f, (float)RS.Height);
	m_MapBase->SetCollision(false);
	m_MapBase->SetColorTint(0.f, 0.f, 0.f, 0.4f);


	m_Logo = CreateWidget<CImage>("Logo");
	m_Logo->SetPos((float)RS.Width / 2.f+150.f, 400.f);
	m_Logo->SetSize(312.f, 150.f);
	m_Logo->SetCollision(false);
	m_Logo->SetTexture("MainLogo", TEXT("TitleScene/MainLogo.png"));

	return true;
}

void CEndingUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CEndingUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CEndingUI::Render()
{
	CWidgetWindow::Render();
}

CEndingUI* CEndingUI::Clone()
{
	return new CEndingUI(*this);
}


#include "BossUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
CBossUI::CBossUI() :
	m_BossProgressBarBase(nullptr),
	m_BossProgressBarBack(nullptr),
	m_BossPortrait(nullptr),
	m_BossProgressBar(nullptr)

{
}

CBossUI::CBossUI(const CBossUI& widget) :
	CWidgetWindow(widget)
{
}

CBossUI::~CBossUI()
{
}

bool CBossUI::Init()
{
	CWidgetWindow::Init();


	m_BossProgressBarBack = CreateWidget<CImage>("BossLifeBack");
	m_BossProgressBarBack->SetSize(500.f, 64.f);
	m_BossProgressBarBack->SetTexture("BossLifeBack", TEXT("UI/BossLifeBack.png"));
	m_BossProgressBarBack->SetPos(0.f, 0.f);
	m_BossProgressBarBack->SetCollision(false);

	m_BossProgressBarBase = CreateWidget<CImage>("BossLifeBase");
	m_BossProgressBarBase->SetSize(500.f, 64.f);
	m_BossProgressBarBase->SetTexture("BossLifeBase", TEXT("UI/BossLifeBase.png"));
	m_BossProgressBarBase->SetPos(0.f, 0.f);
	m_BossProgressBarBase->SetZOrder(1);
	m_BossProgressBarBase->SetCollision(false);

	m_BossPortrait = CreateWidget<CImage>("BossSkellPortrait");
	m_BossPortrait->SetSize(68.f, 40.f);
	m_BossPortrait->SetTexture("BossSkellPortrait", TEXT("UI/BossSkellPortrait.png"));
	m_BossPortrait->SetPos(10.f, 10.f);
	m_BossPortrait->SetCollision(false);


	m_BossProgressBar = CreateWidget<CProgressBar>("BossHPBar");
	m_BossProgressBar->SetSize(405.f, 64.f);
	m_BossProgressBar->SetPos(85.f, 0.f);
	m_BossProgressBar->SetTexture("LifeBar", TEXT("UI/LifeBar.png"));
	m_BossProgressBar->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_BossProgressBar->SetCollision(false);


	return true;
}

void CBossUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CBossUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBossUI::Render()
{
	CWidgetWindow::Render();
}

CBossUI* CBossUI::Clone()
{
	return new CBossUI(*this);
}


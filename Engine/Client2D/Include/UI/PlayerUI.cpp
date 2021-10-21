
#include "PlayerUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
CPlayerUI::CPlayerUI() :
	m_ProgressBar(nullptr)
{
}

CPlayerUI::CPlayerUI(const CPlayerUI& widget) :
	CWidgetWindow(widget)
{
}

CPlayerUI::~CPlayerUI()
{
}

bool CPlayerUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector2 Pos;

	CImage* image;



	image = CreateWidget<CImage>("PlayerLifeBack");
	image->SetSize(74.f * 4, 16.f * 4);
	image->SetTexture("PlayerLifeBack", TEXT("UI/PlayerLifeBack.png"));
	image->SetPos(150.f, 100.f);

	m_ProgressBar = CreateWidget<CProgressBar>("PlayerHPBar");
	m_ProgressBar->SetSize(50.f * 4, 16.f * 4);
	m_ProgressBar->SetPos(240.f, 100.f);
	m_ProgressBar->SetTexture("LifeBar", TEXT("UI/LifeBar.png"));
	m_ProgressBar->SetBackTint(0.f, 0.f, 0.f, 0.f);

	image = CreateWidget<CImage>("PlayerLifeBase");
	image->SetSize(74.f * 4, 16.f * 4);
	image->SetTexture("PlayerLifeBase", TEXT("UI/PlayerLifeBase.png"));
	image->SetPos(150.f, 100.f);

	float hp = (float)CGlobalValue::MainPlayer->GetStatus().GetHP();
	float hpmax= (float)CGlobalValue::MainPlayer->GetStatus().GetHPMax();
	m_ProgressBar->SetPercent(hp/hpmax);

	image= CreateWidget<CImage>("LifeWave");
	image->SetSize(4.f*4, 10.f * 4);
	image->CreateAnimation2D<CLifeWaveAnimation2D>();
	image->SetPos(240.f+(m_ProgressBar->GetSize().x * (hp / hpmax)), 112.f);


	return true;
}

void CPlayerUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CPlayerUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CPlayerUI::Render()
{
	CWidgetWindow::Render();
}

CPlayerUI* CPlayerUI::Clone()
{
	return new CPlayerUI(*this);
}


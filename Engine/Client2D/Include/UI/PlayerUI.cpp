
#include "PlayerUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include "BossUI.h"
#include "WeaponUI.h"
CPlayerUI::CPlayerUI() :
	m_ProgressBar(nullptr),
	m_BossUI(nullptr),
	m_WarningOnHit0(nullptr),
	m_WarningOnHit1(nullptr),
	m_HitTime(0.f)
{
}

CPlayerUI::~CPlayerUI()
{
	m_vecDashCount.clear();
}

bool CPlayerUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector2 Pos;

	CImage* image;

	SetZOrder(UI_ZOrder::PlayerUI);

	image = CreateWidget<CImage>("PlayerLifeBack");
	image->SetSize(296.f, 64.f);
	image->SetTexture("PlayerLifeBack", TEXT("UI/PlayerLifeBack.png"));
	image->SetPos(50.f, 600.f);
	image->SetCollision(false);

	m_ProgressBar = CreateWidget<CProgressBar>("PlayerHPBar");
	m_ProgressBar->SetSize(180.f, 64.f);
	m_ProgressBar->SetPos(140.f, 600.f);
	m_ProgressBar->SetTexture("LifeBar", TEXT("UI/LifeBar.png"));
	m_ProgressBar->SetColorTint(234.f / 255.f, 71.f / 255.f, 71.f / 255.f, 1.f);
	m_ProgressBar->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_ProgressBar->SetCollision(false);

	image = CreateWidget<CImage>("PlayerLifeBase");
	image->SetSize(296.f, 64.f);
	image->SetTexture("PlayerLifeBase", TEXT("UI/PlayerLifeBase.png"));
	image->SetPos(50.f, 600.f);
	image->SetCollision(false);

	float hp = (float)CGlobalValue::MainPlayer->GetStatus().GetHP();
	float hpmax= (float)CGlobalValue::MainPlayer->GetStatus().GetHPMax();
	m_ProgressBar->SetPercent(hp/hpmax);

	image= CreateWidget<CImage>("LifeWave");
	image->SetSize(16.f, 40.f);
	image->CreateAnimation2D<CLifeWaveAnimation2D>();
	image->SetColorTint(234.f / 255.f, 71.f / 255.f, 71.f / 255.f,1.f);
	image->SetPos(140.f+(m_ProgressBar->GetSize().x * (hp / hpmax)), 612.f);
	image->SetCollision(false);

	CPlayer* Player=CGlobalValue::MainPlayer;
	int DashMax=Player->GetStatus().GetDashMax();
	{
		//앞뒤는 미리 만들기 대쉬는 최소 3임

		image = CreateWidget<CImage>("DashBack0");
		image->SetPos(50.f, 560.f);
		image->SetSize(44.f, 32.f);
		image->SetTexture("PlayerUIDashBack", TEXT("UI/DashCountBase_0.png"));
		image->SetCollision(false);
		image = CreateWidget<CImage>("DashCount0");
		image->SetPos(56.f, 568.f);
		image->SetSize(36.f, 16.f);
		image->SetTexture("PlayerUIDashCount", TEXT("UI/DashCount.png"));
		image->SetCollision(false);
		image->SetZOrder(1);
		m_vecDashCount.push_back(image);

		for (int i = 1; i < DashMax-1; ++i)
		{
			std::string str = std::to_string(i);
			image = CreateWidget<CImage>("DashBack"+ str);
			image->SetPos(50.f +i* 36.f, 560.f);
			image->SetSize(36.f, 32.f);
			image->SetTexture("PlayerUIDashBack2", TEXT("UI/DashBase.png"));
			image->SetCollision(false);

			image = CreateWidget<CImage>("DashCount"+ str);
			image->SetPos(56.f + i * 36.f, 568.f);
			image->SetSize(36.f, 16.f);
			image->SetTexture("PlayerUIDashCount", TEXT("UI/DashCount.png"));
			image->SetCollision(false);
			image->SetZOrder(1);
			m_vecDashCount.push_back(image);
		}

		std::string str = std::to_string(DashMax);
		image = CreateWidget<CImage>("DashBack" + str);
		image->SetPos(50.f + (DashMax-1) * 36.f, 560.f);
		image->SetSize(44.f, 32.f);
		image->SetTexture("DashCountBase_01", TEXT("UI/DashCountBase_01.png"));
		image->SetCollision(false);
		image = CreateWidget<CImage>("DashCount" + str);
		image->SetPos(56.f + (DashMax-1) * 36.f, 568.f);
		image->SetSize(36.f, 16.f);
		image->SetTexture("PlayerUIDashCount", TEXT("UI/DashCount.png"));
		image->SetCollision(false);
		image->SetZOrder(1);
		m_vecDashCount.push_back(image);


	}

	m_WarningOnHit0 = CreateWidget<CImage>("RedWarningOnHit_0");
	m_WarningOnHit0->SetSize(640.f, 720.f);
	m_WarningOnHit0->SetTexture("RedWarningOnHit_0", TEXT("UI/RedWarningOnHit_0.png"));
	m_WarningOnHit0->SetPos(0.f, 0.f);
	m_WarningOnHit0->SetCollision(false);
	m_WarningOnHit1 = CreateWidget<CImage>("RedWarningOnHit_1");
	m_WarningOnHit1->SetSize(640.f, 720.f);
	m_WarningOnHit1->SetTexture("RedWarningOnHit_1", TEXT("UI/RedWarningOnHit_1.png"));
	m_WarningOnHit1->SetPos(640.f, 0.f);
	m_WarningOnHit1->SetCollision(false);

	m_PlayerWeaponUI = CreateWidget<CWeaponUI>("WeaponUI");

	//m_BossUI = CreateWidget<CBossUI>("BossUI");
	//m_BossUI->SetPos(100.f, 100.f);
	return true;
}

void CPlayerUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	m_WarningOnHit0->SetColorTint(1.f, 1.f, 1.f, m_HitTime);
	m_WarningOnHit1->SetColorTint(1.f, 1.f, 1.f, m_HitTime);
	CPlayer* Player = CGlobalValue::MainPlayer;
	int Dash=Player->GetStatus().GetDash();
	Dash--;
	for (int i = 0; i < m_vecDashCount.size(); ++i)
	{
		if (i <= Dash)
		{
			m_vecDashCount[i]->Enable(true);
		}
		else
		{
			m_vecDashCount[i]->Enable(false);
		}
	}

	m_HitTime -= DeltaTime;
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

void CPlayerUI::Hit()
{
	m_HitTime = 1.f;
}

void CPlayerUI::WeaponChange()
{
	m_PlayerWeaponUI->WeaponChange();
}


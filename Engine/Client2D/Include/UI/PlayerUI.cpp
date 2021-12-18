
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
	m_HitTime(0.f),
	m_PlayerWeaponUI(nullptr),
	m_bShield(false)
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
	m_ProgressBar->SetSize(200.f, 64.f);
	m_ProgressBar->SetPos(140.f, 600.f);
	m_ProgressBar->SetTexture("LifeBar", TEXT("UI/LifeBar.png"));
	m_ProgressBar->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_ProgressBar->SetCollision(false);

	image = CreateWidget<CImage>("PlayerLifeBase");
	image->SetSize(296.f, 64.f);
	image->SetTexture("PlayerLifeBase", TEXT("UI/PlayerLifeBase.png"));
	image->SetPos(50.f, 600.f);
	image->SetCollision(false);
	image->SetZOrder(1);


	m_HPLifeWave = CreateWidget<CImage>("LifeWave");
	m_HPLifeWave->SetSize(16.f, 40.f);
	m_HPLifeWave->CreateAnimation2D<CLifeWaveAnimation2D>();
	m_HPLifeWave->SetColorTint(234.f / 255.f, 71.f / 255.f, 71.f / 255.f,1.f);
	m_HPLifeWave->SetPos(140.f+(m_ProgressBar->GetSize().x ), 612.f);
	m_HPLifeWave->SetCollision(false);


	m_HPText = CreateWidget<CText>("HPText");
	m_HPText->SetPos(150.f, 580.f);
	m_HPText->SetFontSize(30.f);
	m_HPText->SetCollision(false);
	m_HPText->SetText(TEXT("11"));
	m_HPText->SetZOrder(2);
	m_HPText->SetAlignH(TEXT_ALIGN_H::Center);
	m_HPText->SetAlignV(TEXT_ALIGN_V::Middle);

	m_HPMiddleText = CreateWidget<CText>("HPMiddleText");
	m_HPMiddleText->SetPos(190.f, 580.f);
	m_HPMiddleText->SetFontSize(30.f);
	m_HPMiddleText->SetText(TEXT("/"));
	m_HPMiddleText->SetCollision(false);
	m_HPMiddleText->SetZOrder(2);
	m_HPMiddleText->SetAlignH(TEXT_ALIGN_H::Center);
	m_HPMiddleText->SetAlignV(TEXT_ALIGN_V::Middle);


	m_HPMaxText = CreateWidget<CText>("HPMaxText");
	m_HPMaxText->SetPos(230.f, 580.f);
	m_HPMaxText->SetFontSize(30.f);
	m_HPMaxText->SetCollision(false);
	m_HPMaxText->SetText(TEXT("11"));
	m_HPMaxText->SetZOrder(2);
	m_HPMaxText->SetAlignH(TEXT_ALIGN_H::Center);
	m_HPMaxText->SetAlignV(TEXT_ALIGN_V::Middle);

	CPlayer* Player=CGlobalValue::MainPlayer;
	int DashMax=Player->GetStatus()->GetDashMax();
	{
		//앞뒤는 미리 만들기 대쉬는 최소 2이상

		image = CreateWidget<CImage>("DashBack0");
		image->SetPos(50.f, 560.f);
		image->SetSize(44.f, 32.f);
		image->SetTexture("PlayerUIDashBack", TEXT("UI/DashCountBase_0.png"));
		image->SetCollision(false);
		m_vecDashBack.push_back(image);
		image = CreateWidget<CImage>("DashCount0");
		image->SetPos(58.f, 568.f);
		image->SetSize(36.f, 16.f);
		image->SetTexture("PlayerUIDashCount", TEXT("UI/DashCount.png"));
		image->SetCollision(false);
		image->SetZOrder(1);
		m_vecDashCount.push_back(image);

		for (int i = 0; i < DashMax-2; ++i)
		{
			std::string str = std::to_string(i);
			image = CreateWidget<CImage>("DashBack"+ str);
			image->SetPos(94.f +i* 36.f, 560.f);
			image->SetSize(36.f, 32.f);
			image->SetTexture("PlayerUIDashBase", TEXT("UI/DashBase.png"));
			image->SetCollision(false);
			m_vecDashBack.push_back(image);

			image = CreateWidget<CImage>("DashCount"+ str);
			image->SetPos(94.f + i * 36.f, 568.f);
			image->SetSize(36.f, 16.f);
			image->SetTexture("PlayerUIDashCount", TEXT("UI/DashCount.png"));
			image->SetCollision(false);
			image->SetZOrder(1);
			m_vecDashCount.push_back(image);
		}

		std::string str = std::to_string(DashMax);
		image = CreateWidget<CImage>("DashEnd" + str);
		image->SetPos(94.f + (DashMax-2) * 36.f, 560.f);
		image->SetSize(44.f, 32.f);
		image->SetTexture("PlayerUIDashBac1k", TEXT("UI/DashCountBase_1.png"));
		image->SetCollision(false);
		m_vecDashBack.push_back(image);
		//aimage->SetUIHorizontalReverse2DEnable(true);

		image = CreateWidget<CImage>("DashCount" + str);
		image->SetPos(94.f + (DashMax-2) * 36.f, 568.f);
		image->SetSize(36.f, 16.f);
		image->SetTexture("PlayerUIDashCount", TEXT("UI/DashCount.png"));
		image->SetCollision(false);
		image->SetZOrder(1);
		m_vecDashCount.push_back(image);


	}


	m_GoldImage = CreateWidget<CImage>("GoldImage");
	m_GoldImage->SetSize(21.f, 21.f);
	m_GoldImage->CreateAnimation2D<CAnimation2D>();
	CAnimation2D* Animation2D = m_GoldImage->GetAnimation2D();
	Animation2D->AddAnimationSequence2D("Gold");
	m_GoldImage->SetPos(50.f, 50.f);
	m_GoldImage->SetCollision(false);
	m_GoldImage->SetPivot(0.5f, 0.5f);

	m_GoldText = CreateWidget<CText>("GoldText");
	m_GoldText->SetPos(90.f, 50.f);
	m_GoldText->SetSize(100.f, 28.f);
	m_GoldText->SetFontSize(20.f);
	m_GoldText->SetCollision(false);
	m_GoldText->SetText(TEXT("222222"));
	m_GoldText->SetZOrder(2);
	m_GoldText->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_GoldText->SetPivot(0.5f, 0.5f);

	//m_SatietyImage = CreateWidget<CImage>("SatietyImage");
	//m_SatietyImage->SetSize(34.f, 28.f);
	//m_SatietyImage->SetTexture("SatietyIcon", TEXT("UI/restaurant/SatietyRate.png"));
	//m_SatietyImage->SetPos(50.f, 18.f);
	//m_SatietyImage->SetPivot(0.5f, 0.5f);
	//m_SatietyImage->SetCollision(false);
	//
	//m_SatietyText = CreateWidget<CText>("SatietyText");
	//m_SatietyText->SetPos(100.f, 20.f);
	//m_SatietyText->SetSize(35.f, 28.f);
	//m_SatietyText->SetFontSize(20.f);
	//m_SatietyText->SetCollision(false);
	//m_SatietyText->SetText(TEXT("100"));
	//m_SatietyText->SetZOrder(2);
	//m_SatietyText->SetAlignH(TEXT_ALIGN_H::Left);
	//m_SatietyText->SetPivot(0.5f, 0.5f);
	//
	//m_SatietyTextMiddle = CreateWidget<CText>("SatietyTextMiddle");
	//m_SatietyTextMiddle->SetPos(120.f, 20.f);
	//m_SatietyTextMiddle->SetSize(5.f, 28.f);
	//m_SatietyTextMiddle->SetFontSize(20.f);
	//m_SatietyTextMiddle->SetCollision(false);
	//m_SatietyTextMiddle->SetText(TEXT("/"));
	//m_SatietyTextMiddle->SetZOrder(2);
	//m_SatietyTextMiddle->SetAlignH(TEXT_ALIGN_H::Left);
	//m_SatietyTextMiddle->SetPivot(0.5f, 0.5f);
	//
	//
	//m_SatietyTextMax = CreateWidget<CText>("SatietyTextMax");
	//m_SatietyTextMax->SetPos(145.f, 20.f);
	//m_SatietyTextMax->SetSize(35.f, 28.f);
	//m_SatietyTextMax->SetFontSize(20.f);
	//m_SatietyTextMax->SetCollision(false);
	//m_SatietyTextMax->SetText(TEXT("100"));
	//m_SatietyTextMax->SetZOrder(2);
	//m_SatietyTextMax->SetAlignH(TEXT_ALIGN_H::Left);
	//m_SatietyTextMax->SetPivot(0.5f, 0.5f);

	m_GoldText->SetAlignV(TEXT_ALIGN_V::Middle);
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

	//방어막 UI추가


	m_ShieldBaseUI = CreateWidget<CImage>("ShieldBaseUI");
	m_ShieldBaseUI->SetPos(50.f, 560.f);
	m_ShieldBaseUI->SetSize(208.f, 36.f);
	m_ShieldBaseUI->SetTexture("ShieldBase", TEXT("UI/ShieldBase.png"));
	m_ShieldBaseUI->SetCollision(false);
	m_ShieldBaseUI->SetZOrder(1);
	m_ShieldBaseUI->Enable(false);
	m_ShieldProgressBar = CreateWidget<CProgressBar>("ShieldProgressBar");
	m_ShieldProgressBar->SetPos(52.f, 560.f);
	m_ShieldProgressBar->SetSize(204.f, 36.f);
	m_ShieldProgressBar->SetBaseTint(0.f / 255.f, 224.f/ 255.f, 180.f/ 255.f, 1.f);
	m_ShieldProgressBar->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_ShieldProgressBar->SetCollision(false);
	m_ShieldProgressBar->Enable(false);
	//m_BossUI = CreateWidget<CBossUI>("BossUI");
	//m_BossUI->SetPos(100.f, 100.f);
	return true;
}

void CPlayerUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	CPlayer* Player = CGlobalValue::MainPlayer;
	int Dash=Player->GetStatus()->GetDash();
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

	if (m_bShield)
	{
		m_WarningOnHit0->SetColorTint(0.f, 1.f, 1.f, m_HitTime);
		m_WarningOnHit1->SetColorTint(0.f, 1.f, 1.f, m_HitTime);
	}
	else
	{
		m_WarningOnHit0->SetColorTint(1.f, 1.f, 1.f, m_HitTime);
		m_WarningOnHit1->SetColorTint(1.f, 1.f, 1.f, m_HitTime);
	}
	m_HitTime -= DeltaTime;
	CPlayerStatus* Status = CGlobalValue::MainPlayer->GetStatus();
	int hp = Status->GetHP();
	int hpmax = Status->GetHPMax();
	float Percentt = (float)hp / (float)hpmax;

	std::wstring str;
	str = std::to_wstring(hp);
	m_HPText->SetText(str.c_str());

	str = std::to_wstring(hpmax);
	m_HPMaxText->SetText(str.c_str());

	SetHPBar(Percentt);
	if (m_ShieldProgressBar->IsEnable())
	{
		float ShieldPercent=Status->GetShieldHP_Percent();
		m_ShieldProgressBar->SetPercent(ShieldPercent);
	}

	str = std::to_wstring(Player->GetCoin());
	m_GoldText->SetText(str.c_str());

	//str = std::to_wstring(Player->GetStatus()->GetSatiety());
	//m_SatietyText->SetText(str.c_str());
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

void CPlayerUI::SetShieldUI(bool Enable)
{
	m_ShieldBaseUI->Enable(Enable);
	m_ShieldProgressBar->Enable(Enable);
	CPlayer* Player = CGlobalValue::MainPlayer;
	Player->GetStatus()->SetShield(Enable);
	if (Enable)
	{
		size_t Size = m_vecDashBack.size();
		for (size_t i = 0; i < Size; i++)
		{
			Vector2 Pos = m_vecDashBack[i]->GetPos();
			m_vecDashBack[i]->SetPos(Pos.x, 520.f);
		}
		Size = m_vecDashCount.size();
		for (size_t i = 0; i < Size; i++)
		{
			Vector2 Pos = m_vecDashCount[i]->GetPos();
			m_vecDashCount[i]->SetPos(Pos.x, 528.f);
		}

	}
	else
	{
		size_t Size = m_vecDashBack.size();
		for (size_t i = 0; i < Size; i++)
		{
			Vector2 Pos = m_vecDashBack[i]->GetPos();
			m_vecDashBack[i]->SetPos(Pos.x, 560.f);
		}
		Size = m_vecDashCount.size();
		for (size_t i = 0; i < Size; i++)
		{
			Vector2 Pos = m_vecDashCount[i]->GetPos();
			m_vecDashCount[i]->SetPos(Pos.x, 568.f);
		}
	}
}

void CPlayerUI::Hit(bool bShield)
{
	m_bShield = bShield;
	m_HitTime = 1.f;
}

void CPlayerUI::WeaponChange()
{
	m_PlayerWeaponUI->WeaponChange();
}

void CPlayerUI::SetHPBar(float Percent)
{
	m_ProgressBar->SetPercent(Percent);
	m_HPLifeWave->SetPos(140.f + (m_ProgressBar->GetSize().x * Percent), 612.f);
	float LifeWave = 1.f - Percent;
	if (LifeWave >= 0.2f)
	{
		m_HPLifeWave->SetSize(16.f, 40.f);
	}
	else if (LifeWave < 0.2f)
	{
		m_HPLifeWave->SetSize(16.f*(LifeWave*5.f), 40.f);
	}
	if (LifeWave >= 0.8f)
	{
		m_HPLifeWave->SetSize(16.f * ((1.f-LifeWave) * 5.f), 40.f);
	}
}


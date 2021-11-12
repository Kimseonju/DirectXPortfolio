
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
	image->SetPos(150.f, 600.f);
	image->SetCollision(false);

	m_ProgressBar = CreateWidget<CProgressBar>("PlayerHPBar");
	m_ProgressBar->SetSize(180.f, 64.f);
	m_ProgressBar->SetPos(240.f, 600.f);
	m_ProgressBar->SetTexture("LifeBar", TEXT("UI/LifeBar.png"));
	m_ProgressBar->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_ProgressBar->SetCollision(false);

	image = CreateWidget<CImage>("PlayerLifeBase");
	image->SetSize(296.f, 64.f);
	image->SetTexture("PlayerLifeBase", TEXT("UI/PlayerLifeBase.png"));
	image->SetPos(150.f, 600.f);
	image->SetCollision(false);

	float hp = (float)CGlobalValue::MainPlayer->GetStatus().GetHP();
	float hpmax= (float)CGlobalValue::MainPlayer->GetStatus().GetHPMax();
	m_ProgressBar->SetPercent(hp/hpmax);

	image= CreateWidget<CImage>("LifeWave");
	image->SetSize(16.f, 40.f);
	image->CreateAnimation2D<CLifeWaveAnimation2D>();
	image->SetPos(240.f+(m_ProgressBar->GetSize().x * (hp / hpmax)), 612.f);
	image->SetCollision(false);

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


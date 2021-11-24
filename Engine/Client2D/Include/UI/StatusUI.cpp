
#include "StatusUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include "BossUI.h"
#include "WeaponUI.h"
CStatusUI::CStatusUI()
{
}

CStatusUI::~CStatusUI()
{
}

void CStatusUI::Enable(bool bEnable)
{
	CWidgetWindow::Enable(bEnable);
	m_BasicImage->Enable(bEnable);
	m_BasicText->Enable(bEnable);
	m_DamageImage->Enable(bEnable);
	m_ArmorImage->Enable(bEnable);
	m_CriticalImage->Enable(bEnable);
	m_MoveSpeedImage->Enable(bEnable);
	m_AttackSpeedImage->Enable(bEnable);
	m_ReloadSpeedImage->Enable(bEnable);
	m_DamageText->Enable(bEnable);
	m_DamageMiddleText->Enable(bEnable);
	m_DamageMaxText->Enable(bEnable);
	m_ArmorText->Enable(bEnable);
	m_CriticalText->Enable(bEnable);
	m_MoveSpeedText->Enable(bEnable);
	m_AttackSpeedText->Enable(bEnable);
	m_ReloadSpeedText->Enable(bEnable);
}

bool CStatusUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetZOrder(UI_ZOrder::InventoryUI);

	m_BasicImage = CreateWidget<CImage>("StatusBasicImage");
	m_BasicImage->SetSize(296.f, 252.f);
	m_BasicImage->SetTexture("StatusBasicImage", TEXT("UI/status/Base.png"));
	m_BasicImage->SetPos(100.f, 200.f);
	m_BasicImage->SetCollision(false);
	
	m_BasicText = CreateWidget<CText>("StatusBasicText");
	m_BasicText->SetSize(296.f, 30.f);
	m_BasicText->SetText(TEXT("STATUS"));
	m_BasicText->SetAlignH(TEXT_ALIGN_H::Center);
	m_BasicText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_BasicText->SetFontSize(30.f);
	m_BasicText->SetPos(100.f, 420.f);
	m_BasicText->SetCollision(false);
	m_BasicText->SetZOrder(1);
	
	m_DamageImage = CreateWidget<CImage>("StatusDamageImage");
	m_DamageImage->SetSize(42.f, 42.f);
	m_DamageImage->SetTexture("Stat_00_Pow", TEXT("UI/status/Stat_00_Pow.png"));
	m_DamageImage->SetPos(110.f, 360.f);
	m_DamageImage->SetCollision(false);
	m_DamageImage->SetZOrder(1);

	m_ArmorImage = CreateWidget<CImage>("StatusArmorImage");
	m_ArmorImage->SetSize(42.f, 42.f);
	m_ArmorImage->SetTexture("Stat_01_Def", TEXT("UI/status/Stat_01_Def.png"));
	m_ArmorImage->SetPos(110.f, 310.f);
	m_ArmorImage->SetCollision(false);
	m_ArmorImage->SetZOrder(1);

	m_CriticalImage = CreateWidget<CImage>("StatusCriticalImage");
	m_CriticalImage->SetSize(42.f, 42.f);
	m_CriticalImage->SetTexture("Stat_04_Critical", TEXT("UI/status/Stat_04_Critical.png"));
	m_CriticalImage->SetPos(110.f, 260.f);
	m_CriticalImage->SetCollision(false);
	m_CriticalImage->SetZOrder(1);

	m_MoveSpeedImage = CreateWidget<CImage>("StatusMoveSpeedImage");
	m_MoveSpeedImage->SetSize(42.f, 42.f);
	m_MoveSpeedImage->SetTexture("Stat_07_MoveSpeed", TEXT("UI/status/Stat_07_MoveSpeed.png"));
	m_MoveSpeedImage->SetPos(260.f, 360.f);
	m_MoveSpeedImage->SetCollision(false);
	m_MoveSpeedImage->SetZOrder(1);

	m_AttackSpeedImage = CreateWidget<CImage>("AttackSpeedImage");
	m_AttackSpeedImage->SetSize(42.f, 42.f);
	m_AttackSpeedImage->SetTexture("Stat_08_AttackSpeed", TEXT("UI/status/Stat_08_AttackSpeed.png"));
	m_AttackSpeedImage->SetPos(260.f, 310.f);
	m_AttackSpeedImage->SetCollision(false);
	m_AttackSpeedImage->SetZOrder(1);

	m_ReloadSpeedImage = CreateWidget<CImage>("StatusReloadSpeedImage");
	m_ReloadSpeedImage->SetSize(42.f, 42.f);
	m_ReloadSpeedImage->SetTexture("Stat_09_Reload", TEXT("UI/status/Stat_09_Reload.png"));
	m_ReloadSpeedImage->SetPos(260.f, 260.f);
	m_ReloadSpeedImage->SetCollision(false);
	m_ReloadSpeedImage->SetZOrder(1);


	m_DamageText = CreateWidget<CText>("StatusDamageText");
	m_DamageText->SetSize(100.f, 30.f);
	m_DamageText->SetText(TEXT("20"));
	m_DamageText->SetAlignH(TEXT_ALIGN_H::Center);
	m_DamageText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DamageText->SetFontSize(15.f);
	m_DamageText->SetPos(130.f, 360.f);
	m_DamageText->SetCollision(false);
	m_DamageText->SetZOrder(1);

	m_DamageMiddleText = CreateWidget<CText>("StatusDamageMiddleText");
	m_DamageMiddleText->SetSize(100.f, 30.f);
	m_DamageMiddleText->SetText(TEXT("~"));
	m_DamageMiddleText->SetAlignH(TEXT_ALIGN_H::Center);
	m_DamageMiddleText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DamageMiddleText->SetFontSize(15.f);
	m_DamageMiddleText->SetPos(160.f, 360.f);
	m_DamageMiddleText->SetCollision(false);
	m_DamageMiddleText->SetZOrder(1);

	m_DamageMaxText = CreateWidget<CText>("StatusDamageMaxText");
	m_DamageMaxText->SetSize(100.f, 30.f);
	m_DamageMaxText->SetText(TEXT("20"));
	m_DamageMaxText->SetAlignH(TEXT_ALIGN_H::Center);
	m_DamageMaxText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_DamageMaxText->SetFontSize(15.f);
	m_DamageMaxText->SetPos(190.f, 360.f);
	m_DamageMaxText->SetCollision(false);
	m_DamageMaxText->SetZOrder(1);

	m_ArmorText = CreateWidget<CText>("ArmorText");
	m_ArmorText->SetSize(100.f, 30.f);
	m_ArmorText->SetText(TEXT("3"));
	m_ArmorText->SetAlignH(TEXT_ALIGN_H::Center);
	m_ArmorText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ArmorText->SetFontSize(15.f);
	m_ArmorText->SetPos(160.f, 310.f);
	m_ArmorText->SetCollision(false);
	m_ArmorText->SetZOrder(1);


	m_CriticalText = CreateWidget<CText>("CriticalText");
	m_CriticalText->SetSize(100.f, 30.f);
	m_CriticalText->SetText(TEXT("3"));
	m_CriticalText->SetAlignH(TEXT_ALIGN_H::Center);
	m_CriticalText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_CriticalText->SetFontSize(15.f);
	m_CriticalText->SetPos(160.f, 260.f);
	m_CriticalText->SetCollision(false);
	m_CriticalText->SetZOrder(1);


	m_MoveSpeedText = CreateWidget<CText>("MoveSpeedText");
	m_MoveSpeedText->SetSize(100.f, 30.f);
	m_MoveSpeedText->SetText(TEXT("3"));
	m_MoveSpeedText->SetAlignH(TEXT_ALIGN_H::Center);
	m_MoveSpeedText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_MoveSpeedText->SetFontSize(15.f);
	m_MoveSpeedText->SetPos(300.f, 360.f);
	m_MoveSpeedText->SetCollision(false);
	m_MoveSpeedText->SetZOrder(1);


	m_AttackSpeedText = CreateWidget<CText>("AttackSpeedText");
	m_AttackSpeedText->SetSize(100.f, 30.f);
	m_AttackSpeedText->SetText(TEXT("3"));
	m_AttackSpeedText->SetAlignH(TEXT_ALIGN_H::Center);
	m_AttackSpeedText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_AttackSpeedText->SetFontSize(15.f);
	m_AttackSpeedText->SetPos(300.f, 310.f);
	m_AttackSpeedText->SetCollision(false);
	m_AttackSpeedText->SetZOrder(1);


	m_ReloadSpeedText = CreateWidget<CText>("ReloadSpeedText");
	m_ReloadSpeedText->SetSize(100.f, 30.f);
	m_ReloadSpeedText->SetText(TEXT("3"));
	m_ReloadSpeedText->SetAlignH(TEXT_ALIGN_H::Center);
	m_ReloadSpeedText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ReloadSpeedText->SetFontSize(15.f);
	m_ReloadSpeedText->SetPos(300.f, 260.f);
	m_ReloadSpeedText->SetCollision(false);
	m_ReloadSpeedText->SetZOrder(1);
	return true;
}

void CStatusUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	CPlayer* Player=CGlobalValue::MainPlayer;

	std::wstring str;

	str = std::to_wstring(Player->GetDamage());
	m_DamageText->SetText(str.c_str());

	str = std::to_wstring(Player->GetDamageMax());
	m_DamageMaxText->SetText(str.c_str());

	str = std::to_wstring(Player->GetArmor());
	m_ArmorText->SetText(str.c_str());

	str = std::to_wstring(Player->GetCritical());
	m_CriticalText->SetText(str.c_str());

	str = std::to_wstring(Player->GetMoveSpeed());
	m_MoveSpeedText->SetText(str.c_str());

	str = std::to_wstring(Player->GetAttackSpeed());
	m_AttackSpeedText->SetText(str.c_str());

	str = std::to_wstring(Player->GetReloadSpeed());
	m_ReloadSpeedText->SetText(str.c_str());
}

void CStatusUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CStatusUI::Render()
{
	CWidgetWindow::Render();
}

CStatusUI* CStatusUI::Clone()
{
	return new CStatusUI(*this);
}


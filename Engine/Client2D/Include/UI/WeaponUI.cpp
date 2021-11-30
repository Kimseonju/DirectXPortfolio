
#include "WeaponUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include "UIManager.h"
#include "../Object/Item.h"
#include "../Object/Weapon.h"
#include "../BasicStatus.h"
#include <Scene/SceneResource.h>

CWeaponUI::CWeaponUI() :
	m_SelectWeapon(Select_Weapon::Left)
{
}

CWeaponUI::CWeaponUI(const CWeaponUI& widget) :
	CWidgetWindow(widget)
{
}

CWeaponUI::~CWeaponUI()
{
}

bool CWeaponUI::Init()
{
	CWidgetWindow::Init();

	//WeaponUI
	m_WeaponImage1 = CreateWidget<CImage>("WeaponUIBase1");
	m_WeaponImage1->SetSize(0.f, 0.f);
	m_WeaponImage1->SetPivot(0.5f, 0.5f);
	m_WeaponImage1->SetCollision(false);
	m_WeaponImage1->SetZOrder(4);

	m_WeaponUIBase1 = CreateWidget<CImage>("WeaponUIBase1");
	m_WeaponUIBase1->SetSize(136.f, 96.f);
	m_WeaponUIBase1->SetPos(1100.f, 30.f);
	m_WeaponUIBase1->SetTexture("WeaponUIBase", TEXT("UI/EquippedWeaponBase.png"));
	m_WeaponUIBase1->SetCollision(false);
	m_WeaponUIBase1->SetZOrder(3);


	m_WeaponUIProgressBar1 = CreateWidget<CProgressBar>("WeaponUIProgressBar1");
	m_WeaponUIProgressBar1->SetSize(0.f, 0.f);
	m_WeaponUIProgressBar1->SetPos(1100.f, 30.f);
	m_WeaponUIProgressBar1->SetTint(0.f, 0.f, 0.f, 0.51f);
	m_WeaponUIProgressBar1->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_WeaponUIProgressBar1->SetCollision(false);
	m_WeaponUIProgressBar1->SetZOrder(3);

	m_WeaponMagazine1 = CreateWidget<CText>("WeaponMagazine1");
	m_WeaponMagazine1->SetFontSize(20.f);
	m_WeaponMagazine1->SetPos(1100.f, 30.f);
	m_WeaponMagazine1->SetCollision(false);
	m_WeaponMagazine1->SetZOrder(4);
	m_WeaponMagazine1->SetAlignH(TEXT_ALIGN_H::Center);

	m_WeaponMagazineMiddle1 = CreateWidget<CText>("WeaponMagazineMiddle1");
	m_WeaponMagazineMiddle1->SetFontSize(20.f);
	m_WeaponMagazineMiddle1->SetText(TEXT("/"));
	m_WeaponMagazineMiddle1->SetPos(1100.f, 30.f);
	m_WeaponMagazineMiddle1->SetCollision(false);
	m_WeaponMagazineMiddle1->SetZOrder(4);
	m_WeaponMagazineMiddle1->SetAlignH(TEXT_ALIGN_H::Center);


	m_WeaponMagazineMax1 = CreateWidget<CText>("WeaponMagazineMax1");
	m_WeaponMagazineMax1->SetFontSize(20.f);
	m_WeaponMagazineMax1->SetPos(1100.f, 30.f);
	m_WeaponMagazineMax1->SetCollision(false);
	m_WeaponMagazineMax1->SetZOrder(4);
	m_WeaponMagazineMax1->SetAlignH(TEXT_ALIGN_H::Center);



	m_SelectPos=Vector2(1100.f, 30.f);
	m_WaltPos=Vector2(1130.f, 50.f);

	m_WeaponImage2 = CreateWidget<CImage>("WeaponImage2");
	m_WeaponImage2->SetSize(0.f, 0.f);
	m_WeaponImage2->SetPivot(0.5f, 0.5f);
	m_WeaponImage2->SetCollision(false);
	m_WeaponImage2->SetZOrder(2);

	m_WeaponUIBase2 = CreateWidget<CImage>("WeaponUIBase2");
	m_WeaponUIBase2->SetSize(136.f, 96.f);
	m_WeaponUIBase2->SetPos(1130.f, 50.f);
	m_WeaponUIBase2->SetTexture("WeaponUIBase", TEXT("UI/EquippedWeaponBase.png"));
	m_WeaponUIBase2->SetCollision(false);
	m_WeaponUIBase2->SetZOrder(1);

	m_WeaponUIProgressBar2 = CreateWidget<CProgressBar>("WeaponUIProgressBar1");
	m_WeaponUIProgressBar2->SetSize(0.f, 0.f);
	m_WeaponUIProgressBar2->SetPos(1130.f, 50.f);
	m_WeaponUIProgressBar2->SetTint(0.f, 0.f, 0.f, 0.51f);
	m_WeaponUIProgressBar2->SetBackTint(0.f, 0.f, 0.f, 0.f);
	m_WeaponUIProgressBar2->SetCollision(false);
	m_WeaponUIProgressBar2->SetZOrder(1);

	m_WeaponMagazine2 = CreateWidget<CText>("WeaponMagazine2");
	m_WeaponMagazine2->SetFontSize(20.f);
	m_WeaponMagazine2->SetPos(1130.f, 50.f);
	m_WeaponMagazine2->SetCollision(false);
	m_WeaponMagazine2->SetZOrder(2);
	m_WeaponMagazine2->SetAlignH(TEXT_ALIGN_H::Center);

	m_WeaponMagazineMiddle2 = CreateWidget<CText>("WeaponMagazineMiddle2");
	m_WeaponMagazineMiddle2->SetFontSize(20.f);
	m_WeaponMagazineMiddle2->SetText(TEXT("/"));
	m_WeaponMagazineMiddle2->SetPos(1130.f, 50.f);
	m_WeaponMagazineMiddle2->SetCollision(false);
	m_WeaponMagazineMiddle2->SetZOrder(2);
	m_WeaponMagazineMiddle2->SetAlignH(TEXT_ALIGN_H::Center);

	m_WeaponMagazineMax2 = CreateWidget<CText>("WeaponMagazineMax2");
	m_WeaponMagazineMax2->SetFontSize(20.f);
	m_WeaponMagazineMax2->SetPos(1130.f, 50.f);
	m_WeaponMagazineMax2->SetCollision(false);
	m_WeaponMagazineMax2->SetZOrder(2);
	m_WeaponMagazineMax2->SetAlignH(TEXT_ALIGN_H::Center);
	m_InventoryUI = CUIManager::GetInst()->GetInventory();
	m_SelectWeapon=m_InventoryUI->GetCurrentNumber();
	return true;
}

void CWeaponUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	CWeapon* LeftWeapon=(CWeapon*)m_InventoryUI->GetInventoryWeapon(0);
	CWeapon* RightWeapon = (CWeapon*)m_InventoryUI->GetInventoryWeapon(2);

	Vector2 UIBasePos1 = m_WeaponUIBase1->GetPos();
	Vector2 UIBasePos2 = m_WeaponUIBase2->GetPos();
	if (LeftWeapon)
	{
		Vector2 Size = Vector2(LeftWeapon->GetWorldScale().x, LeftWeapon->GetWorldScale().y);
		m_WeaponImage1->SetTexture(LeftWeapon->GetItemTexture());
		m_WeaponImage1->SetSize(Size*4.f);

		float Percent=LeftWeapon->GetReloadPercent();
		Vector2 Size2 = m_WeaponUIBase1->GetSize();
		m_WeaponUIProgressBar1->SetSize(Vector2(Size2.x * Percent, Size2.y));
		CBasicStatus* Status=LeftWeapon->GetStatus();
		if (Status->GetMagazineMax() != 0)
		{
			m_WeaponMagazine1->Enable(true);
			m_WeaponMagazineMiddle1->Enable(true);
			m_WeaponMagazineMax1->Enable(true);

			std::wstring str;
			str = std::to_wstring(Status->GetMagazine());
			m_WeaponMagazine1->SetText(str.c_str());


			str = std::to_wstring(Status->GetMagazineMax());
			m_WeaponMagazineMax1->SetText(str.c_str());
		}
		else
		{
			m_WeaponMagazine1->Enable(false);
			m_WeaponMagazineMiddle1->Enable(false);
			m_WeaponMagazineMax1->Enable(false);
		}

	}
	else
	{
		m_WeaponImage1->SetSize(0.f, 0.f);
		m_WeaponUIProgressBar1->SetSize(0.f, 0.f);
		m_WeaponMagazine1->Enable(false);
		m_WeaponMagazineMiddle1->Enable(false);
		m_WeaponMagazineMax1->Enable(false);

	}
	if (RightWeapon)
	{
		Vector2 Size = Vector2(RightWeapon->GetWorldScale().x, RightWeapon->GetWorldScale().y);
		m_WeaponImage2->SetTexture(RightWeapon->GetItemTexture());
		m_WeaponImage2->SetSize(Size * 4.f);

		float Percent = RightWeapon->GetReloadPercent();
		Vector2 Size2 = m_WeaponUIBase2->GetSize();
		m_WeaponUIProgressBar2->SetSize(Vector2(Size2.x * Percent, Size2.y));
		CBasicStatus* Status = RightWeapon->GetStatus();
		if (Status->GetMagazineMax() != 0)
		{
			m_WeaponMagazine2->Enable(true);
			m_WeaponMagazineMiddle2->Enable(true);
			m_WeaponMagazineMax2->Enable(true);

			std::wstring str;
			str = std::to_wstring(Status->GetMagazine());
			m_WeaponMagazine2->SetText(str.c_str());

			str = std::to_wstring(Status->GetMagazineMax());
			m_WeaponMagazineMax2->SetText(str.c_str());
		}
		else
		{
			m_WeaponMagazine2->Enable(false);
			m_WeaponMagazineMiddle2->Enable(false);
			m_WeaponMagazineMax2->Enable(false);
		}
	}
	else
	{
		m_WeaponImage2->SetSize(0.f, 0.f);
		m_WeaponUIProgressBar2->SetSize(0.f, 0.f);
		m_WeaponMagazine2->Enable(false);
		m_WeaponMagazineMiddle2->Enable(false);
		m_WeaponMagazineMax2->Enable(false);
	}
	bool Change = true;
	if (m_SelectWeapon == Select_Weapon::Left)
	{
		if (UIBasePos1 != m_SelectPos)
		{
			UIBasePos1 =UIBasePos1.Lerp2DMax(UIBasePos1, m_SelectPos, m_MoveRatio);
			if (m_MoveRatio > 0.5f)
			{
				m_WeaponImage1->SetZOrder(4);
				m_WeaponMagazine1->SetZOrder(4);
				m_WeaponMagazineMiddle1->SetZOrder(4);
				m_WeaponMagazineMax1->SetZOrder(4);
				m_WeaponUIBase1->SetZOrder(3);
				m_WeaponUIProgressBar1->SetZOrder(3);
			}
			Change = false;
		}
		else
		{
			m_WeaponImage1->SetZOrder(4);
			m_WeaponMagazine1->SetZOrder(4);
			m_WeaponMagazineMiddle1->SetZOrder(4);
			m_WeaponMagazineMax1->SetZOrder(4);
			m_WeaponUIBase1->SetZOrder(3);
			m_WeaponUIProgressBar1->SetZOrder(3);
		}
		if (UIBasePos2 != m_WaltPos)
		{
			UIBasePos2 = UIBasePos2.Lerp2DMax(UIBasePos2, m_WaltPos, m_MoveRatio);
			if (m_MoveRatio>0.5f)
			{
				m_WeaponImage2->SetZOrder(2);
				m_WeaponMagazine2->SetZOrder(2);
				m_WeaponMagazineMiddle2->SetZOrder(2);
				m_WeaponMagazineMax2->SetZOrder(2);
				m_WeaponUIBase2->SetZOrder(1);
				m_WeaponUIProgressBar2->SetZOrder(1);
			}
			Change = false;
		}
		else
		{
			m_WeaponImage2->SetZOrder(2);
			m_WeaponMagazine2->SetZOrder(2);
			m_WeaponMagazineMiddle2->SetZOrder(2);
			m_WeaponMagazineMax2->SetZOrder(2);
			m_WeaponUIBase2->SetZOrder(1);
			m_WeaponUIProgressBar2->SetZOrder(1);
		}
	}
	else if (m_SelectWeapon == Select_Weapon::Right)
	{
		if (UIBasePos1 != m_WaltPos)
		{
			UIBasePos1 = UIBasePos1.Lerp2DMax(UIBasePos1, m_WaltPos, m_MoveRatio);
			if (m_MoveRatio> 0.5f)
			{
				m_WeaponImage1->SetZOrder(2);
				m_WeaponMagazine1->SetZOrder(2);
				m_WeaponMagazineMiddle1->SetZOrder(2);
				m_WeaponMagazineMax1->SetZOrder(2);
				m_WeaponUIBase1->SetZOrder(1);
				m_WeaponUIProgressBar1->SetZOrder(1);
			}
			Change = false;
		}
		else
		{
			m_WeaponImage1->SetZOrder(2);
			m_WeaponMagazine1->SetZOrder(2);
			m_WeaponMagazineMiddle1->SetZOrder(2);
			m_WeaponMagazineMax1->SetZOrder(2);
			m_WeaponUIBase1->SetZOrder(1);
			m_WeaponUIProgressBar1->SetZOrder(1);
		}
		if (UIBasePos2 != m_SelectPos)
		{
			UIBasePos2 = UIBasePos2.Lerp2DMax(UIBasePos2, m_SelectPos, m_MoveRatio);
			if (m_MoveRatio> 0.5f)
			{
				m_WeaponImage2->SetZOrder(4);
				m_WeaponMagazine2->SetZOrder(4);
				m_WeaponMagazineMiddle2->SetZOrder(4);
				m_WeaponMagazineMax2->SetZOrder(4);
				m_WeaponUIBase2->SetZOrder(3);
				m_WeaponUIProgressBar2->SetZOrder(3);
			}
			Change = false;
		}
		else
		{
			if (m_MoveRatio > 0.5f)
			{
				m_WeaponImage2->SetZOrder(4);
				m_WeaponMagazine2->SetZOrder(4);
				m_WeaponMagazineMiddle2->SetZOrder(4);
				m_WeaponMagazineMax2->SetZOrder(4);
				m_WeaponUIBase2->SetZOrder(3);
				m_WeaponUIProgressBar2->SetZOrder(3);
			}
		}
	}
	m_MoveRatio += (DeltaTime*2.f);
	m_WeaponUIBase1->SetPos(UIBasePos1);
	m_WeaponUIProgressBar1->SetPos(UIBasePos1);

	m_WeaponUIBase2->SetPos(UIBasePos2);
	m_WeaponUIProgressBar2->SetPos(UIBasePos2);
	Vector2 Size=m_WeaponUIBase1->GetSize();
	Size /= 2.f;
	m_WeaponImage1->SetPos(UIBasePos1 + Size);
	m_WeaponImage2->SetPos(UIBasePos2 + Size);
	UIBasePos1.x += Size.x;
	UIBasePos1.y -= Size.y;
	UIBasePos1.y -= 10.f;
	UIBasePos1.x -= 70.f;

	UIBasePos2.x += Size.x;
	UIBasePos2.y -= Size.y;
	UIBasePos2.y -= 10.f;
	UIBasePos2.x -= 70.f;
	m_WeaponMagazine1->SetPos(UIBasePos1);
	m_WeaponMagazine2->SetPos(UIBasePos2);

	UIBasePos1.x += 20.f;
	UIBasePos2.x += 20.f;

	m_WeaponMagazineMiddle1->SetPos(UIBasePos1);
	m_WeaponMagazineMiddle2->SetPos(UIBasePos2);

	UIBasePos1.x += 20.f;
	UIBasePos2.x += 20.f;

	m_WeaponMagazineMax1->SetPos(UIBasePos1);
	m_WeaponMagazineMax2->SetPos(UIBasePos2);
	m_FinishChange = Change;
}

void CWeaponUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CWeaponUI::Render()
{
	CWidgetWindow::Render();
}

CWeaponUI* CWeaponUI::Clone()
{
	return new CWeaponUI(*this);
}

void CWeaponUI::WeaponChange()
{
	if (!m_FinishChange)
		return;
	m_MoveRatio = 0.f;
	m_Scene->GetResource()->FindSound("PlayerWeaponSwap")->Play();

	if (m_SelectWeapon == Select_Weapon::Left)
	{
		m_SelectWeapon = Select_Weapon::Right;
	}
	else if (m_SelectWeapon == Select_Weapon::Right)
	{
		m_SelectWeapon = Select_Weapon::Left;
	}
	m_InventoryUI->WeaponChange();
}



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
CWeaponUI::CWeaponUI() :
	m_WeaponUIBase1(nullptr),
	m_WeaponUIBase2(nullptr),
	m_WeaponImage1(nullptr),
	m_WeaponImage2(nullptr),
	m_FinishChange(true),
	m_MoveRatio(0.f)

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




	
	m_SelectPos=Vector2(1100.f, 30.f);
	m_WaltPos=Vector2(1130.f, 50.f);

	m_WeaponImage2 = CreateWidget<CImage>("WeaponUIBase1");
	m_WeaponImage2->SetSize(0.f, 0.f);
	m_WeaponImage2->SetPivot(0.5f, 0.5f);
	m_WeaponImage2->SetCollision(false);
	m_WeaponImage2->SetZOrder(2);

	m_WeaponUIBase2 = CreateWidget<CImage>("WeaponUIBase2");
	m_WeaponUIBase2->SetSize(136.f, 96.f);
	m_WeaponUIBase2->SetTexture("WeaponUIBase", TEXT("UI/EquippedWeaponBase.png"));
	m_WeaponUIBase2->SetPos(1130.f, 50.f);
	m_WeaponUIBase2->SetCollision(false);
	m_WeaponUIBase2->SetZOrder(1);

	Vector2 UIBasePos1 = m_WeaponUIBase1->GetPos();
	Vector2 UIBasePos2 = m_WeaponUIBase2->GetPos();
	Vector2 Size = m_WeaponUIBase1->GetSize();
	Size /= 2.f;
	m_WeaponImage1->SetPos(UIBasePos1 + Size);
	m_WeaponImage2->SetPos(UIBasePos2 + Size);


	m_InventoryUI = CUIManager::GetInst()->GetInventory();
	m_SelectWeapon=m_InventoryUI->GetCurrentNumber();
	return true;
}

void CWeaponUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	CItem* LeftWeapon=m_InventoryUI->GetInventoryWeapon(0);
	CItem* RightWeapon = m_InventoryUI->GetInventoryWeapon(2);

	Vector2 UIBasePos1 = m_WeaponUIBase1->GetPos();
	Vector2 UIBasePos2 = m_WeaponUIBase2->GetPos();
	if (LeftWeapon)
	{
		Vector2 Size = Vector2(LeftWeapon->GetWorldScale().x, LeftWeapon->GetWorldScale().y);
		m_WeaponImage1->SetTexture(LeftWeapon->GetItemTexture());
		m_WeaponImage1->SetSize(Size*2.f);
	}
	else
	{

		m_WeaponImage1->SetSize(0.f, 0.f);
	}
	if (RightWeapon)
	{
		Vector2 Size = Vector2(RightWeapon->GetWorldScale().x, RightWeapon->GetWorldScale().y);
		m_WeaponImage2->SetTexture(RightWeapon->GetItemTexture());
		m_WeaponImage2->SetSize(Size * 2.f);
	}
	else
	{
		m_WeaponImage2->SetSize(0.f, 0.f);
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
				m_WeaponUIBase1->SetZOrder(3);
			}
			Change = false;
		}
		if (UIBasePos2 != m_WaltPos)
		{
			UIBasePos2 = UIBasePos2.Lerp2DMax(UIBasePos2, m_WaltPos, m_MoveRatio);
			if (m_MoveRatio>0.5f)
			{
				m_WeaponImage2->SetZOrder(2);
				m_WeaponUIBase2->SetZOrder(1);
			}
			Change = false;
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
				m_WeaponUIBase1->SetZOrder(1);
			}
			Change = false;
		}
		if (UIBasePos2 != m_SelectPos)
		{
			UIBasePos2 = UIBasePos2.Lerp2DMax(UIBasePos2, m_SelectPos, m_MoveRatio);
			if (m_MoveRatio> 0.5f)
			{
				m_WeaponImage2->SetZOrder(4);
				m_WeaponUIBase2->SetZOrder(3);
			}
			Change = false;
		}
	}
	m_MoveRatio += (DeltaTime*2.f);
	m_WeaponUIBase1->SetPos(UIBasePos1);
	m_WeaponUIBase2->SetPos(UIBasePos2);
	Vector2 Size=m_WeaponUIBase1->GetSize();
	Size /= 2.f;
	m_WeaponImage1->SetPos(UIBasePos1 + Size);
	m_WeaponImage2->SetPos(UIBasePos2 + Size);
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


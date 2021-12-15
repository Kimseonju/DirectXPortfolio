
#include "Inventory.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include <Device.h>
#include "InventoryButton.h"
#include <Scene/SceneManager.h>

#include "../Object/ShortSword.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Revolver.h"
#include "../Object/CosmosSword.h"
#include "../Object/DaisyRing.h"
#include "../Object/MiniEarth.h"
#include "../Object/Taana.h"
#include "../Object/Item.h"
#include "../Object/Player.h"
CInventory::CInventory():
	m_Current(Select_Weapon::Left),
	m_WeaponSelect_Left(nullptr),
	m_WeaponSelect_Right(nullptr),
	m_InventoryBaseImage(nullptr),
	m_AccBaseImage(nullptr)

{
}


CInventory::~CInventory()
{
}

bool CInventory::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetZOrder(UI_ZOrder::InventoryUI);
	// �κ� ���
	m_InventoryBaseImage = CreateWidget<CImage>("InventoryBase");

	Vector2 InventoryBasePos;
	Vector2 Size;
	Size.x = 369.f;
	Size.y = 564.f;
	InventoryBasePos.x = RS.Width - (Size.x / 2.f);
	InventoryBasePos.y = Size.y / 2.f;
	m_InventoryBaseImage->SetPos(InventoryBasePos);
	m_InventoryBaseImage->SetSize(Size);
	m_InventoryBaseImage->SetPivot(0.5f, 0.5f);
	m_InventoryBaseImage->SetTexture("Inventory", TEXT("UI/Inventory/InventoryBase.png"));
	m_InventoryBaseImage->SetCollision(false);
	// ����,���� ��ư(1.2)
	CInventoryButton* WeaponButton;
	Vector2 WeaponSize;
	WeaponSize.x = 57.f;
	WeaponSize.y = 57.f;

	WeaponButton = CreateWidget<CInventoryButton>("WeaponButton0" );
	WeaponButton->SetSize(WeaponSize);
	WeaponButton->SetPos(988.f, 430.f);
	WeaponButton->SetPivot(0.5f, 0.5f);
	WeaponButton->SetStateTexture(Button_State::Normal, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::MouseOn, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::Click, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetZOrder(0);
	WeaponButton->SetButtonSlot(InventoryButton_Slot::Weapon);
	m_Weapon.push_back(WeaponButton);

	WeaponButton = CreateWidget<CInventoryButton>("WeaponButton1");
	WeaponButton->SetSize(WeaponSize);
	WeaponButton->SetPos(988.f+9.f+ WeaponSize.x, 430.f);
	WeaponButton->SetPivot(0.5f, 0.5f);
	WeaponButton->SetStateTexture(Button_State::Normal, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::MouseOn, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::Click, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetZOrder(0);
	WeaponButton->SetButtonSlot(InventoryButton_Slot::Weapon);
	m_Weapon.push_back(WeaponButton);

	WeaponButton = CreateWidget<CInventoryButton>("WeaponButton2");
	WeaponButton->SetSize(WeaponSize);
	WeaponButton->SetPos(1150.f, 430.f);
	WeaponButton->SetPivot(0.5f, 0.5f);
	WeaponButton->SetStateTexture(Button_State::Normal, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::MouseOn, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::Click, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetZOrder(0);
	WeaponButton->SetButtonSlot(InventoryButton_Slot::Weapon);
	m_Weapon.push_back(WeaponButton);

	WeaponButton = CreateWidget<CInventoryButton>("WeaponButton3");
	WeaponButton->SetSize(WeaponSize);
	WeaponButton->SetPos(1150.f+9.f + WeaponSize.x, 430.f);
	WeaponButton->SetPivot(0.5f, 0.5f);
	WeaponButton->SetStateTexture(Button_State::Normal, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::MouseOn, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetStateTexture(Button_State::Click, "normals", TEXT("UI/Inventory/inventory.png"));
	WeaponButton->SetZOrder(0);
	WeaponButton->SetButtonSlot(InventoryButton_Slot::Weapon);
	m_Weapon.push_back(WeaponButton);

	//���⼱�ù��
	m_WeaponSelect_Left = CreateWidget<CImage>("WeaponSelect_Left");
	m_WeaponSelect_Left->SetSize(141.f, 90.f);
	m_WeaponSelect_Left->SetPos(1020.f, 440.f);
	m_WeaponSelect_Left->SetPivot(0.5f, 0.5f);
	m_WeaponSelect_Left->SetTexture("WeaponSelectLeft", TEXT("UI/Inventory/WeaponSelect0.png"));
	m_WeaponSelect_Left->SetCollision(false);
	m_WeaponSelect_Right = CreateWidget<CImage>("WeaponSelect_Right");
	m_WeaponSelect_Right->SetSize(141.f, 90.f);
	m_WeaponSelect_Right->SetPos(1180.f, 440.f);
	m_WeaponSelect_Right->SetPivot(0.5f, 0.5f);
	m_WeaponSelect_Right->SetTexture("WeaponSelectRight", TEXT("UI/Inventory/WeaponSelect1.png"));
	m_WeaponSelect_Right->SetCollision(false);

	//�Ǽ��縮

	m_AccBaseImage = CreateWidget<CImage>("AccessoryBase.png");
	m_AccBaseImage->SetSize(254.f, 75.f);
	m_AccBaseImage->SetPos(1100.f, 350.f);
	m_AccBaseImage->SetPivot(0.5f, 0.5f);
	m_AccBaseImage->SetTexture("AccessoryBase", TEXT("UI/Inventory/accessoryZone.png"));
	m_AccBaseImage->SetCollision(false);

	CInventoryButton* AccButton;
	for (int i = 0; i < 4; ++i)
	{
		std::string str;
		str = std::to_string(i);
		AccButton = CreateWidget<CInventoryButton>("AccButton"+str);
		AccButton->SetSize(WeaponSize);
		AccButton->SetPos(1008.f+(WeaponSize.x + 4.f) * i, 350.f);
		AccButton->SetPivot(0.5f, 0.5f);
		AccButton->SetStateTexture(Button_State::Normal, "accessory", TEXT("UI/Inventory/accessory.png"));
		AccButton->SetStateTexture(Button_State::MouseOn, "accessory", TEXT("UI/Inventory/accessory.png"));
		AccButton->SetStateTexture(Button_State::Click, "accessory", TEXT("UI/Inventory/accessory.png"));
		AccButton->SetButtonSlot(InventoryButton_Slot::Acc);
		m_Accs.push_back(AccButton);
	}

	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			std::string str;
			str = std::to_string(y*5+x);
			WeaponButton = CreateWidget<CInventoryButton>("InventoryButton"+ str);
			WeaponButton->SetSize(WeaponSize);
			WeaponButton->SetPos(972.f+ (WeaponSize.x + 8.f) * x, 255.f-(WeaponSize.x + 7.f)*y);
			WeaponButton->SetPivot(0.5f, 0.5f);
			WeaponButton->SetStateTexture(Button_State::Normal, "normals", TEXT("UI/Inventory/inventory.png"));
			WeaponButton->SetStateTexture(Button_State::MouseOn, "selected", TEXT("UI/Inventory/inventory_select.png"));
			WeaponButton->SetStateTexture(Button_State::Click, "selected", TEXT("UI/Inventory/inventory_select.png"));
			WeaponButton->SetZOrder(1);
			WeaponButton->SetButtonSlot(InventoryButton_Slot::All);
			m_Items.push_back(WeaponButton);
		}
	}


	CItem* Item = m_Scene->SpawnObject<CShortSword>("CShortSword1");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[5]->SetItem(Item);

	Item = m_Scene->SpawnObject<CMetalBoomerang>("MetalBoomerang");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[2]->SetItem(Item);


	Item = m_Scene->SpawnObject<CRevolver>("Revolver");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[4]->SetItem(Item);

	Item = m_Scene->SpawnObject<CCosmosSword>("CosmosSword");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[7]->SetItem(Item);


	Item = m_Scene->SpawnObject<CDaisyRing>("DaisyRing");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[9]->SetItem(Item);


	Item = m_Scene->SpawnObject<CMiniEarth>("MiniEarth");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[10]->SetItem(Item);


	Item = m_Scene->SpawnObject<CTaana>("Taana");
	Item->Enable(false);
	Item->StateNoMapItem();
	m_Items[11]->SetItem(Item);

	m_CoinText = CreateWidget<CText>("GoldText");
	m_CoinText->SetColor(0.f, 0.f, 0.f);
	m_CoinText->SetText(L"1000");
	m_CoinText->SetFontSize(20.f);
	m_CoinText->SetPos(1130.f, -40.f);
	//text->SetAlignH(TEXT_ALIGN_H::Right);
	return true;
}

void CInventory::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_Current == Select_Weapon::Left)
	{
		m_WeaponSelect_Left->Enable(true);
		m_WeaponSelect_Right->Enable(false);

	}
	else if (m_Current == Select_Weapon::Right)
	{
		m_WeaponSelect_Left->Enable(false);
		m_WeaponSelect_Right->Enable(true);
	}
	CPlayer* Player=CGlobalValue::MainPlayer;

	std::wstring str;
	str = std::to_wstring(Player->GetCoin());

	m_CoinText->SetText(str.c_str());
}

void CInventory::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CInventory::Render()
{
	CWidgetWindow::Render();
}

CInventory* CInventory::Clone()
{
	return new CInventory(*this);
}

CItem* CInventory::GetWeapon() const
{
	switch (m_Current)
	{
	case Select_Weapon::Left:
		return m_Weapon[0]->GetItem();
		break;
	case Select_Weapon::Right:
		return m_Weapon[2]->GetItem();
		break;
	}
	return nullptr;
}


CItem* CInventory::GetInventoryWeapon(int Index) const
{
	return m_Weapon[Index]->GetItem();
}

void CInventory::WeaponChange()
{
	if (m_Current == Select_Weapon::Left)
	{
		m_Current = Select_Weapon::Right;
	}
	else if (m_Current == Select_Weapon::Right)
	{
		m_Current = Select_Weapon::Left;
	}
}

bool CInventory::AddInventoryItem(CItem* Item)
{
	auto iter = m_Items.begin();
	auto iterEnd = m_Items.end();

	for (; iter != iterEnd; ++iter)
	{
		//�������� ���ٸ� �߰��ϱ�
		if (!(*iter)->GetItem())
		{
			(*iter)->SetItem(Item);
			return true;
		}
	}
	//�κ��丮�� �����ִ�.
	return false;

}

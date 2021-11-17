
#include "ShopUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include <Device.h>
#include "InventoryButton.h"
#include <Scene/SceneManager.h>

#include "../Object/ShortSword.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Item.h"
#include "ShopButton.h"
CShopUI::CShopUI()

{
}


CShopUI::~CShopUI()
{
}

bool CShopUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetZOrder(UI_ZOrder::ShopUI);
	// 인벤 배경
	m_BaseImage = CreateWidget<CImage>("InventoryBase");

	Vector2 Size;
	Size.x = 488.f;
	Size.y = 720.f;
	m_BaseImage->SetPos(0.f,0.f);
	m_BaseImage->SetSize(Size);
	m_BaseImage->SetTexture("ShopBase", TEXT("UI/shop/DungeonShopBase.png"));
	m_BaseImage->SetCollision(false);
	m_ShopUIButton = CreateWidget<CShopButton>("ShopButton");
	m_ShopUIButton->SetSize(310.f, 105.f);
	m_ShopUIButton->SetPos(244.f,300.f);
	m_ShopUIButton->SetPivot(0.f, 0.f);
	m_ShopUIButton->SetStateTexture(Button_State::Normal, "ShopNormal", TEXT("UI/shop/shopItemBase.png"));
	m_ShopUIButton->SetStateTexture(Button_State::MouseOn, "Shopselected", TEXT("UI/shop/shopItemBase_selected.png"));
	m_ShopUIButton->SetStateTexture(Button_State::Click, "Shopselected", TEXT("UI/shop/shopItemBase_selected.png"));
	m_ShopUIButton->SetZOrder(1);
	//m_Items.push_back(WeaponButton);
	//or (int y = 0; y < 3; ++y)
	//
	//	for (int x = 0; x < 5; ++x)
	//	{
	//		std::string str;
	//		str = std::to_string(y * 5 + x);
	//		WeaponButton = CreateWidget<CShopUIButton>("InventoryButton" + str);
	//		WeaponButton->SetSize(WeaponSize);
	//		WeaponButton->SetPos(972.f + (WeaponSize.x + 8.f) * x, 255.f - (WeaponSize.x + 7.f) * y);
	//		WeaponButton->SetPivot(0.5f, 0.5f);
	//		WeaponButton->SetStateTexture(Button_State::Normal, "normals", TEXT("UI/Inventory/inventory.png"));
	//		WeaponButton->SetStateTexture(Button_State::MouseOn, "selected", TEXT("UI/Inventory/inventory_select.png"));
	//		WeaponButton->SetStateTexture(Button_State::Click, "selected", TEXT("UI/Inventory/inventory_select.png"));
	//		WeaponButton->SetZOrder(1);
	//		WeaponButton->SetButtonSlot(InventoryButton_Slot::All);
	//		m_Items.push_back(WeaponButton);
	//	}
	//
	return true;
}

void CShopUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CShopUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CShopUI::Render()
{
	CWidgetWindow::Render();
}

CShopUI* CShopUI::Clone()
{
	return new CShopUI(*this);
}


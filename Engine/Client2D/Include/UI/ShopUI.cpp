
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
#include "../GlobalValue.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Revolver.h"
#include "../Object/Player.h"
#include "UIManager.h"
CShopUI::CShopUI()

{
}


CShopUI::~CShopUI()
{
}

void CShopUI::Enable(bool bEnable)
{
	CWidgetWindow::Enable(bEnable);
	m_BaseImage->Enable(bEnable);
	auto iter = m_ShopItemInfo.begin();
	auto iterEnd = m_ShopItemInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		iter->Enable(bEnable);
	}
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


	for (int i = 0; i < 4; ++i)
	{

		
		CItem* Item = nullptr;
		m_Scene->SpawnObject<CShortSword>("CShortSwordShop");
		ShopItemInfo ShopInfo;
		int SelectWeapon=GetRandom(0, Weapons::End-1);

		std::string str = std::to_string(i);
		switch (SelectWeapon)
		{
		case ShortSword:
			Item = m_Scene->SpawnObject<CShortSword>("ShortSwordShop"+ str);
			break;
		case MetalBoomerang:
			Item = m_Scene->SpawnObject<CMetalBoomerang>("MetalBoomerangShop"+ str);
			break;
		case Revolver:
			Item = m_Scene->SpawnObject<CRevolver>("RevolverShop"+ str);
			break;
		}
		Item->Enable(false);
		Item->StateNoMapItem();



		CShopButton* ShopUIButton;
		CImage* ItemImage;
		CText* ItemName;
		CText* ItemPrice;
		ItemImage = CreateWidget<CImage>("ShopUIItemImage" + str);
		ItemImage->SetTexture(Item->GetItemTexture());
		ItemImage->SetPos(30.f, 100.f + 110.f * i);
		ItemImage->SetSize(100.f, 105.f);
		ItemImage->SetCollision(false);

		ShopUIButton = CreateWidget<CShopButton>("ShopUIButton"+str);
		ShopUIButton->SetSize(310.f, 105.f);
		ShopUIButton->SetPos(130.f, 100.f+110.f*i);
		ShopUIButton->SetPivot(0.f, 0.f);
		ShopUIButton->SetStateTexture(Button_State::Normal, "ShopNormal", TEXT("UI/shop/shopItemBase.png"));
		ShopUIButton->SetStateTexture(Button_State::MouseOn, "Shopselected", TEXT("UI/shop/shopItemBase_selected.png"));
		ShopUIButton->SetStateTexture(Button_State::Click, "Shopselected", TEXT("UI/shop/shopItemBase_selected.png"));
		ShopUIButton->SetClickCallback< CShopUI>(this, &CShopUI::ShopButtonClick);
		ShopUIButton->SetItem(Item);
		ItemName = CreateWidget<CText>("ItemName");
		ItemName->SetSize(400.f, 105.f);
		ItemName->SetPos(140.f, 80.f + 110.f * i);
		ItemName->SetFontSize(23.f);
		ItemName->SetAlignH(TEXT_ALIGN_H::Left);
		ItemName->SetAlignV(TEXT_ALIGN_V::Top);
		ItemName->SetText(Item->GetItemName());
		ItemName->SetFont("DungreedFont");
		ItemName->SetCollision(false);


		int Price=Item->GetPrice();

		TCHAR buf[10];
		memset(buf, 0, sizeof(buf));
		_itot_s(Price, buf, 10);

		ItemPrice = CreateWidget<CText>("ItemBuyCoin");
		ItemPrice->SetSize(150.f, 100.f);
		ItemPrice->SetPos(250.f, 40.f + 110.f * i);
		ItemPrice->SetFontSize(20.f);
		ItemPrice->SetColor(1.f, 1.f, 0.f);
		ItemPrice->SetText(buf);
		ItemPrice->SetAlignV(TEXT_ALIGN_V::Top);
		ItemPrice->SetAlignH(TEXT_ALIGN_H::Right);
		ItemPrice->SetFont("DungreedFont");
		ItemPrice->SetCollision(false);

		ShopInfo.Item = Item;
		ShopInfo.ShopButton = ShopUIButton;
		ShopInfo.ItemImage = ItemImage;
		ShopInfo.ItemName = ItemName;
		ShopInfo.ItemPrice = ItemPrice;

		m_ShopItemInfo.push_back(ShopInfo);
	}
	


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

void CShopUI::ShopButtonClick()
{

	auto iter = m_ShopItemInfo.begin();
	auto iterEnd = m_ShopItemInfo.end();

	for (; iter != iterEnd; ++iter)
	{
		//클릭된 버튼 찾기
		if ((*iter).ShopButton->IsClick())
		{
			CPlayer* Player = CGlobalValue::MainPlayer;

			int ItemPrice=(*iter).Item->GetPrice();
			if (Player->SubCoin(ItemPrice))
			{
				//구입성공
				CInventory* Inventory = CUIManager::GetInst()->GetInventory();
				if (Inventory->AddInventoryItem((*iter).Item))
				{
					//추가성공
					(*iter).Active(false);
					iter=m_ShopItemInfo.erase(iter);
					return;
				}
				else
				{
					//추가못했으면 다시원래대로
					Player->AddCoin(ItemPrice);

				}
			}
			//여기까지왔으면 실패한상태이다.
			return;
		}
	}



	//여기서 클릭했을시 아이템클릭된버튼을 찾고난후
	// 그 버튼을 지운다.
}


#include "ShopButton.h"
#include "../Object/Item.h"
#include "Resource/UITransformConstantBuffer.h"
#include "BasicMouse.h"
#include "../GlobalValue.h"
#include "ItemInfoWidget.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Scene/Viewport.h>
#include "../UI/ShopInfoWidget.h"
CShopButton::CShopButton() :
	m_ItemInfoWidget(nullptr),
	m_Item(nullptr)
{
}

CShopButton::~CShopButton()
{
}

void CShopButton::Active(bool bActive)
{
	CButton::Active(bActive);
	m_ItemInfoWidget->Active(bActive);
}

void CShopButton::Start()
{
	CButton::Start();
	Vector2 Pos = GetPos();
	Vector2 Size = m_ItemInfoWidget->GetSize();
	Pos.x += Size.x;
	m_ItemInfoWidget->SetPos(Pos);
	m_ItemInfoWidget->SetCollision(false);
}

bool CShopButton::Init()
{
	CButton::Init();
	SetClickCallback(this, &CShopButton::Click);
	//아이템 받아오고 전부 설정
	m_Item->GetName();


	m_ItemInfoWidget = m_Scene->GetViewport()->AddWindow<CItemInfoWidget>("ItemInfoWidget" + m_Name);
	m_ItemInfoWidget->Enable(false);
	m_ItemInfoWidget->SetZOrder(10);


	return true;
}

void CShopButton::Update(float DeltaTime)
{
	CButton::Update(DeltaTime);

	//if (m_State == Button_State::Click)
	//{
	//	if (m_Item)
	//	{
	//		CBasicMouse* Mouse = CGlobalValue::MainMouse;
	//	}
	//}

}

void CShopButton::PostUpdate(float DeltaTime)
{
	CButton::PostUpdate(DeltaTime);
}

void CShopButton::Render()
{
	m_TintCBuffer->SetTint(m_ButtonState[(int)m_State].Tint);

	if (m_ButtonState[(int)m_State].Texture)
		m_TransformCBuffer->SetTextureEnable(true);

	else
		m_TransformCBuffer->SetTextureEnable(false);

	CWidget::Render();

	if (m_ButtonState[(int)m_State].Texture)
		m_ButtonState[(int)m_State].Texture->SetShader(0, TST_PIXEL);

	m_Mesh->Render();

	if (m_ButtonState[(int)m_State].Texture)
		m_ButtonState[(int)m_State].Texture->ResetShader(0, TST_PIXEL);
}

CShopButton* CShopButton::Clone()
{
	return new CShopButton(*this);
}

void CShopButton::CollisionMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
	{
		m_State = Button_State::MouseOn;
	}


	if (m_Item)
	{
		m_ItemInfoWidget->Enable(true);
		m_ItemInfoWidget->SetItemNameText(m_Item->GetItemName());
		m_ItemInfoWidget->SetAttackDamageText(m_Item->GetDamage(), m_Item->GetDamageMax());
		m_ItemInfoWidget->SetAttackSpeedText(m_Item->GetAttackSpeed());
		m_ItemInfoWidget->SetItemRankText(m_Item->GetItemRank());
		m_ItemInfoWidget->SetItemTypeText(m_Item->GetItemType());
		m_ItemInfoWidget->SetItemText(m_Item->GetItemText());
		m_ItemInfoWidget->SetImage(m_Item->GetItemTexture());
	}
}

void CShopButton::CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionUpdateMouse(MousePos, DeltaTime);
	//CGlobalValue::MainMouse->InventoryMove(this);
}

void CShopButton::CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionReleaseMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
		m_State = Button_State::Normal;
	m_ItemInfoWidget->Enable(false);
}

void CShopButton::SetItem(CItem* Item)
{
	m_Item = Item;
}

CItem* CShopButton::GetItem() const
{
	return m_Item;
}

void CShopButton::Click()
{
	if (m_Item)
	{
		CBasicMouse* mouse = CGlobalValue::MainMouse;
	}
}

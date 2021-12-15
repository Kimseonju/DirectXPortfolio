#include "InventoryButton.h"
#include "../Object/Item.h"
#include "Resource/UITransformConstantBuffer.h"
#include "BasicMouse.h"
#include "../GlobalValue.h"
#include "ItemInfoWidget.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Scene/Viewport.h>
CInventoryButton::CInventoryButton()	:
	m_InventoryButtonState(InventoryButton_State::Normal),
	m_ItemInfoWidget(nullptr),
	m_Slot(InventoryButton_Slot::All),
	m_Item(nullptr)
{
}

CInventoryButton::~CInventoryButton()
{
}

void CInventoryButton::Start()
{
	CButton::Start();
	Vector2 Pos = GetPos();
	Vector2 Size = m_ItemInfoWidget->GetSize();
	Pos.x -= Size.x;
	m_ItemInfoWidget->SetPos(Pos);
	m_ItemInfoWidget->SetCollision(false);
	m_ItemInfoWidget->Enable(false);
}

bool CInventoryButton::Init()
{
	CButton::Init();
	SetClickCallback(this, &CInventoryButton::Click);

	m_ItemInfoWidget = m_Scene->GetViewport()->AddWindow<CItemInfoWidget>("ItemInfoWidget" + m_Name);
	m_ItemInfoWidget->Enable(false);
	m_ItemInfoWidget->SetZOrder(10);
	return true;
}

void CInventoryButton::Update(float DeltaTime)
{
	CButton::Update(DeltaTime);

	if (m_State == Button_State::Click)
	{
		if (m_Item)
		{
			CBasicMouse* Mouse=CGlobalValue::MainMouse;
			Mouse->InventoryClick(this);
		}
	}

}

void CInventoryButton::PostUpdate(float DeltaTime)
{
	CButton::PostUpdate(DeltaTime);
}

void CInventoryButton::Render()
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


	if (m_Item)
	{
		m_TransformCBuffer->SetTextureEnable(true);
		m_TransformCBuffer->UpdateCBuffer();

		CTexture* texture=m_Item->GetItemTexture();

		texture->SetShader(0, TST_PIXEL);
		m_Mesh->Render();
		texture->ResetShader(0, TST_PIXEL);

	}
}

CInventoryButton* CInventoryButton::Clone()
{
	return new CInventoryButton(*this);
}

void CInventoryButton::CollisionMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
	{
		m_State = Button_State::MouseOn;
	}


	if (m_Item)
	{
		m_ItemInfoWidget->Enable(true);
		if (m_Item->GetType() == ITEM_TYPE::Weapon_One_Hand || m_Item->GetType() == ITEM_TYPE::Weapon_Two_Hand)
		{

			m_ItemInfoWidget->SetItemNameText(m_Item->GetItemName(), m_Item->GetType());
			m_ItemInfoWidget->SetAttackDamageText(m_Item->GetDamage(), m_Item->GetDamageMax());
			m_ItemInfoWidget->SetAttackSpeedText(m_Item->GetAttackSpeed());
			m_ItemInfoWidget->SetItemRankText(m_Item->GetItemRank());
			m_ItemInfoWidget->SetItemTypeText(m_Item->GetItemType());
			m_ItemInfoWidget->SetItemText(m_Item->GetItemText());
			m_ItemInfoWidget->SetImage(m_Item->GetItemTexture());
		}
		else
		{
			m_ItemInfoWidget->SetItemNameText(m_Item->GetItemName(), m_Item->GetType());
			m_ItemInfoWidget->SetAttackDamageText(m_Item->GetDamage(), 0, TEXT("위력 :"));
			m_ItemInfoWidget->SetAttackSpeedText(m_Item->GetHPMax(), TEXT("최대체력 :"), 0);
			m_ItemInfoWidget->SetItemRankText(m_Item->GetItemRank());
			m_ItemInfoWidget->SetItemTypeText(m_Item->GetItemType());
			m_ItemInfoWidget->SetItemText(m_Item->GetItemText());
			m_ItemInfoWidget->SetImage(m_Item->GetItemTexture());
			//악세사리임

		}
	}
}

void CInventoryButton::CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionUpdateMouse(MousePos, DeltaTime);
	CGlobalValue::MainMouse->InventoryMove(this);
}

void CInventoryButton::CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionReleaseMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
		m_State = Button_State::Normal;
	m_ItemInfoWidget->Enable(false);
}

void CInventoryButton::SetItem(CItem* Item)
{
	m_Item = Item;
}

CItem* CInventoryButton::GetItem() const
{
	return m_Item;
}

void CInventoryButton::Click()
{
	if (m_Item)
	{
		CBasicMouse* mouse = CGlobalValue::MainMouse;
	}
}

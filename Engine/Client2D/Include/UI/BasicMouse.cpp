#include "BasicMouse.h"
#include <Input.h>
#include "InventoryButton.h"
#include <Scene/SceneResource.h>
#include <Scene/Scene.h>
CBasicMouse::CBasicMouse():
	m_State(Mouse_State::UI),
	m_ClickInventoryButton(nullptr),
	m_Item(nullptr),
	m_Down(false),
	m_Push(false),
	m_Up(false),
	m_UpItem(false),
	m_ClickDownSound(false)
{
}


CBasicMouse::~CBasicMouse()
{
}

bool CBasicMouse::Init()
{
	CMouseWidget::Init();
	return true;
}

void CBasicMouse::Update(float DeltaTime)
{
	CMouseWidget::Update(DeltaTime);
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_Down && !m_Push)
			m_Down = true;

		else if (!m_Push)
		{
			m_Down = false;
			m_Push = true;
		}
	}

	else if (m_Push || m_Down)
	{
		m_Up = true;
		m_UpItem = true;
		m_Push = false;
		m_Down = false;
	}

	else if (m_Up)
	{
		m_Up = false;
		
	}
	else if (m_UpItem)
	{
		m_UpItem = false;
		m_Item = nullptr;
	}

	//CInput::GetInst()->GetMouseMove DILBUTTON(MouseState)
	switch (m_State)
	{
	case Mouse_State::World:
		SetPivot(0.5f, -0.5f);
		SetTexture("ShootingCursor", TEXT("UI/Cursor/ShootingCursor.png"));
		break;
	case Mouse_State::UI:
		SetPivot(0.f, 0.f);
		SetTexture("BasicCursor", TEXT("UI/Cursor/BasicCursor.png"));
		break;
	default:
		break;
	}


}

void CBasicMouse::PostUpdate(float DeltaTime)
{
	CMouseWidget::PostUpdate(DeltaTime);
}

void CBasicMouse::Render()
{
	CMouseWidget::Render();
	if (m_Item)
	{
		m_TransformCBuffer->SetTextureEnable(true);
		m_TransformCBuffer->UpdateCBuffer();

		CTexture* texture = m_Item->GetItemTexture();

		texture->SetShader(0, TST_PIXEL);
		m_Mesh->Render();
		texture->ResetShader(0, TST_PIXEL);
		
	}
}

CMouseWidget* CBasicMouse::Clone()
{
	return new CBasicMouse(*this);
}

void CBasicMouse::InventoryClick(CInventoryButton* Button)
{
	m_Item = Button->GetItem();
	m_ClickInventoryButton = Button;
	if (!m_ClickDownSound)
	{
		m_ClickDownSound = true;
		m_Scene->GetResource()->FindSound("ItemInputInventory")->Play();
	}
}

void CBasicMouse::InventoryMove(CInventoryButton* Button)
{
	if ((m_UpItem||m_Up) && m_Item)
	{
		m_ClickDownSound = false;
		if (Button->GetButtonState() == InventoryButton_State::NotItem)
		{
			ClearItem();
		}
		else if (Button->GetItem() == nullptr)
		{
			m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
			switch (m_Item->GetType())
			{
			case ITEM_TYPE::Weapon_One_Hand:
			{
				if (Button->GetButtonSlot() == InventoryButton_Slot::Weapon
					|| Button->GetButtonSlot() == InventoryButton_Slot::All)
				{
					Button->SetItem(m_Item);
					m_Item = nullptr;
					m_ClickInventoryButton->SetItem(nullptr);
					m_ClickInventoryButton = nullptr;
					m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
				}
			}
				break;
			case ITEM_TYPE::Weapon_Two_Hand:
			{
				if (Button->GetButtonSlot() == InventoryButton_Slot::Weapon
					|| Button->GetButtonSlot() == InventoryButton_Slot::All)
				{
					Button->SetItem(m_Item);
					m_Item = nullptr;
					m_ClickInventoryButton->SetItem(nullptr);
					m_ClickInventoryButton = nullptr;
					m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
				}
			}
				break;
			case ITEM_TYPE::Acc:
			{
				if (Button->GetButtonSlot() == InventoryButton_Slot::Acc
					|| Button->GetButtonSlot() == InventoryButton_Slot::All)
				{
					Button->SetItem(m_Item);
					m_Item = nullptr;
					m_ClickInventoryButton->SetItem(nullptr);
					m_ClickInventoryButton = nullptr;
					m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
				}
			}
				break;
			case ITEM_TYPE::End:
				m_Item = nullptr;
				m_ClickInventoryButton->SetItem(nullptr);
				m_ClickInventoryButton = nullptr;
				break;
			}
		}

		else
		{
			switch (m_Item->GetType())
			{
			case ITEM_TYPE::Weapon_One_Hand:
			{
				if (Button->GetButtonSlot() == InventoryButton_Slot::Weapon
					|| Button->GetButtonSlot() == InventoryButton_Slot::All)
				{
					CItem* Item = Button->GetItem();
					Button->SetItem(m_Item);
					m_Item = nullptr;
					m_ClickInventoryButton->SetItem(Item);
					m_ClickInventoryButton = nullptr;
					m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
				}
			}
			break;
			case ITEM_TYPE::Weapon_Two_Hand:
			{
				if (Button->GetButtonSlot() == InventoryButton_Slot::Weapon
					|| Button->GetButtonSlot() == InventoryButton_Slot::All)
				{
					CItem* Item = Button->GetItem();
					Button->SetItem(m_Item);
					m_Item = nullptr;
					m_ClickInventoryButton->SetItem(Item);
					m_ClickInventoryButton = nullptr;
					m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
				}
			}
			break;
			case ITEM_TYPE::Acc:
			{
				if (Button->GetButtonSlot() == InventoryButton_Slot::Acc
					|| Button->GetButtonSlot() == InventoryButton_Slot::All)
				{
					CItem* Item = Button->GetItem();
					Button->SetItem(m_Item);
					m_Item = nullptr;
					m_ClickInventoryButton->SetItem(Item);
					m_ClickInventoryButton = nullptr;
					m_Scene->GetResource()->FindSound("ItemOutInventory")->Play();
				}
			}
			break;
			case ITEM_TYPE::End:
				m_Item = nullptr;
				m_ClickInventoryButton->SetItem(nullptr);
				m_ClickInventoryButton = nullptr;
				break;
			}

		}
	}
}

void CBasicMouse::ClearItem()
{
	m_Item = nullptr;
	m_ClickInventoryButton = nullptr;
}

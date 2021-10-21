#pragma once
#include <UI/Button.h>
#include "../GlobalValue.h"
//Inventory�� �������
class CItem;
class CImage;
class CText;
class CInventoryButton :
	public CButton
{
	friend class CViewport;
	friend class CScene;
	friend class CWidgetWindow;

protected:
	CInventoryButton();
	CInventoryButton(const CInventoryButton& widget);
	virtual ~CInventoryButton();

protected:
	CItem* m_Item;
	InventoryButton_State m_InventoryButtonState;
	class CItemInfoWidget* m_ItemInfoWidget;
	InventoryButton_Slot m_Slot;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CInventoryButton* Clone();

public:
	virtual void CollisionMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime);
public:
	void SetButtonState(InventoryButton_State State)
	{
		m_InventoryButtonState= State;
	}
	void SetButtonSlot(InventoryButton_Slot Slot)
	{
		m_Slot = Slot;
	}
	InventoryButton_State GetButtonState() const
	{
		return m_InventoryButtonState;
	}
	InventoryButton_Slot GetButtonSlot() const
	{
		return m_Slot;
	}
	void SetItem(CItem* Item);
	CItem* GetItem() const ;
	void Click();
};


#pragma once
#include <UI/Button.h>
#include "../GlobalValue.h"
#include "UI/Image.h"
#include "UI/Text.h"
//Inventory가 들고있음
class CItem;
class CImage;
class CText;
class CShopButton :
	public CButton
{
	friend class CViewport;
	friend class CScene;
	friend class CWidgetWindow;

protected:
	CShopButton();
	virtual ~CShopButton();

protected:
	CSharedPtr<CImage> m_TextBase;
	CSharedPtr<CText> m_ItemName;
	CSharedPtr<CImage> m_CoinImage;
	CItem* m_Item;
	class CItemInfoWidget* m_ItemInfoWidget;
public:
	virtual void Active(bool bActive);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CShopButton* Clone();

public:
	virtual void CollisionMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime);
public:
	bool IsClick()
	{
		if (m_State == Button_State::Click)
		{
			return true;
		}
		return false;
	}
	void SetItem(CItem* Item);
	CItem* GetItem() const;
	void Click();
};


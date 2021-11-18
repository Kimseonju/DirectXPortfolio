#pragma once
#include <UI/Button.h>
#include "../GlobalValue.h"
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
	CItem* m_Item;
	CImage*  m_TextBase;
	CText* m_ItemName;
	CImage* m_CoinImage;
	class CItemInfoWidget* m_ItemInfoWidget;
public:
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


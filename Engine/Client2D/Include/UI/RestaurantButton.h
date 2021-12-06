#pragma once
#include <UI/Button.h>
#include "../GlobalValue.h"
#include "UI/Image.h"
#include "UI/Text.h"
//Inventory가 들고있음
class CRestaurantButton :
	public CButton
{
	friend class CViewport;
	friend class CScene;
	friend class CWidgetWindow;

protected:
	CRestaurantButton();
	virtual ~CRestaurantButton();

protected:
	CSharedPtr<CImage> m_Base;
	CSharedPtr<CText> m_FoodName;
	class CResturantInfoWidget* m_ResturantInfoWidget;
	FoodType m_Type;
	std::wstring m_Foodstr;
	int m_Price;
	int m_SatietyNumber;
	bool m_Eat;
public:
	void SetEat(bool bEat)
	{
		m_Eat = bEat;
	}

	std::wstring GetFoodstr() const
	{
		return m_Foodstr;
	}

	int GetPrice() const
	{
		return m_Price;
	}

	int GetSatiety() const
	{
		return m_SatietyNumber;
	}

	bool IsEat() const
	{
		return m_Eat;
	}
public:
	virtual void Active(bool bActive);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CRestaurantButton* Clone();

public:
	virtual void CollisionMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime);
public:
	void SetFoodType(FoodType Type);
	bool PlayerEat();
public:
	FoodType GetFoodType()
	{
		return m_Type;
	}
	bool IsClick();
	bool IsMouseOn();
};


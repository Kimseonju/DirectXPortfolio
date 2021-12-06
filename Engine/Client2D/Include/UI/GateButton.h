#pragma once
#include <UI/Button.h>
#include "../GlobalValue.h"
#include "UI/Image.h"
#include "UI/Text.h"
//Inventory가 들고있음
class CGateButton :
	public CButton
{
	friend class CViewport;
	friend class CScene;
	friend class CWidgetWindow;

protected:
	CGateButton();
	virtual ~CGateButton();

protected:
	CSharedPtr<CImage> m_Base;
	Vector2 m_CurPos;
	std::function<void()>	m_MouseOutCallback;
public:
	void SetCurPos(Vector2 Pos)
	{
		m_CurPos = Pos;
	}
	Vector2 GetCurPos()const
	{
		return m_CurPos;
	}
public:
	virtual void Active(bool bActive);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render();
	virtual CGateButton* Clone();

public:
	virtual void CollisionMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime);
	virtual void CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime);
public:
	bool IsClick();
	bool IsMouseOn();

public:

	template <typename T>
	void SetMouseOutCallback(T* Obj, void(T::* Func)())
	{
		m_MouseOutCallback = std::bind(Func, Obj);
	}
};


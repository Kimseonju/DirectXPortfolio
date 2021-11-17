#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "../BasicStatus.h"

class CKeyboardUIObject :
	public CGameObject
{
	friend class CScene;

protected:
	CKeyboardUIObject();
	CKeyboardUIObject(const CKeyboardUIObject& obj);
	virtual ~CKeyboardUIObject();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	Vector2 m_SizeBar;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CKeyboardUIObject* Clone();

public:
	void SetKey(std::string Key);
};

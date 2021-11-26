#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
class CEndingMountain :
	public CGameObject
{
	friend class CScene;

protected:
	CEndingMountain();
	CEndingMountain(const CEndingMountain& obj);
	virtual ~CEndingMountain();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEndingMountain* Clone();
};

#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
class CEndingCloud :
	public CGameObject
{
	friend class CScene;

protected:
	CEndingCloud();
	CEndingCloud(const CEndingCloud& obj);
	virtual ~CEndingCloud();

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
	virtual CEndingCloud* Clone();
};

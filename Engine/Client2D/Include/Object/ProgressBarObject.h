#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../BasicStatus.h"

class CProgressBarObject :
	public CGameObject
{
	friend class CScene;

protected:
	CProgressBarObject();
	CProgressBarObject(const CProgressBarObject& obj);
	virtual ~CProgressBarObject();

protected:
	CSharedPtr<CSpriteComponent> m_SpriteBack;
	CSharedPtr<CSpriteComponent> m_SpriteBar;
	Vector2 m_SizeBar;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CProgressBarObject* Clone();

public:
	void SetHPBar(float Percent);
};

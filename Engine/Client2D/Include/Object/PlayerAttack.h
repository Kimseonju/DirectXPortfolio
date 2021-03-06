#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../BasicStatus.h"

class CPlayerAttack :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayerAttack();
	CPlayerAttack(const CPlayerAttack& obj);
	virtual ~CPlayerAttack();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	float m_AttackTimeMax;
	float m_AttackTime;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerAttack* Clone();
};

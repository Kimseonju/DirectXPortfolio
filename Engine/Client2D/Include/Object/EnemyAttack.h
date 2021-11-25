#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../BasicStatus.h"

class CEnemyAttack :
	public CGameObject
{
	friend class CScene;

protected:
	CEnemyAttack();
	CEnemyAttack(const CEnemyAttack& obj);
	virtual ~CEnemyAttack();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	float m_AttackTimeMax;
	float m_AttackTime;
	int   m_Damage;
public:
	void SetDamage(int Damage)
	{
		m_Damage = Damage;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEnemyAttack* Clone();
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
};

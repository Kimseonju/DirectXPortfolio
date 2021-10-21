#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../BasicStatus.h"
#include "../GlobalValue.h"

class CEnemy :
	public CGameObject
{
	friend class CScene;

protected:
	CEnemy();
	CEnemy(const CEnemy& obj);
	virtual ~CEnemy();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CColliderBox2D> m_AttackRangeCollider2D;
	CSharedPtr<CRigidBodyComponent> m_Body;
	CSharedPtr<CWidgetComponent> m_EnemyInfoWidgetComponent;
	class CEnemyWorldInfoWidget* m_EnemyInfoWidget;

	Enemy_State m_State;
	class CAnimation2D* m_Animation2D;
	CBasicStatus m_Status;
	class CWeapon* m_Weapon;
	class CWeaponArm* m_WeaponArm;
	bool m_OneAttack;
	Object_Dir m_Dir;

	bool m_StartGravity;
protected:
	bool    m_ChildFire;
	float   m_ChildFireTime;
	float   m_ChildFireTimeMax;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEnemy* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
};

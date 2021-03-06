#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../BasicStatus.h"
#include "../GlobalValue.h"
#include <EngineFSM.h>

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
	CSharedPtr<CColliderBox2D> m_Collider2DHorizon;
	CSharedPtr<CColliderBox2D> m_Collider2DVertical;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CColliderBox2D> m_AttackRangeCollider2D;
	CSharedPtr<CRigidBodyComponent> m_Body;
	CEngineFSM<CEnemy> m_EnemyFSM;
	CSharedPtr<CWidgetComponent> m_EnemyInfoWidgetComponent;
	class CEnemyWorldInfoWidget* m_EnemyInfoWidget;

	Enemy_State m_State;
	class CAnimation2D_FSM* m_Animation2D;
	CBasicStatus* m_Status;
	class CWeapon* m_Weapon;
	class CWeaponArm* m_WeaponArm;
	bool m_OneAttack;
	Object_Dir m_Dir;
	bool m_WallCol;
	float m_EnemyHit;
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
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEnemy* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void Enable(bool bEnable);
	virtual void SetStatus(const std::string& Name);
	virtual void DropGold() {}
public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionAttackRangeMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionHorizonBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionHorizonMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionHorizonEnd(const HitResult& result, CCollider* Collider);
	virtual void CollisionVerticalBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionVerticalMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionVerticalEnd(const HitResult& result, CCollider* Collider);
	//????
	virtual void ColDirHorizon(float Angle, CCollider* Col);
	virtual void ColDirVertical(float Angle, CCollider* Col);
	virtual void ColTilePassDirVertical(float Angle, CCollider* Col);
public:
	virtual void FindStart() {}
	virtual void FindStay() {}
	virtual void FindEnd() {}
	virtual void MoveStart() {}
	virtual void MoveStay() {}
	virtual void MoveEnd() {}
	virtual void AttackStart() {}
	virtual void AttackStay() {}
	virtual void AttackEnd() {}
	virtual void DieStart();
	virtual void DieStay();
	virtual void DieEnd() {}

	
};

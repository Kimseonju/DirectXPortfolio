#pragma once
#include "Enemy.h"
#include "../GlobalValue.h"
class CBanshee :
	public CEnemy
{
	friend class CScene;

protected:
	CBanshee();
	CBanshee(const CBanshee& obj);
	virtual ~CBanshee();
private:
	bool m_PlayerFind;
	float m_AttackTimer;
	float m_AttackTimerMax;
	bool m_BansheeAttack;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBanshee* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void DropGold();
public:

	virtual void FindStay() override;
	virtual void MoveStart() override;
	virtual void MoveStay() override;
	virtual void AttackStart()override;
	virtual void AttackStay() override;
};


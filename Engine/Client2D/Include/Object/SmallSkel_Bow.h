#pragma once
#include "Enemy.h"
#include "../GlobalValue.h"
class CSmallSkel_Bow :
	public CEnemy
{
	friend class CScene;

protected:
	CSmallSkel_Bow();
	CSmallSkel_Bow(const CSmallSkel_Bow& obj);
	virtual ~CSmallSkel_Bow();
private:
	bool m_PlayerFind;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSmallSkel_Bow* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionAttackRangeMiddle(const HitResult& result, CCollider* Collider);

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


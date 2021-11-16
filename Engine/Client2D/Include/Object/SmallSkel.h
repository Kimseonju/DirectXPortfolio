#pragma once
#include "Enemy.h"
class CSmallSkel :
    public CEnemy
{
	friend class CScene;

protected:
	CSmallSkel();
	CSmallSkel(const CSmallSkel& obj);
	virtual ~CSmallSkel();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSmallSkel* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
public:

	void FindStay() override;
	void MoveStart() override;
	void MoveStay() override;
	void AttackStart()override;
	void AttackStay() override;
};


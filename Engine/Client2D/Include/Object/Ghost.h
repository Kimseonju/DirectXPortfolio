#pragma once
#include "Enemy.h"
#include "../GlobalValue.h"
//고스트는 길찾기알고리즘통해 찾아가기
class CGhost :
	public CEnemy
{
	friend class CScene;

protected:
	CGhost();
	CGhost(const CGhost& obj);
	virtual ~CGhost();
private:
	bool m_PlayerFind;
	bool m_GhostAttack;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGhost* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

	virtual void DropGold();
public:
	virtual void AnimationFrameEnd(const std::string& Name);

	virtual void CollisionHorizonBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionHorizonMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionHorizonEnd(const HitResult& result, CCollider* Collider);
	virtual void CollisionVerticalBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionVerticalMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionVerticalEnd(const HitResult& result, CCollider* Collider);
	//충돌
	virtual void ColDirHorizon(float Angle, CCollider* Col);
	virtual void ColDirVertical(float Angle, CCollider* Col);
public:

	virtual void FindStay() override;
	virtual void MoveStart() override;
	virtual void MoveStay() override;
	virtual void AttackStart()override;
	virtual void AttackStay() override;

};


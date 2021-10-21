#pragma once
#include "Enemy.h"
class CBelial :
	public CEnemy
{
	friend class CScene;

protected:
	CBelial();
	CBelial(const CBelial& obj);
	virtual ~CBelial();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelial* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	void Attack1();
	void Attack2();
	void Attack3();
	void Attack4();
public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
};


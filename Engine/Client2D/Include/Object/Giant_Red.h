#pragma once
#include "Enemy.h"
#include "../GlobalValue.h"
#include "Giant_RedBulletMain.h"
class CGiant_Red :
	public CEnemy
{
	friend class CScene;

protected:
	CGiant_Red();
	CGiant_Red(const CGiant_Red& obj);
	virtual ~CGiant_Red();
private:
	bool m_PlayerFind;
	float m_AttackTimer;
	float m_AttackTimerMax;
	bool m_Giant_RedAttack;
	CSharedPtr<CGiant_RedBulletMain> m_Bullet;
public:
	virtual void Active(bool bActive);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGiant_Red* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
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


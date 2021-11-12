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
private:
	float m_AttackTimer;
	float m_AttackTimerMax;
	float m_PatternTimer;
	float m_PatternTimerMax;

	float m_SwordSpawnTimer;
	float m_SwordSpawnTimerMax;
	bool m_SwordSpawn;
	bool m_Attacking;
	Belial_Pattern m_Pattern;
	class CBelialHand* m_LeftHand;
	class CBelialHand* m_RightHand;
	std::vector<class CBelialWeapon*> m_BelialWeapon;
	CSharedPtr<CColliderBox2D> m_SpawnColliderBox2D;
	bool m_Spawn;
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
	void AttackSword(float DeltaTime);
	void AttackBullet(float DeltaTime);
	void AttackLaser(float DeltaTime);
	void Spawn()
	{
		m_Spawn = true;
	}
public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);
	void CollisionBossSpawnBegin(const HitResult& result, CCollider* Collider);
	
public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
};


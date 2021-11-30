#pragma once
#include "Enemy.h"
#include <Component/ParticleSystemComponent.h>
class CBelial :
	public CGameObject
{
	friend class CScene;

protected:
	CBelial();
	virtual ~CBelial();
private:
	std::vector<class CBelialWeapon*> m_BelialWeapon;
	class CBelialHand* m_LeftHand;
	class CBelialHand* m_RightHand;

	CSharedPtr<CColliderBox2D> m_SpawnColliderBox2D;
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSpriteComponent> m_BackSprite;
	CSharedPtr<CParticleSystemComponent> m_BackParticle;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CEngineFSM<CEnemy> m_EnemyFSM;
	CBasicStatus* m_Status;
	class CAnimation2D* m_Animation2D;
	class CAnimation2D* m_BackAnimation2D;
	bool m_Attacking;
	Belial_Pattern m_Pattern;
	float m_PatternTimer;

	float m_AttackTimer;
	float m_AttackTimerMax;

	float m_SwordSpawnTimer;
	float m_SwordSpawnTimerMax;
	bool m_SwordSpawn;

	float m_BulletAngle;
	float m_BulletFireCount;
	float m_BulletFireCountMax;

	bool m_Spawn;
	float m_Alpha;
	float m_HandAlpha;
	bool  m_AlphaUpdate;
	bool m_PatternStop;

	int m_LaserCount;
	int m_LaserCountMax;
	
	//기본위치
	Vector3 m_BasicWorldPos;
	bool m_EffectEndStart;
	bool m_EffectEnd;
	float m_EffectEndTimer;

	bool m_SpawnEnd;
	float m_HitTimer;
public:
	void EffectEnd()
	{
		m_EffectEnd = true;
	}
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
	void SetStatus(const std::string& Name);
	void AttackSword(float DeltaTime);
	void AttackBullet(float DeltaTime);
	void AttackLaser(float DeltaTime);
public:
	void EffectEndUpdate(float DeltaTime);
	void AlphaUpdate(float DeltaTime);
	void PatternUpdate(float DeltaTime);
public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);
	void CollisionBossSpawnBegin(const HitResult& result, CCollider* Collider);
	
public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
};


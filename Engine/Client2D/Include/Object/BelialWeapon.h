#pragma once
#include "Enemy.h"
class CBelialWeapon :
	public CEnemy
{
	friend class CScene;

protected:
	CBelialWeapon();
	CBelialWeapon(const CBelialWeapon& obj);
	virtual ~CBelialWeapon();
private:
	bool m_StartAttack;
	bool m_Attacking;
	bool m_TextureUpdate;
	float m_AttackTimer;
	float m_AttackTimerMax;
	class CBelial* m_Belial;
	class CBelialWeaponCharge* m_Charge;
	float m_AcitveTime;
	Vector3 m_TargetMove;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialWeapon* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	void SetTarget();
	void SetBelial(class CBelial* Belial);
	void SetCharge(class CBelialWeaponCharge* Charge);
	void SetAttackTimerMax(float Timer)
	{
		m_AttackTimerMax = Timer;
	}
	void SetHorizontalReverse2DEnable(bool Enable);
public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
};


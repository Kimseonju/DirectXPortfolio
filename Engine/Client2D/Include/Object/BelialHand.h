#pragma once
#include "Enemy.h"
class CBelialHand :
	public CEnemy
{
	friend class CScene;

protected:
	CBelialHand();
	CBelialHand(const CBelialHand& obj);
	virtual ~CBelialHand();
	bool m_Attacking;
	class CBelial* m_Belial;
	bool m_AttackMove;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialHand* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	bool GetHorizontalReverse2DEnable();
	void SetBelial(class CBelial* Belial);
	bool Attack();
	void SetOpaacity(float Opacity);
	void SetHorizontalReverse2DEnable(bool Enable);
	CMaterial* GetMaterial(int Index=0);
public:
	virtual void CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
};


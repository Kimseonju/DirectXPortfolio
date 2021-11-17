#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
class CHPFairy :
	public CGameObject
{
	friend class CScene;

protected:
	CHPFairy();
	CHPFairy(const CHPFairy& obj);
	virtual ~CHPFairy();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CAnimation2D> m_Animation2D;
protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CHPFairy* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);

};

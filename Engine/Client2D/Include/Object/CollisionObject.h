#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include <Component/ColliderBox2D.h>

class CCollisionObject :
	public CGameObject
{
	friend class CScene;

protected:
	CCollisionObject();
	CCollisionObject(const CCollisionObject& obj);
	virtual ~CCollisionObject();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_Animation2D;
	CSharedPtr<CColliderBox2D> m_Body;
	float m_Speed;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCollisionObject* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);
};


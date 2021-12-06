#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
class CFirefly :
	public CGameObject
{
	friend class CScene;

protected:
	CFirefly();
	CFirefly(const CFirefly& obj);
	virtual ~CFirefly();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSpriteComponent> m_SpriteBlend;
	CSharedPtr<CColliderBox2D> m_Collider2D;
protected:
	Vector2 m_NextPos;
	Vector2 m_OldPos;
	float m_MoveTimer;
public:
	void SetOldPos(const Vector2 OldPos)
	{
		m_OldPos = OldPos;
	}
	void SetNextPos(const Vector2 NextPos)
	{
		m_NextPos = NextPos;
	}
public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CFirefly* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);

};

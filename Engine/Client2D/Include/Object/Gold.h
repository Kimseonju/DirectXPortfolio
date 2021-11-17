#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
class CGold :
	public CGameObject
{
	friend class CScene;

protected:
	CGold();
	CGold(const CGold& obj);
	virtual ~CGold();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2DHorizon;
	CSharedPtr<CColliderBox2D> m_Collider2DVertical;
	CSharedPtr<CAnimation2D> m_Animation2D;
	CSharedPtr<CRigidBodyComponent> m_Body;
	bool m_WallCol;
protected:
	bool m_Open;
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGold* Clone();
	void CollisionHorizonBegin(const HitResult& result, CCollider* Collider);
	void CollisionHorizonMiddle(const HitResult& result, CCollider* Collider);
	void CollisionHorizonEnd(const HitResult& result, CCollider* Collider);
	void CollisionVerticalBegin(const HitResult& result, CCollider* Collider);
	void CollisionVerticalMiddle(const HitResult& result, CCollider* Collider);
	void CollisionVerticalEnd(const HitResult& result, CCollider* Collider);
	//Ãæµ¹
	void ColDirHorizon(float Angle, CCollider* Col);
	void ColDirVertical(float Angle, CCollider* Col);

	void Drop(float Angle, float Power);
};

#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
class CShopNPC :
	public CGameObject
{
	friend class CScene;

protected:
	CShopNPC();
	CShopNPC(const CShopNPC& obj);
	virtual ~CShopNPC();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CAnimation2D> m_Animation2D;
	class CKeyboardUIObject* m_KeyUIObject;
protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CShopNPC* Clone();
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
};

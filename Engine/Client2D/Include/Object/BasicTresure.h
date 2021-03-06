#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
class CBasicTresure :
	public CGameObject
{
	friend class CScene;

protected:
	CBasicTresure();
	CBasicTresure(const CBasicTresure& obj);
	virtual ~CBasicTresure();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CAnimation2D> m_Animation2D;
	CSharedPtr<CRigidBodyComponent> m_Body;
	class CKeyboardUIObject* m_KeyUIObject;
protected:
	bool m_Open;
public:

public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBasicTresure* Clone();
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
	void ColDirStart(float Angle, CCollider* Col);
};

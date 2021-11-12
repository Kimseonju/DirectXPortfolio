#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include <Component/ParticleSystemComponent.h>
class CMainDoor :
	public CGameObject
{
	friend class CScene;

protected:
	CMainDoor();
	CMainDoor(const CMainDoor& obj);
	virtual ~CMainDoor();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_DoorCollider2D;
	CSharedPtr<CAnimation2D> m_Animation2D;
	class CKeyboardUIObject* m_KeyUIObject;
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
	virtual CMainDoor* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
	void StartDoor();
	void EndDoor();
};

#pragma once
#include <GameObject.h>
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../BasicStatus.h"
#include "../GlobalValue.h"
class CBelialDeadMouth :
	public CGameObject
{
	friend class CScene;

protected:
	CBelialDeadMouth();
	CBelialDeadMouth(const CBelialDeadMouth& obj);
	virtual ~CBelialDeadMouth();
private:

	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CRigidBodyComponent> m_Body;
	bool m_Rotation;
	float m_RotationTimer;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialDeadMouth* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void CollisionBegin(const HitResult& result, CCollider* Collider);
	virtual void CollisionMiddle(const HitResult& result, CCollider* Collider);
	virtual void CollisionEnd(const HitResult& result, CCollider* Collider);
	void ColDirStart(float Angle, CCollider* Col);
	void ColDirMiddle(float Angle, CCollider* Col);
	//Ãæµ¹End
	void ColDirEnd(CCollider* Col);
};


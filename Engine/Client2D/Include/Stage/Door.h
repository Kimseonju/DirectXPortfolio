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
class CDoor :
	public CGameObject
{
	friend class CScene;

protected:
	CDoor();
	CDoor(const CDoor& obj);
	virtual ~CDoor();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_DoorCollider2D;
	CSharedPtr<CColliderBox2D> m_NextStageCollider2D;
	CSharedPtr<CParticleSystemComponent> m_Particle;
	CSharedPtr<CAnimation2D> m_Animation2D;
	
protected:
	Object_Dir m_Dir;
	Vector2    m_MapPos;
	bool m_Open;
public:
	

	void SetDir(Object_Dir Dir)
	{
		m_Dir = Dir;
	}
	
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDoor* Clone();
	virtual void Animation2DNotify(const std::string& Name);
	void testDoorOnOff(float DeltaTime);
	void CollisionBegin(const HitResult& result, CCollider* Collider);

};

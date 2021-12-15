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
class CBelialBackParticle :
	public CGameObject
{
	friend class CScene;

protected:
	CBelialBackParticle();
	CBelialBackParticle(const CBelialBackParticle& obj);
	virtual ~CBelialBackParticle();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CParticleSystemComponent> m_Particle;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialBackParticle* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

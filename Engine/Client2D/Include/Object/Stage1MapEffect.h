#pragma once

#include "GameObject.h"
#include "Component/ParticleSystemComponent.h"

class CStage1MapEffect :
	public CGameObject
{
	friend class CScene;

protected:
	CStage1MapEffect();
	CStage1MapEffect(const CStage1MapEffect& obj);
	virtual ~CStage1MapEffect();

protected:
	CSharedPtr<CParticleSystemComponent> m_Particle;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CStage1MapEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

#pragma once

#include "GameObject.h"
#include "Component/ParticleSystemComponent.h"
#include "../GlobalValue.h"

class CDoorEffect :
	public CGameObject
{
	friend class CScene;

protected:
	CDoorEffect();
	CDoorEffect(const CDoorEffect& obj);
	virtual ~CDoorEffect();

protected:
	CSharedPtr<CParticleSystemComponent> m_Particle;
public:
	
	
public:

	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDoorEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	void SetDir(Object_Dir Dir);
	void SetRange(const Vector3& Range);
	void SetRange(float x, float y, float z);
};

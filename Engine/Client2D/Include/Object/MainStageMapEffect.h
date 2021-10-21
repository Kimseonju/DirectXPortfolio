#pragma once

#include "GameObject.h"
#include "Component/ParticleSystemComponent.h"
#include "../GlobalValue.h"

class CMainStageMapEffect :
	public CGameObject
{
	friend class CScene;

protected:
	CMainStageMapEffect();
	CMainStageMapEffect(const CMainStageMapEffect& obj);
	virtual ~CMainStageMapEffect();

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
	virtual CMainStageMapEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	void SetDir(Effect_Dir Dir);
	void SetRange(const Vector3& Range);
	void SetRange(float x, float y, float z);
};

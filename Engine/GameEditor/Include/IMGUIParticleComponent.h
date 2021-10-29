#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIParticleComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIParticleComponent();
	virtual ~CIMGUIParticleComponent();

private:

public:
	void InfoUpdate(CGameObject* Object);
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	/*
	
	CSharedPtr<CParticleSystem> m_Particle;
	std::vector<class CStructuredBuffer*>   m_vecBuffer;
	CSharedPtr<CMesh>                       m_Mesh;
	CSharedPtr<CParticleUpdateShader>		m_UpdateShader;
	CSharedPtr<CShader>                     m_RenderShader;
	CParticleConstantBuffer* m_CBuffer;
	ParticleInfo							m_ParticleInfo;
	ParticleInfoShared						m_ParticleInfoShare;
	float									m_SpawnTime;
	float									m_SpawnTimeMax;
	class CStructuredBuffer* m_CopyBuffer;
	ParticleInfo	m_Info[1000];
	*/
public:

};

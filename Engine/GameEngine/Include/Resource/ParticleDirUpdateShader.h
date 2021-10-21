#pragma once
#include "ParticleUpdateShader.h"
//고정된방향으로 날라가는 계산셰이더
class CParticleDirUpdateShader :
	public CParticleUpdateShader
{
	friend class CShaderManager;

protected:
	CParticleDirUpdateShader();
	virtual ~CParticleDirUpdateShader();

public:
	virtual bool Init();
};


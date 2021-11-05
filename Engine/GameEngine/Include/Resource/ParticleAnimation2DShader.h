#pragma once
#include "ParticleUpdateShader.h"
//고정된방향으로 날라가는 계산셰이더
class CParticleAnimation2DShader :
	public CParticleUpdateShader
{
	friend class CShaderManager;

protected:
	CParticleAnimation2DShader();
	virtual ~CParticleAnimation2DShader();

public:
	virtual bool Init();
};


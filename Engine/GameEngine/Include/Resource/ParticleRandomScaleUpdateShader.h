#pragma once
#include "ParticleUpdateShader.h"
//고정된방향으로 날라가는 계산셰이더
class CParticleRandomScaleUpdateShader :
	public CParticleUpdateShader
{
	friend class CShaderManager;

protected:
	CParticleRandomScaleUpdateShader();
	virtual ~CParticleRandomScaleUpdateShader();

public:
	virtual bool Init();
};


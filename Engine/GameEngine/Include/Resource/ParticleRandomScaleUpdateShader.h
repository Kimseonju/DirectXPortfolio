#pragma once
#include "ParticleUpdateShader.h"
//�����ȹ������� ���󰡴� �����̴�
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


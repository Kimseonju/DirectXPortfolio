#pragma once
#include "ParticleUpdateShader.h"
//�����ȹ������� ���󰡴� �����̴�
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


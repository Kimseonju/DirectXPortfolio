#pragma once
#include "ParticleUpdateShader.h"
//�����ȹ������� ���󰡴� �����̴�
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


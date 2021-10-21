
#include "ParticleRandomScaleUpdateShader.h"

CParticleRandomScaleUpdateShader::CParticleRandomScaleUpdateShader()
{
}

CParticleRandomScaleUpdateShader::~CParticleRandomScaleUpdateShader()
{
}

bool CParticleRandomScaleUpdateShader::Init()
{
    if (!LoadComputeShader(m_Name, "ParticleRandomScaleUpdate", TEXT("Particle.fx"), SHADER_PATH))
        return false;

    return true;
}

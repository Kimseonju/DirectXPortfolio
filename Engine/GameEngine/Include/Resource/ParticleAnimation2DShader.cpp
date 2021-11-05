
#include "ParticleAnimation2DShader.h"

CParticleAnimation2DShader::CParticleAnimation2DShader()
{
}

CParticleAnimation2DShader::~CParticleAnimation2DShader()
{
}

bool CParticleAnimation2DShader::Init()
{
    if (!LoadComputeShader(m_Name, "ParticleAnimation2D", TEXT("Particle.fx"), SHADER_PATH))
        return false;

    return true;
}

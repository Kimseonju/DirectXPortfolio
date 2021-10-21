
#include "ParticleDirUpdateShader.h"

CParticleDirUpdateShader::CParticleDirUpdateShader()
{
}

CParticleDirUpdateShader::~CParticleDirUpdateShader()
{
}

bool CParticleDirUpdateShader::Init()
{
    if (!LoadComputeShader(m_Name, "ParticleDirUpdate", TEXT("Particle.fx"), SHADER_PATH))
        return false;

    return true;
}

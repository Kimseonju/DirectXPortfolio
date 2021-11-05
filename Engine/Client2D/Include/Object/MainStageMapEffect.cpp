
#include "MainStageMapEffect.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
CMainStageMapEffect::CMainStageMapEffect()
{
}

CMainStageMapEffect::CMainStageMapEffect(const CMainStageMapEffect& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");
}

CMainStageMapEffect::~CMainStageMapEffect()
{
}



void CMainStageMapEffect::Start()
{
	CGameObject::Start();
}

bool CMainStageMapEffect::Init()
{
	CGameObject::Init();

	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("MainStageMapEffect");

	//m_Particle->SetRelativePos(Vector3(150.f, 75.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.05f);
	SetLifeTime(3.9f);
	SetLifeTimeCheck(false);
	m_Particle->SetTwinkleEnable(false);
	//m_Particle->SetGravityEnable(true);
	SetRootComponent(m_Particle);


	return true;
}

void CMainStageMapEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMainStageMapEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMainStageMapEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CMainStageMapEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CMainStageMapEffect* CMainStageMapEffect::Clone()
{
	return new CMainStageMapEffect(*this);
}

void CMainStageMapEffect::Animation2DNotify(const std::string& Name)
{
}

void CMainStageMapEffect::SetDir(Object_Dir Dir)
{

	switch (Dir)
	{
	case Object_Dir::Left:
	{
		m_Particle->SetMoveDir({ -1,0,0 });
		break;
	}
	case Object_Dir::Right:
	{
		m_Particle->SetMoveDir({ 1,0,0 });
		break;
	}
	case Object_Dir::Up:
	{

		m_Particle->SetMoveDir({ 0,1,0 });
		break;
	}
	case Object_Dir::Down:
	{

		m_Particle->SetMoveDir({ 0,-1,0 });
		break;
	}
	default:
		break;
	}

}

void CMainStageMapEffect::SetRange(const Vector3& Range)
{
	m_Particle->SetRange(Range);
}

void CMainStageMapEffect::SetRange(float x, float y, float z)
{
	m_Particle->SetRange(x, y, z);
}

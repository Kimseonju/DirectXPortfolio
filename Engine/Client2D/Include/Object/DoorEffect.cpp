
#include "DoorEffect.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CDoorEffect::CDoorEffect()
{
}

CDoorEffect::CDoorEffect(const CDoorEffect& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");
}

CDoorEffect::~CDoorEffect()
{
}



void CDoorEffect::Start()
{
	CGameObject::Start();
}

bool CDoorEffect::Init()
{
	CGameObject::Init();

	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");
	
	m_Particle->SetParticle("DoorParticle");

	m_Particle->SetRelativePos(Vector3(150.f, 75.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	//SetLifeTime(3.9f);
	SetLifeTimeCheck(false);
	m_Particle->SetTwinkleEnable(false);
	//m_Particle->SetGravityEnable(true);
	SetRootComponent(m_Particle);


	return true;
}

void CDoorEffect::Update(float DeltaTime)
{
 	CGameObject::Update(DeltaTime);
}

void CDoorEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CDoorEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDoorEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CDoorEffect* CDoorEffect::Clone()
{
	return new CDoorEffect(*this);
}

void CDoorEffect::Animation2DNotify(const std::string& Name)
{
}

void CDoorEffect::SetDir(Object_Dir Dir)
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

void CDoorEffect::SetRange(const Vector3& Range)
{
	m_Particle->SetRange(Range);
}

void CDoorEffect::SetRange(float x, float y, float z)
{
	m_Particle->SetRange(x, y, z);
}

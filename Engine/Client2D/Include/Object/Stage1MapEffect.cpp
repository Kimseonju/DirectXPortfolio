
#include "Stage1MapEffect.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CStage1MapEffect::CStage1MapEffect()
{
}

CStage1MapEffect::CStage1MapEffect(const CStage1MapEffect& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");
}

CStage1MapEffect::~CStage1MapEffect()
{
}



void CStage1MapEffect::Start()
{
	CGameObject::Start();
}

bool CStage1MapEffect::Init()
{
	CGameObject::Init();

	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("StageMapParticle");

	//m_Particle->SetRelativePos(Vector3(150.f, 75.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.05f);
	m_Particle->SetTwinkleEnable(true);

	CSharedPtr<CMaterial>   Mtrl = m_Particle->GetMaterial(0);
	Mtrl->SetTransparency(true, true);
	//m_Particle->SetGravityEnable(true);
	SetRootComponent(m_Particle);


	return true;
}

void CStage1MapEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CStage1MapEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CStage1MapEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CStage1MapEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CStage1MapEffect* CStage1MapEffect::Clone()
{
	return new CStage1MapEffect(*this);
}

void CStage1MapEffect::Animation2DNotify(const std::string& Name)
{
}
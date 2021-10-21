
#include "BossDieEffect.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CBossDieEffect::CBossDieEffect()
{
}

CBossDieEffect::CBossDieEffect(const CBossDieEffect& obj) :
	CGameObject(obj)
{
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");
}

CBossDieEffect::~CBossDieEffect()
{
}
void CBossDieEffect::Start()
{
	CGameObject::Start();
}

bool CBossDieEffect::Init()
{
	CGameObject::Init();

	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("DoorEffect");

	//m_Particle->SetRelativePos(Vector3(150.f, 75.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.05f);
	SetLifeTime(3.9f);
	SetLifeTimeCheck(false);
	//m_Particle->SetGravityEnable(true);
	SetRootComponent(m_Particle);


	return true;
}

void CBossDieEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBossDieEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossDieEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBossDieEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBossDieEffect* CBossDieEffect::Clone()
{
	return new CBossDieEffect(*this);
}

void CBossDieEffect::Animation2DNotify(const std::string& Name)
{
}
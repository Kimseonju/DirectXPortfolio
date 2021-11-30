
#include "BossDieParticle.h"
#include <Input.h>
#include "BossDieEffectLast.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
CBossDieParticle::CBossDieParticle():
	m_SoundTimer(0.f),
	m_SoundTimerMax(0.2f),
	m_Effect(false)
{
}

CBossDieParticle::CBossDieParticle(const CBossDieParticle& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");

}

CBossDieParticle::~CBossDieParticle()
{
}

void CBossDieParticle::Start()
{
	CGameObject::Start();

}

bool CBossDieParticle::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");


	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(0.f, 0.f, 0.f);
	m_Sprite->AddChild(m_Particle);

	m_Particle->SetParticle("BossDieParticle");
	m_Particle->SetRelativePos(Vector3(0.f, 0.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	m_Particle->SetTwinkleEnable(false);
	m_Particle->SetAnimation2DEnable(true);
	m_Particle->SetAnimation2DCount(12);
	Vector2 Size;
	Size.x = m_Particle->GetMaterial(0)->GetMaterialTextureInfo()->pTexture->GetWidth();
	Size.y = m_Particle->GetMaterial(0)->GetMaterialTextureInfo()->pTexture->GetHeight();
	m_Particle->SetAnimation2DSize(Size);
	m_Particle->SetAnimation2DPlayRate(0.05f);
	m_Particle->SetRender2DType(Render_Type_2D::RT2D_Particle);
	//m_Particle->SetParticle("DoorParticle");


	return true;
}

void CBossDieParticle::Update(float DeltaTime)
{
 	CGameObject::Update(DeltaTime);
	m_LifeTime += DeltaTime;
	if (m_LifeTime > 5.f)
	{
		m_Effect = true;
		CBossDieEffectLast* Effect = m_pScene->SpawnObject<CBossDieEffectLast>("BossDieEffect");
		Effect->SetWorldPos(GetWorldPos());
		Effect->SetBelial(m_Belial);
		Active(false);
	}
	m_SoundTimer += DeltaTime;
	if (m_SoundTimer >= m_SoundTimerMax)
	{
		m_SoundTimer -= m_SoundTimerMax;
		m_pScene->GetResource()->FindSound("EnemyDie")->Play();
	}
}

void CBossDieParticle::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossDieParticle::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBossDieParticle::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBossDieParticle* CBossDieParticle::Clone()
{
	return new CBossDieParticle(*this);
}

void CBossDieParticle::Animation2DNotify(const std::string& Name)
{
}


#include "BelialBackParticle.h"
#include <Input.h>
#include "BossDieEffectLast.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
CBelialBackParticle::CBelialBackParticle()
{
}

CBelialBackParticle::CBelialBackParticle(const CBelialBackParticle& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");

}

CBelialBackParticle::~CBelialBackParticle()
{
}

void CBelialBackParticle::Start()
{
	CGameObject::Start();

}

bool CBelialBackParticle::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");


	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(0.f, 0.f, 0.f);
	m_Sprite->AddChild(m_Particle);

	m_Particle->SetParticle("BossBackParticle");

	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	m_Particle->SetTwinkleEnable(false);
	m_Particle->SetAnimation2DEnable(true);
	m_Particle->SetAnimation2DCount(8);
	m_Particle->SetRender2DType(Render_Type_2D::RT2D_Back1);
	Vector2 Size;
	Size.x = (float)m_Particle->GetMaterial(0)->GetMaterialTextureInfo()->pTexture->GetWidth();
	Size.y = (float)m_Particle->GetMaterial(0)->GetMaterialTextureInfo()->pTexture->GetHeight();
	m_Particle->SetAnimation2DSize(Size);
	m_Particle->SetAnimation2DPlayRate(0.1f);


	return true;
}

void CBelialBackParticle::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBelialBackParticle::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelialBackParticle::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialBackParticle::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialBackParticle* CBelialBackParticle::Clone()
{
	return new CBelialBackParticle(*this);
}

void CBelialBackParticle::Animation2DNotify(const std::string& Name)
{
}

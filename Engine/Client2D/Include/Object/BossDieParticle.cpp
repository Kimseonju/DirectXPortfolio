
#include "BossDieParticle.h"
#include <Input.h>
CBossDieParticle::CBossDieParticle()
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
	m_Sprite->SetWorldScale(66.f, 20.f, 0.f);
	CMaterial* SpriteMtrl =m_Sprite->GetMaterial(0);
	SpriteMtrl->AddTexture("PlayerTex", TEXT("teemo.png"));
	m_Sprite->AddChild(m_Particle);
	
	m_Particle->SetParticle("BossDieParticle");
	//m_Particle->SetParticle("DoorParticle");

	m_Particle->SetRelativePos(Vector3(0.f, -30.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	//SetLifeTime(3.9f);
	SetLifeTimeCheck(false);
	m_Particle->SetTwinkleEnable(false);
	m_Particle->SetAnimation2DEnable(true);
	m_Particle->SetAnimation2DCount(12);
	Vector2 Size;
	Size.x = m_Particle->GetMaterial(0)->GetMaterialTextureInfo()->pTexture->GetWidth();
	Size.y = m_Particle->GetMaterial(0)->GetMaterialTextureInfo()->pTexture->GetHeight();
	m_Particle->SetAnimation2DSize(Size);
	m_Particle->SetAnimation2DPlayRate(0.1f);
	return true;
}

void CBossDieParticle::Update(float DeltaTime)
{
 	CGameObject::Update(DeltaTime);
	
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

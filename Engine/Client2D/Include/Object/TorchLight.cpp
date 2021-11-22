#include "TorchLight.h"
#include <Input.h>
#include "Player.h"
CTorchLight::CTorchLight()
{
}

CTorchLight::CTorchLight(const CTorchLight& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CTorchLight::~CTorchLight()
{
}

void CTorchLight::Start()
{
	CGameObject::Start();

}

bool CTorchLight::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_SpriteBlend= CreateSceneComponent<CSpriteComponent>("SpriteBlend");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_SpriteBlend);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(20.f, 30.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("Torch");

	m_SpriteBlend->SetPivot(0.5f, 0.5f, 0.f);
	m_SpriteBlend->SetWorldScale(100.f, 100.f, 0.f);


	CMaterial* Material= m_SpriteBlend->GetMaterial(0);
	
	Material->AddTexture("torchRight", TEXT("object/torch/torchRight.png"));
	Material->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	Material->SetEmissiveColor(1.f, 1.f, 1.f, 1.f);
	//Material->SetOpacity(0.51f);
	//Material->SetTransparency(true);
	//Material->DistortionEnable(true);
	
	//Material->AddTexture("TorchLightt", TEXT("object/torch/torchEffect.png"));

	return true;
}

void CTorchLight::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	CPlayer* Player = CGlobalValue::MainPlayer;
	if (Player)
	{
		SetWorldPos(Player->GetWorldPos());
	}
}

void CTorchLight::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTorchLight::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CTorchLight::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CTorchLight* CTorchLight::Clone()
{
	return new CTorchLight(*this);
}

void CTorchLight::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

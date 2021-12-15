#include "BossTorchLight.h"
#include <Input.h>
#include "Player.h"
#include <Render/RenderManager.h>
#include <Scene/Scene.h>
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
CBossTorchLight::CBossTorchLight()
{
}

CBossTorchLight::CBossTorchLight(const CBossTorchLight& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CBossTorchLight::~CBossTorchLight()
{
}

void CBossTorchLight::Start()
{
	CGameObject::Start();

}

bool CBossTorchLight::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_SpriteBlend = CreateSceneComponent<CSpriteComponent>("SpriteBlend");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_SpriteBlend);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(20.f, 30.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("Torch");

	m_SpriteBlend->SetPivot(0.5f, 0.5f, 0.f);
	m_SpriteBlend->SetWorldScale(100.f, 100.f, 0.f);

	CMaterial* Material = m_SpriteBlend->GetMaterial(0);

	Material->AddTexture("torchEffect", TEXT("object/torch/torchEffect6.png"));
	//º¸½º¿ë
	Material->SetBaseColor(255.f /255.f, 0.f / 255.f, 255.f / 255.f, 80.f / 255.f);
	//Material->SetBaseColor(227.f / 255.f, 79.f / 255.f, 64.f / 255.f, 140.f / 255.f);
	Material->SetTransparency(true, true);

	//Material->AddTexture("TorchLightt", TEXT("object/torch/torchEffect.png"));

	return true;
}

void CBossTorchLight::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	//CPlayer* Player = CGlobalValue::MainPlayer;
	//if (Player)
	//{
	//	SetWorldPos(Player->GetWorldPos());
	//}
}

void CBossTorchLight::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossTorchLight::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBossTorchLight::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);

	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();



	CRenderManager::GetInst()->AddTouchLight(GetWorldPos(), m_RootComponent->GetWorldMatrix(), Vector4(1.f, 1.f, 1.f, 1.f));
}

void CBossTorchLight::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBossTorchLight* CBossTorchLight::Clone()
{
	return new CBossTorchLight(*this);
}

void CBossTorchLight::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}


#include "Bird.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include <Device.h>
#include "../../Animation2D/BirdAnimation2D.h"
#include <Component/Transform.h>
CBird::CBird() :
	m_Speed(200)
{
}

CBird::CBird(const CBird& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBird::~CBird()
{
}

void CBird::Start()
{
	CGameObject::Start();
}

bool CBird::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(48.f, 32.f, 1.f);
	m_Sprite->SetRelativePos(0.f, 0.f, 1.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	//m_Sprite->GetTransform()->SetDefaultZ(0.3f);
	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture("BackCloud", TEXT("TitleScene/BackCloud.png"));

	m_Sprite->CreateAnimation2D<CBirdAnimation2D>();

	m_Animation2D = m_Sprite->GetAnimation2D();

	return true;
}

void CBird::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector3 Pos = m_Sprite->GetRelativePos();
	if (Pos.x > 1400.f)
	{
		Pos.x -= 1700.f;
	}
	Pos.x += m_Speed * DeltaTime;
	m_Sprite->SetRelativePos(Pos);
}

void CBird::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBird::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBird::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBird* CBird::Clone()
{
	return new CBird(*this);
}

#include "HPFairy.h"
#include <Input.h>
CHPFairy::CHPFairy() 
{
}

CHPFairy::CHPFairy(const CHPFairy& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CHPFairy::~CHPFairy()
{
}

void CHPFairy::Start()
{
	CGameObject::Start();

}

bool CHPFairy::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Collider2D);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(20.f, 20.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("HPFairy");

	m_Collider2D->SetCollisionProfile("Object");

	m_Collider2D->AddCollisionCallbackFunction<CHPFairy>(Collision_State::Begin, this,
		&CHPFairy::CollisionBegin);


	m_Collider2D->SetExtent(10.f, 10.f);

	return true;
}

void CHPFairy::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CHPFairy::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CHPFairy::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CHPFairy::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CHPFairy* CHPFairy::Clone()
{
	return new CHPFairy(*this);
}

void CHPFairy::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		CPlayer* Player = CGlobalValue::MainPlayer;
		//플레이어 HP 증가 , 사운드 재생
		Active(false);
	}
}

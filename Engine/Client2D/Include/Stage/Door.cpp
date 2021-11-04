
#include "Door.h"
#include <Input.h>
CDoor::CDoor() 
{
	Enable(false);
}

CDoor::CDoor(const CDoor& obj) 
{
	m_DoorCollider2D = (CColliderBox2D*)FindSceneComponent("DoorCollider2D");
	m_NextStageCollider2D = (CColliderBox2D*)FindSceneComponent("NextStageCollider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Particle = (CParticleSystemComponent*)FindSceneComponent("Particle");

}

CDoor::~CDoor()
{
}

void CDoor::Start()
{
}

bool CDoor::Init()
{
	m_DoorCollider2D = CreateSceneComponent<CColliderBox2D>("DoorCollider2D");
	m_NextStageCollider2D = CreateSceneComponent<CColliderBox2D>("NextStageCollider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("DoorParticle");

	m_Particle->SetRelativePos(Vector3(0.f, -20.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	//SetLifeTime(3.9f);
	SetLifeTimeCheck(false);
	m_Particle->SetTwinkleEnable(false);
	//m_Particle->SetGravityEnable(true);
	SetRootComponent(m_Particle);


	SetRootComponent(m_Sprite);

	m_DoorCollider2D->SetCollisionProfile("T");
	m_DoorCollider2D->AddCollisionCallbackFunction<CDoor>(Collision_State::Begin, this,
		&CDoor::CollisionBegin);
	m_DoorCollider2D->SetExtent(50.f, 50.f);

	m_DoorCollider2D->SetCollisionProfile("Tile_Nopass");
	m_DoorCollider2D->AddCollisionCallbackFunction<CDoor>(Collision_State::Begin, this,
		&CDoor::CollisionBegin);
	m_DoorCollider2D->SetExtent(50.f, 50.f);
	m_Sprite->AddChild(m_DoorCollider2D);
	m_Sprite->AddChild(m_Particle);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();

	m_Animation2D->AddAnimationSequence2D("DoorOpen", false);
	m_Animation2D->AddAnimationSequence2D("DoorClose", false);
	m_Animation2D->AddAnimationSequence2D("DoorIdle", true);
	CInput::GetInst()->AddKeyCallback<CDoor>("Attack", KT_Down, this, &CDoor::testDoorOnOff);
	return true;
}

void CDoor::Update(float DeltaTime)
{
	if (m_Animation2D->GetFrameEnd())
	{
		if (m_Animation2D->GetCurrentSequenceName() == "DoorOpen")
		{
			m_Animation2D->ChangeAnimation("DoorIdle");
		}
		else
		{

		}
	}
}

void CDoor::PostUpdate(float DeltaTime)
{
}

void CDoor::Collision(float DeltaTime)
{
}

void CDoor::Render(float DeltaTime)
{
}

CDoor* CDoor::Clone()
{
	return new CDoor(*this);
}

void CDoor::Animation2DNotify(const std::string& Name)
{
}

void CDoor::testDoorOnOff(float DeltaTime)
{
	m_Open = !m_Open;
	if (m_Open)
	{
		m_Animation2D->ChangeAnimation("DoorOpen");
		m_Particle->Enable(true);
	}
	else
	{
		m_Animation2D->ChangeAnimation("DoorClose");
		m_Particle->Enable(false);
	}
}

void CDoor::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

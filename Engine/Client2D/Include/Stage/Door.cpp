
#include "Door.h"
#include <Input.h>
CDoor::CDoor() 
{
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
	CGameObject::Start();

}

bool CDoor::Init()
{
	CGameObject::Init();
	m_DoorCollider2D = CreateSceneComponent<CColliderBox2D>("DoorCollider2D");
	m_NextStageCollider2D = CreateSceneComponent<CColliderBox2D>("NextStageCollider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("DoorParticle");

	m_Particle->SetRelativePos(Vector3(0.f, -30.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	//SetLifeTime(3.9f);
	SetLifeTimeCheck(false);
	m_Particle->SetTwinkleEnable(false);
	//m_Particle->SetGravityEnable(true);
	SetRootComponent(m_Particle);


	SetRootComponent(m_Sprite);

	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Sprite->SetWorldScale(66.f, 20.f, 0.f);

	m_Animation2D->AddAnimationSequence2D("DoorOpen", false);
	m_Animation2D->AddAnimationSequence2D("DoorClose", false);
	m_Animation2D->AddAnimationSequence2D("DoorIdle", true);

	m_NextStageCollider2D->SetCollisionProfile("NextStage");
	m_NextStageCollider2D->AddCollisionCallbackFunction<CDoor>(Collision_State::Begin, this,
		&CDoor::CollisionBegin_NextStage);
	m_NextStageCollider2D->SetExtent(33.f, 5.f);
	m_NextStageCollider2D->SetRelativePos(0, -30.f, 0.f);

	m_DoorCollider2D->SetCollisionProfile("Tile_Nopass");
	m_DoorCollider2D->AddCollisionCallbackFunction<CDoor>(Collision_State::Begin, this,
		&CDoor::CollisionBegin);
	m_DoorCollider2D->SetExtent(33.f, 10.f);
	m_Sprite->AddChild(m_DoorCollider2D);
	m_Sprite->AddChild(m_Particle);
	m_Sprite->AddChild(m_NextStageCollider2D);
	CInput::GetInst()->AddKeyCallback<CDoor>("Attack", KT_Down, this, &CDoor::testDoorOnOff);
	return true;
}

void CDoor::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Animation2D->GetFrameEnd())
	{
		if (m_Animation2D->GetCurrentSequenceName() == "DoorClose")
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
	CGameObject::PostUpdate(DeltaTime);
}

void CDoor::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CDoor::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
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
		m_DoorCollider2D->Enable(false);
	}
	else
	{
		m_Animation2D->ChangeAnimation("DoorClose");
		m_Particle->Enable(false);
		m_DoorCollider2D->Enable(true);
	}
}

void CDoor::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CDoor::CollisionBegin_NextStage(const HitResult& result, CCollider* Collider)
{
}

void CDoor::SetDir(Object_Dir Dir)
{
	switch (Dir)
	{
	case Object_Dir::Left:
	{
		m_Particle->SetMoveDir({ -1,0,0 });
		SetWorldRotation(0.f, 0.f, 90.f);
		break;
	}
	case Object_Dir::Right:
	{
		m_Particle->SetMoveDir({ 1,0,0 });
		SetWorldRotation(0.f, 0.f, 270.f);
		break;
	}
	case Object_Dir::Up:
	{

		m_Particle->SetMoveDir({ 0,1,0 });
		break;
	}
	case Object_Dir::Down:
	{

		m_Particle->SetMoveDir({ 0,-1,0 });
		SetWorldRotation(0.f, 0.f, 180.f);
		break;
	}
	m_Dir = Dir;
	}
}

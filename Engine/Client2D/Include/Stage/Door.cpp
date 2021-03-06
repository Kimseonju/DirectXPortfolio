
#include "Door.h"
#include <Input.h>
#include "StageManager.h"
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../UI/UIManager.h"
#include "../UI/FadeInOutUI.h"
#include <Scene/SceneResource.h>
CDoor::CDoor() :
	m_Open(true),
	m_StartInput(false)
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

void CDoor::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	if (m_Open)
	{
		if(!bEnable)
			m_DoorCollider2D->Enable(bEnable);
	}
	m_NextStageCollider2D->Enable(bEnable);
	m_Sprite->Enable(bEnable);
	m_Particle->Enable(bEnable);
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
	m_SpriteBody = CreateSceneComponent<CSpriteComponent>("SpriteBody");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Particle = CreateSceneComponent<CParticleSystemComponent>("Particle");

	m_Particle->SetParticle("DoorParticle");

	m_Particle->SetRelativePos(Vector3(0.f, -30.f, 0.f));
	m_Particle->SetPivot(0.5f, 0.5f, 0.f);
	m_Particle->SetSpawnTime(0.1f);
	m_Particle->SetTwinkleEnable(false);
	//m_Particle->SetGravityEnable(true);

	SetRootComponent(m_SpriteBody);

	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Sprite->SetWorldScale(66.f, 20.f, 0.f);

	m_Animation2D->AddAnimationSequence2D("DoorOpen", false);
	m_Animation2D->AddAnimationSequence2D("DoorClose", false);
	m_Animation2D->AddAnimationSequence2D("DoorIdle", true);

	m_NextStageCollider2D->SetCollisionProfile("Tile_Nopass");
	m_NextStageCollider2D->AddCollisionCallbackFunction<CDoor>(Collision_State::Begin, this,
		&CDoor::CollisionBegin_NextStage);
	m_NextStageCollider2D->SetExtent(33.f, 5.f);
	m_NextStageCollider2D->SetRelativePos(0, -5.f, 0.f);

	m_DoorCollider2D->SetCollisionProfile("Tile_Nopass");
	m_DoorCollider2D->AddCollisionCallbackFunction<CDoor>(Collision_State::Begin, this,
		&CDoor::CollisionBegin);
	m_DoorCollider2D->SetExtent(33.f, 10.f);

	m_SpriteBody->AddChild(m_Sprite);
	m_SpriteBody->AddChild(m_DoorCollider2D);
	m_SpriteBody->AddChild(m_Particle);
	m_SpriteBody->AddChild(m_NextStageCollider2D);
	m_DoorCollider2D->Enable(false);
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
			m_Sprite->Enable(false);
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

void CDoor::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	switch (m_DoorDir)
	{
	case Door_Dir::Door_Left:
	{	
		CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 16.f), Vector4(0.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);
		break;
	}
	case Door_Dir::Door_Right:
	{
		CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 16.f), Vector4(0.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);
		break;
	}
	case Door_Dir::Door_Up:
	{
		CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(16.f, 4.f), Vector4(0.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);
		break;
	}
	case Door_Dir::Door_Down:
	{
		CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(16.f, 4.f), Vector4(0.f / 255.f, 255.f / 255.f, 0.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);
		break;
	}
	}
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
	if (Name == "DoorSound")
	{
		m_pScene->GetResource()->FindSound("DoorOnOff")->Play();
	}
}

void CDoor::DoorOpenClose(bool Open)
{
	if (m_Open != Open || !m_StartInput)
	{
		m_StartInput = true;
		m_Open = Open;

		if (m_Open)
		{
			m_Sprite->Enable(true);
			m_Animation2D->ChangeAnimation("DoorOpen");
			m_Particle->Enable(true);
			m_DoorCollider2D->Enable(false);
			m_NextStageCollider2D->Enable(true);
		}
		else
		{
			m_Sprite->Enable(true);
			m_Animation2D->ChangeAnimation("DoorClose");
			m_Particle->Enable(false);
			m_DoorCollider2D->Enable(true);
			m_NextStageCollider2D->Enable(false);
		}
	}
}

void CDoor::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CDoor::CollisionBegin_NextStage(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		switch (m_DoorDir)
		{
		case Door_Dir::Door_Left:
		{
			CUIManager::GetInst()->GetFadeInOutUI()->StageMoveIn(Stage_Dir::LEFT);
			break;
		}
		case Door_Dir::Door_Right:
		{
			CUIManager::GetInst()->GetFadeInOutUI()->StageMoveIn(Stage_Dir::RIGHT);
			break;
		}
		case Door_Dir::Door_Up:
		{
			CUIManager::GetInst()->GetFadeInOutUI()->StageMoveIn(Stage_Dir::UP);
			break;
		}
		case Door_Dir::Door_Down:
		{
			CUIManager::GetInst()->GetFadeInOutUI()->StageMoveIn(Stage_Dir::DOWN);
			break;
		}
		}
	}



	
}

void CDoor::PlayerMove()
{
	Vector3 Pos = GetWorldPos();
	CGlobalValue::MainPlayer->StageMove();
	switch (m_DoorDir)
	{
	case Door_Dir::Door_Left:
	{
		Pos.x += 60.f;
		CGlobalValue::MainPlayer->SetWorldPos(Pos);
		break;
	}
	case Door_Dir::Door_Right:
	{
		Pos.x -= 60.f;
		CGlobalValue::MainPlayer->SetWorldPos(Pos);
		break;
	}
	case Door_Dir::Door_Up:
	{
		Pos.y -= 60.f;
		CGlobalValue::MainPlayer->SetWorldPos(Pos);
		break;
	}
	case Door_Dir::Door_Down:
	{
		Pos.y += 60.f;
		CGlobalValue::MainPlayer->SetWorldPos(Pos);
		break;
	}
	}
	CGlobalValue::MainPlayer->SetGravity(true);
}

void CDoor::SetDir(Door_Dir Dir)
{
	switch (Dir)
	{
	case Door_Dir::Door_Left:
	{
		m_Particle->SetMoveDir({ 1,0,0 });
		m_Particle->SetRelativeRotationZ(90.f);
		m_Particle->SetRelativePos(0.f, 5.f, 0.f);
		m_Sprite->SetRelativeRotationZ(90.f);
		m_DoorCollider2D->SetExtent(10.f, 33.f);
		m_NextStageCollider2D->SetExtent(10.f, 33.f);
		break;
	}
	case Door_Dir::Door_Right:
	{
		m_Particle->SetMoveDir({ -1,0,0 });
		m_Particle->SetRelativeRotationZ(270.f);
		m_Particle->SetRelativePos(0.f, 5.f, 0.f);

		m_Sprite->SetRelativeRotationZ(270.f);
		m_DoorCollider2D->SetExtent(10.f, 33.f);
		m_NextStageCollider2D->SetExtent(10.f, 33.f);
		break;
	}
	case Door_Dir::Door_Up:
	{

		m_Particle->SetMoveDir({ 0,-1,0 });
		m_Particle->SetRelativeRotationZ(0.f);
		m_Sprite->SetRelativeRotationZ(0.f);
		m_DoorCollider2D->SetExtent(33.f, 10.f);
		m_NextStageCollider2D->SetExtent(33.f, 10.f);
		break;
	}
	case Door_Dir::Door_Down:
	{
		m_Particle->SetMoveDir({ 0,1,0 });
		m_Particle->SetRelativeRotationZ(180.f);
		m_Sprite->SetRelativeRotationZ(180.f);
		m_DoorCollider2D->SetExtent(33.f, 10.f);
		m_NextStageCollider2D->SetExtent(33.f, 10.f);
		break;
	}
	}
	m_DoorDir = Dir;
}

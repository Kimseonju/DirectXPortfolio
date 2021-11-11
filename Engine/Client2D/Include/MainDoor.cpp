
#include "MainDoor.h"
#include <Input.h>
CMainDoor::CMainDoor()
{
}

CMainDoor::CMainDoor(const CMainDoor& obj)
{
	m_DoorCollider2D = (CColliderBox2D*)FindSceneComponent("DoorCollider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CMainDoor::~CMainDoor()
{
}

void CMainDoor::Start()
{
	CGameObject::Start();

}

bool CMainDoor::Init()
{
	CGameObject::Init();
	m_DoorCollider2D = CreateSceneComponent<CColliderBox2D>("DoorCollider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);

	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Sprite->SetWorldScale(70.f, 70.f, 0.f);

	m_Animation2D->AddAnimationSequence2D("MainDoorClose", false);
	m_Animation2D->AddAnimationSequence2D("MainDoorCloseIdle", false);
	m_Animation2D->AddAnimationSequence2D("MainDoorOpen", true);
	m_Animation2D->AddAnimationSequence2D("MainDoorOpenIdle", true);


	m_DoorCollider2D->SetCollisionProfile("InteractionInputKey");
	m_DoorCollider2D->AddCollisionCallbackFunction<CMainDoor>(Collision_State::Begin, this,
		&CMainDoor::CollisionBegin);
	m_DoorCollider2D->SetExtent(33.f, 10.f);
	m_Sprite->AddChild(m_DoorCollider2D);

	return true;
}

void CMainDoor::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Animation2D->GetFrameEnd())
	{
		if (m_Animation2D->GetCurrentSequenceName() == "MainDoorOpen")
		{
			m_Animation2D->ChangeAnimation("MainDoorOpenIdle");
		}
		else if(m_Animation2D->GetCurrentSequenceName() == "MainDoorClose")
		{
			m_Animation2D->ChangeAnimation("MainDoorCloseIdle");
		}
	}
}

void CMainDoor::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMainDoor::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CMainDoor::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CMainDoor* CMainDoor::Clone()
{
	return new CMainDoor(*this);
}


void CMainDoor::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CMainDoor::StartDoor()
{
	m_Animation2D->ChangeAnimation("MainDoorClose");
	m_DoorCollider2D->Enable(false);
}

void CMainDoor::EndDoor()
{
	m_Animation2D->ChangeAnimation("MainDoorOpen");
	m_DoorCollider2D->Enable(true);
}

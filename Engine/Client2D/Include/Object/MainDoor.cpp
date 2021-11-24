#include "MainDoor.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "../Stage/StageManager.h"
#include "../UI/UIManager.h"
#include "../UI/StageMap.h"
CMainDoor::CMainDoor():
	m_DoorCollider2D(nullptr),
	m_Open(false)
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

void CMainDoor::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	if (m_Open)
	{
		m_DoorCollider2D->Enable(bEnable);
	}
}

void CMainDoor::Active(bool bActive)
{
	CGameObject::Active(bActive);
	m_KeyUIObject->Active(bActive);
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
	m_Animation2D->AddAnimationSequence2D("MainDoorOpen", false);
	m_Animation2D->AddAnimationSequence2D("MainDoorOpenIdle", true);


	m_DoorCollider2D->SetCollisionProfile("InteractionInputKey");
	m_DoorCollider2D->AddCollisionCallbackFunction<CMainDoor>(Collision_State::Begin, this,
		&CMainDoor::CollisionBegin);
	m_DoorCollider2D->AddCollisionCallbackFunction<CMainDoor>(Collision_State::End, this,
		&CMainDoor::CollisionEnd);
	m_DoorCollider2D->SetExtent(33.f, 60.f);
	m_Sprite->AddChild(m_DoorCollider2D);



	m_KeyUIObject = m_pScene->SpawnObject<CKeyboardUIObject>("KeyUI_MainDoor");
	m_KeyUIObject->SetKey("F");
	m_KeyUIObject->SetWorldPos(GetWorldPos());
	m_KeyUIObject->Enable(false);

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
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(true);
		m_KeyUIObject->SetWorldPos(GetWorldPos());
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::InteractionInputKey)
	{
		if (CStageManager::GetInst()->IsBossStage())
		{
			//¿£µù
		}
		else
		{
			CStageManager::GetInst()->CreateBossStage();
			CUIManager::GetInst()->GetStageMap()->StageUpdate();
		}
	}
}

void CMainDoor::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	m_KeyUIObject->Enable(false);
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(false);
	}

}

void CMainDoor::StartDoor()
{
	if(m_DoorCollider2D)
		m_DoorCollider2D->Enable(false);
	m_Animation2D->ChangeAnimation("MainDoorClose");
	m_Open = false;
}

void CMainDoor::EndDoor()
{
	if(m_DoorCollider2D)
		m_DoorCollider2D->Enable(true);

	m_Animation2D->ChangeAnimation("MainDoorOpen");
	m_Open = true;
}

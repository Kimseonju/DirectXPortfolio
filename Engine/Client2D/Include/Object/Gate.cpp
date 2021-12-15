#include "Gate.h"
#include <Input.h>
#include "Player.h"
#include <Render/RenderManager.h>
#include <Scene/Scene.h>
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
#include "SpawnEffect.h"
#include "../UI/UIManager.h"
#include "KeyboardUIObject.h"
CGate::CGate():
	m_Spawn(false),
	m_KeyUIObject(nullptr)
{
}

CGate::CGate(const CGate& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CGate::~CGate()
{
}


void CGate::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_ColliderBox2D->Enable(bEnable);
}

void CGate::Start()
{
	CGameObject::Start();

	m_KeyUIObject->SetWorldPos(GetWorldPos());
	m_KeyUIObject->AddWorldPos(-0.f, 30.f, 0.f);
}

bool CGate::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_ColliderBox2D = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_ColliderBox2D);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(27.f, 31.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("Gate_Idle");
	m_Animation2D->AddAnimationSequence2D("Gate_In", false);


	m_ColliderBox2D->SetCollisionProfile("Object");
	m_ColliderBox2D->AddCollisionCallbackFunction<CGate>(Collision_State::Begin, this,
		&CGate::CollisionBegin);
	m_ColliderBox2D->AddCollisionCallbackFunction<CGate>(Collision_State::End, this,
		&CGate::CollisionEnd);

	m_ColliderBox2D->SetExtent(5.f, 5.f);

	m_KeyUIObject = m_pScene->SpawnObject<CKeyboardUIObject>("KeyUIObject");
	m_KeyUIObject->SetKey("F");
	m_KeyUIObject->SetWorldPos(GetWorldPos());
	m_KeyUIObject->AddWorldPos(0.f, 30.f, 0.f);
	m_KeyUIObject->Enable(false);
	return true;
}

void CGate::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	
}

void CGate::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CGate::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CGate::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);

	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();



	CRenderManager::GetInst()->AddTouchLight(GetWorldPos(), m_RootComponent->GetWorldMatrix(), Vector4(1.f, 1.f, 1.f, 1.f));
}

void CGate::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CGate* CGate::Clone()
{
	return new CGate(*this);
}

void CGate::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(true);
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::InteractionInputKey)
	{
		CUIManager::GetInst()->GetStageMap()->Enable(true);
		CUIManager::GetInst()->GetStageMap()->GateIn();
		//상점 UI시작
		//플레이어 키 다 잠금
	}
}

void CGate::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider == nullptr || result.DestCollider == nullptr)
		return;

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(false);
	}
}

void CGate::Animation2DNotify(const std::string& Name)
{
	if (Name == "Gate_InEnd")
	{
		CUIManager::GetInst()->GetFadeInOutUI()->StageGateIn(m_NextGateStagePos);
	}
}

void CGate::StageGateMove(Vector2 Pos)
{
	m_Animation2D->ChangeAnimation("Gate_In");
	m_NextGateStagePos = Pos;
	//이동되는위치를 마우스로 가져와야된다. UI를 터치시켜서 마우스에 다음 게이트가 있는 좌표를 저장시켜야된다.
	//CUIManager::GetInst()->GetFadeInOutUI()->StageGateIn();
}

void CGate::StageGateEnd()
{
	m_Spawn = true;
	CGameObject* Obj = m_pScene->SpawnObject<CSpawnEffect>("SpawnEffect");
	Obj->SetWorldPos(GetWorldPos());
	CGlobalValue::MainPlayer->SetWorldPos(GetWorldPos());
	m_Animation2D->ChangeAnimation("Gate_Idle");

}

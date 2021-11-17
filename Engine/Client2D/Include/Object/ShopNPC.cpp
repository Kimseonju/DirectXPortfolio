#include "ShopNPC.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
CShopNPC::CShopNPC()
{
}

CShopNPC::CShopNPC(const CShopNPC& obj)
{
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CShopNPC::~CShopNPC()
{
}

void CShopNPC::Start()
{
	CGameObject::Start();

}

bool CShopNPC::Init()
{
	CGameObject::Init();
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Collider2D);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(48.f, 48.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("Shop");

	m_Collider2D->SetCollisionProfile("Object");
	m_Collider2D->AddCollisionCallbackFunction<CShopNPC>(Collision_State::Begin, this,
		&CShopNPC::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CShopNPC>(Collision_State::Middle, this,
		&CShopNPC::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CShopNPC>(Collision_State::End, this,
		&CShopNPC::CollisionEnd);

	m_Collider2D->SetExtent(24.f, 24.f);



	m_KeyUIObject = m_pScene->SpawnObject<CKeyboardUIObject>("KeyUIObject");
	m_KeyUIObject->SetKey("F");
	m_KeyUIObject->SetWorldPos(GetWorldPos());
	m_KeyUIObject->AddWorldPos(-0.f, 30.f, 0.f);
	m_KeyUIObject->Enable(false);

	return true;
}

void CShopNPC::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CShopNPC::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CShopNPC::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CShopNPC::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CShopNPC* CShopNPC::Clone()
{
	return new CShopNPC(*this);
}


void CShopNPC::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(true);
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::InteractionInputKey)
	{
		//���� UI����
		//�÷��̾� Ű �� ���
	}

}
void CShopNPC::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CShopNPC::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider == nullptr || result.DestCollider == nullptr)
		return;

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(false);
	}
}
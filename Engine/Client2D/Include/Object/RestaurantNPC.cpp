#include "RestaurantNPC.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CRestaurantNPC::CRestaurantNPC():
	m_KeyUIObject(nullptr)
{
}

CRestaurantNPC::CRestaurantNPC(const CRestaurantNPC& obj)
{
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CRestaurantNPC::~CRestaurantNPC()
{
}
void CRestaurantNPC::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Collider2D->Enable(bEnable);
	m_Sprite->Enable(bEnable);
	if (!bEnable)
		m_KeyUIObject->Enable(false);
}

void CRestaurantNPC::Start()
{
	CGameObject::Start();
	m_KeyUIObject->SetWorldPos(GetWorldPos());
	m_KeyUIObject->AddWorldPos(-0.f, 30.f, 0.f);

}

bool CRestaurantNPC::Init()
{
	CGameObject::Init();
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_SpriteTavern = CreateSceneComponent<CSpriteComponent>("SpriteTavern");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_SpriteTavern);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back2);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(15.f, 23.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("Restaurant");

	m_SpriteTavern->SetRender2DType(Render_Type_2D::RT2D_Back1);
	m_SpriteTavern->SetRelativePos(-60.f, 35.f, 0.f);
	m_SpriteTavern->SetPivot(0.5f, 0.5f, 0.f);
	m_SpriteTavern->SetRelativeScale(198.f, 92.f, 0.f);
	CMaterial* Material =m_SpriteTavern->GetMaterial(0);
	Material->AddTexture("Tavern", TEXT("Villiage/Tavern.png"));

	m_Collider2D->SetCollisionProfile("Object");
	m_Collider2D->AddCollisionCallbackFunction<CRestaurantNPC>(Collision_State::Begin, this,
		&CRestaurantNPC::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CRestaurantNPC>(Collision_State::Middle, this,
		&CRestaurantNPC::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CRestaurantNPC>(Collision_State::End, this,
		&CRestaurantNPC::CollisionEnd);

	m_Collider2D->SetExtent(5.f, 5.f);



	m_KeyUIObject = m_pScene->SpawnObject<CKeyboardUIObject>("KeyUIObject");
	m_KeyUIObject->SetKey("F");
	m_KeyUIObject->Enable(false);

	return true;
}

void CRestaurantNPC::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CRestaurantNPC::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CRestaurantNPC::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CRestaurantNPC::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CRestaurantNPC* CRestaurantNPC::Clone()
{
	return new CRestaurantNPC(*this);
}


void CRestaurantNPC::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(true);
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::InteractionInputKey)
	{
		CUIManager::GetInst()->RestaurantUIOnOff();
		//상점 UI시작
		//플레이어 키 다 잠금
	}

}
void CRestaurantNPC::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CRestaurantNPC::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider == nullptr || result.DestCollider == nullptr)
		return;

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_KeyUIObject->Enable(false);
	}
}
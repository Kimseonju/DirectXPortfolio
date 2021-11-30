#include "ShopNPC.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
#include "../UI/MiniMap.h"
CShopNPC::CShopNPC() :
	m_KeyUIObject(nullptr)
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

void CShopNPC::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Collider2D->Enable(bEnable);
	m_Sprite->Enable(bEnable);
}

void CShopNPC::Start()
{
	CGameObject::Start();
	m_KeyUIObject->SetWorldPos(GetWorldPos());
}

bool CShopNPC::Init()
{
	CGameObject::Init();
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_SpriteObject = CreateSceneComponent<CSpriteComponent>("SpriteObject");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_SpriteObject);

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

	m_Collider2D->SetExtent(24.f, 48.f);

	m_SpriteObject->SetPivot(0.5f, 0.5f, 0.f);
	m_SpriteObject->SetRelativePos(70.f, -10.f, 0.f);
	m_SpriteObject->SetRelativeScale(101.f, 27.f, 0.f);
	CMaterial* Material=m_SpriteObject->GetMaterial(0);
	Material->AddTexture("InDungeonShop", TEXT("Villiage/InDungeonShop.png"));
	m_KeyUIObject = m_pScene->SpawnObject<CKeyboardUIObject>("KeyUIObject");
	m_KeyUIObject->SetKey("F");
	m_KeyUIObject->AddWorldPos(0.f, 60.f, 0.f);
	m_KeyUIObject->Enable(false);

	return true;
}

void CShopNPC::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	//CPlayer* Player = CGlobalValue::MainPlayer;
	//if (Player)
	//{
	//	SetWorldPos(Player->GetWorldPos());
	//}
}

void CShopNPC::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CShopNPC::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CShopNPC::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 4.f), Vector4(0.f / 255.f, 0.f / 255.f, 255.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);

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
		m_KeyUIObject->SetWorldPos(GetWorldPos());
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::InteractionInputKey)
	{
		//상점 UI시작
		//플레이어 키 다 잠금
		CUIManager::GetInst()->GetShopUI()->Enable(true);
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
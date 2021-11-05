
#include "CollisionObject.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include <Device.h>
#include <Component/Transform.h>
#include "Item.h"
#include "ShortSword.h"
CCollisionObject::CCollisionObject() :
	m_Speed(200),
	m_SpawnCount(0.f)
{
}

CCollisionObject::CCollisionObject(const CCollisionObject& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Body = (CColliderBox2D*)FindSceneComponent("Body");
}

CCollisionObject::~CCollisionObject()
{
}

void CCollisionObject::Start()
{
	CGameObject::Start();
}

bool CCollisionObject::Init()
{
	CGameObject::Init();

	m_Body = CreateSceneComponent<CColliderBox2D>("ObejctBody");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativePos(0.f, 0.f, 1.f);
	m_Sprite->AddChild(m_Body);
	m_Body->SetLine2D({ 0.f,0.f }, { 100.f,0.f });
	m_Body->SetCollisionProfile("Tile_Nopass");
	m_Body->AddCollisionCallbackFunction<CCollisionObject>(Collision_State::Begin, this,
			&CCollisionObject::CollisionBegin);
	return true;
}

void CCollisionObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	//m_SpawnCount += DeltaTime;
	//if (m_SpawnCount > 0.1f)
	//{
	//	m_SpawnCount -= 0.1f;
	//	CItem* Item=m_pScene->SpawnObject< CShortSword>("Spawn");
	//	Vector3 Pos = GetWorldPos();
	//	Pos.y += 40.f;
	//	
	//	Item->SetWorldPos(Pos);
 	//	Item->Drop((float)GetRandom(0, 180), 300.f);
	//	Item->Enable(true);
	//	Item->Drop();
	//
	//}
}

void CCollisionObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCollisionObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CCollisionObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CCollisionObject* CCollisionObject::Clone()
{
	return new CCollisionObject(*this);
}

void CCollisionObject::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	std::string strName=result.DestObject->GetName();
	std::string strName2 = GetName();

}

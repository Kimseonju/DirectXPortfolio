
#include "CollisionObject.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include <Device.h>
#include <Component/Transform.h>
CCollisionObject::CCollisionObject() :
	m_Speed(200)
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
	m_Body->SetLine2D({ 0.f,0.f }, { 5000.f,0.f });
	m_Body->SetCollisionProfile("Tile_Nopass");
	
	return true;
}

void CCollisionObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
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

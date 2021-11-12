
#include "ProgressBarObject.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "../GlobalValue.h"
#include "Player.h"
CProgressBarObject::CProgressBarObject() 
{
}

CProgressBarObject::CProgressBarObject(const CProgressBarObject& obj) :
	CGameObject(obj)
{
}

CProgressBarObject::~CProgressBarObject()
{
}

void CProgressBarObject::Start()
{
	CGameObject::Start();
}

bool CProgressBarObject::Init()
{
	CGameObject::Init();

	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_SpriteBack = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_SpriteBar= CreateSceneComponent<CSpriteComponent>("SpriteBar");
	SetRootComponent(m_SpriteBack);

	m_SpriteBack->SetRelativeScale(20.f, 5.f, 1.f);
	m_SpriteBar->SetRelativeScale(20.f, 5.f, 1.f);
	m_SpriteBar->AddRelativePos(0.f, -1.f, 0.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	CMaterial* material= m_SpriteBack->GetMaterial(0);
	material->AddTexture("Room", TEXT("object/door/openEffect.png"));
	material->SetBaseColor(0.f, 0.f, 0.f, 1.f);

	material = m_SpriteBar->GetMaterial(0);
	
	material->AddTexture("Room", TEXT("object/door/openEffect.png"));
	material->SetBaseColor(1.f, 0.f, 0.f, 1.f);


	m_Collider2D->SetExtent(50.f, 50.f);
	m_Collider2D->SetCollisionProfile("EnemyAttack");

	m_SpriteBack->AddChild(m_Collider2D);
	m_SpriteBack->AddChild(m_SpriteBar);

	return true;
}

void CProgressBarObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CProgressBarObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CProgressBarObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CProgressBarObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CProgressBarObject* CProgressBarObject::Clone()
{
	return new CProgressBarObject(*this);
}

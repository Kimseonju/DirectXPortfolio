
#include "PlayerAttack.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "../GlobalValue.h"
#include "Player.h"
CPlayerAttack::CPlayerAttack() :
	m_AttackTime(0.f),
	m_AttackTimeMax(0.1f)
{
}

CPlayerAttack::CPlayerAttack(const CPlayerAttack& obj) :
	CGameObject(obj)
{
	m_AttackTime = obj.m_AttackTime;
	m_AttackTimeMax = obj.m_AttackTimeMax;
}

CPlayerAttack::~CPlayerAttack()
{
}

void CPlayerAttack::Start()
{
	CGameObject::Start();
}

bool CPlayerAttack::Init()
{
	CGameObject::Init();

	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(0.f, 0.f, 1.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Collider2D->SetExtent(15.f, 15.f);
	m_Collider2D->SetCollisionProfile("PlayerAttack");

	m_Sprite->AddChild(m_Collider2D);

	return true;
}

void CPlayerAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_AttackTime += DeltaTime;
	if (m_AttackTime >= m_AttackTimeMax)
	{
		Active(false);
	}
}

void CPlayerAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPlayerAttack::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CPlayerAttack::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CPlayerAttack* CPlayerAttack::Clone()
{
	return new CPlayerAttack(*this);
}

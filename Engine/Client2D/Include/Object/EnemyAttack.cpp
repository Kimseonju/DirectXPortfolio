
#include "EnemyAttack.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "../GlobalValue.h"
#include "Player.h"
CEnemyAttack::CEnemyAttack() :
	m_AttackTime(0.f),
	m_AttackTimeMax(0.5f),
	m_Damage(1)
{
}

CEnemyAttack::CEnemyAttack(const CEnemyAttack& obj) :
	CGameObject(obj)
{
	m_AttackTime = 0.f;
	m_AttackTimeMax = 0.5f;
	m_Damage = 1;
}

CEnemyAttack::~CEnemyAttack()
{
}

void CEnemyAttack::Start()
{
	CGameObject::Start();
}

bool CEnemyAttack::Init()
{
	CGameObject::Init();

	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Collider2D->SetExtent(20.f, 20.f);
	m_Collider2D->SetCollisionProfile("EnemyAttack");

	m_Collider2D->AddCollisionCallbackFunction<CEnemyAttack>(Collision_State::Begin, this,
		&CEnemyAttack::CollisionBegin);
	m_Sprite->AddChild(m_Collider2D);

	return true;
}

void CEnemyAttack::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_AttackTime += DeltaTime;
	if (m_AttackTime >= m_AttackTimeMax)
	{
		Active(false);
	}
}

void CEnemyAttack::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEnemyAttack::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEnemyAttack::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEnemyAttack* CEnemyAttack::Clone()
{
	return new CEnemyAttack(*this);
}

void CEnemyAttack::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		CGlobalValue::MainPlayer->EnemyHit(m_Damage);
	}
}

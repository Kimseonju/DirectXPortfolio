#include "Banshee.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SmallSkelBow.h"

CBanshee::CBanshee() :
	m_PlayerFind(false),
	m_AttackTimer(0.f),
	m_AttackTimerMax(3.f)
{
	SetStatus("Banshee");
}

CBanshee::CBanshee(const CBanshee& obj) :
	CEnemy(obj)
{
}

CBanshee::~CBanshee()
{
}

void CBanshee::Start()
{
	CEnemy::Start();
	m_Body->SetGravity(false);
}

bool CBanshee::Init()
{
	CEnemy::Init();

	m_Collider2D->SetExtent(8.f, 10.f);
	m_AttackRangeCollider2D->SetExtent(7.f, 9.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	m_Sprite->SetWorldScale(20.f, 22.f, 0.f);
	m_Animation2D->SetIdleAnimation2D("BansheeIdle");
	m_Animation2D->SetMoveAnimation2D("BansheeIdle");
	m_Animation2D->SetAttackAnimation2D("BansheeAttack", false);
	m_Animation2D->ChangeIdleAnimation2D();


	return true;
}

void CBanshee::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
	m_AttackTimer += DeltaTime;

}

void CBanshee::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
}

void CBanshee::Collision(float DeltaTime)
{
	CEnemy::Collision(DeltaTime);
}

void CBanshee::Render(float DeltaTime)
{
	CEnemy::Render(DeltaTime);
}

CBanshee* CBanshee::Clone()
{
	return new CBanshee(*this);
}

void CBanshee::Animation2DNotify(const std::string& Name)
{
	if (Name == "Attack")
	{
		m_BansheeAttack = false;
	}
}

void CBanshee::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
	}
}

void CBanshee::AnimationFrameEnd(const std::string& Name)
{
}

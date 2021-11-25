#include "SmallSkel_Bow.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SmallSkelBow.h"
#include "Gold.h"
CSmallSkel_Bow::CSmallSkel_Bow() :
	m_PlayerFind(false)
{
	SetStatus("SmallSkel_Bow");
}

CSmallSkel_Bow::CSmallSkel_Bow(const CSmallSkel_Bow& obj) :
	CEnemy(obj)
{
}

CSmallSkel_Bow::~CSmallSkel_Bow()
{
}

void CSmallSkel_Bow::Start()
{
	CEnemy::Start();
}

bool CSmallSkel_Bow::Init()
{
	CEnemy::Init();

	m_Collider2D->SetExtent(5.f, 10.f);
	m_AttackRangeCollider2D->SetExtent(7.f, 9.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	m_Sprite->SetWorldScale(14.f, 19.f, 0.f);
	m_Animation2D->SetIdleAnimation2D("SmallEnemyIdle");
	m_Animation2D->ChangeIdleAnimation2D();
	m_Weapon = m_pScene->SpawnObject<CSmallSkelBow>("SmallSkelBow");
	m_Weapon->SetRelativePos(0.f, 0.f, 0.f);
	m_WeaponArm->PushObjectChild(m_Weapon);
	m_Status->SetMoveSpeed(50.f);
	m_Body->SetMoveSpeed(m_Status->GetMoveSpeed());

	return true;
}

void CSmallSkel_Bow::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
	if (m_Weapon->IsAttack())
	{
		return;
	}


	AddRelativePos(m_Body->GetMove());
}

void CSmallSkel_Bow::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
}

void CSmallSkel_Bow::Collision(float DeltaTime)
{
	CEnemy::Collision(DeltaTime);
}

void CSmallSkel_Bow::Render(float DeltaTime)
{
	CEnemy::Render(DeltaTime);
}

CSmallSkel_Bow* CSmallSkel_Bow::Clone()
{
	return new CSmallSkel_Bow(*this);
}

void CSmallSkel_Bow::Animation2DNotify(const std::string& Name)
{
}

void CSmallSkel_Bow::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
	}
}

void CSmallSkel_Bow::AnimationFrameEnd(const std::string& Name)
{
}

void CSmallSkel_Bow::DropGold()
{
	int DropCount = GetRandom(0, 4);
	for (int i = 0; i < DropCount; ++i)
	{
		CGold* Gold = m_pScene->SpawnObject<CGold>("Gold");
		Gold->SetWorldPos(GetWorldPos());
		Gold->AddWorldPos(0.f, 20.f, 0.f);
		Gold->Drop((float)GetRandom(0, 180), 300.f);
	}
}

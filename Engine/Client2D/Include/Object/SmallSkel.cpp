#include "SmallSkel.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"

CSmallSkel::CSmallSkel():
	m_PlayerFind(false)
{
	SetStatus("SmallSkel_Sword");
}

CSmallSkel::CSmallSkel(const CSmallSkel& obj) :
	CEnemy(obj)
{
}

CSmallSkel::~CSmallSkel()
{
}

void CSmallSkel::Start()
{
	CEnemy::Start();
}

bool CSmallSkel::Init()
{
	CEnemy::Init();

	m_Collider2DVertical->SetExtent(5.f, 10.f);
	m_AttackRangeCollider2D->SetExtent(7.f, 9.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	m_Sprite->SetWorldScale(100.f, 100.f,0.f);
	m_Animation2D->SetIdleAnimation2D("SmallEnemyIdle");
	m_Animation2D->SetMoveAnimation2D("SmallEnemyMove");
	m_Animation2D->SetAttackAnimation2D("SmallEnemyIdle");
	m_Animation2D->ChangeIdleAnimation2D();
	m_Weapon = m_pScene->SpawnObject<CSkelSmallDagger>("SkelSmallDagger");
	m_Weapon->SetRelativePos(0.f, 0.f, 0.f);
	m_WeaponArm->PushObjectChild(m_Weapon);
	m_WeaponArm->SetDirPos(Vector3(10.f, 0.f, 0.f));
	m_Status->SetMoveSpeed(50.f);
	m_Body->SetMoveSpeed(m_Status->GetMoveSpeed());

	return true;
}

void CSmallSkel::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
	if (m_Weapon->IsAttack())
	{
		return;
	}

	
}

void CSmallSkel::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
	AddRelativePos(m_Body->GetMove());
}

void CSmallSkel::Collision(float DeltaTime)
{
	CEnemy::Collision(DeltaTime);
}

void CSmallSkel::Render(float DeltaTime)
{
	CEnemy::Render(DeltaTime);
}

CSmallSkel* CSmallSkel::Clone()
{
	return new CSmallSkel(*this);
}

void CSmallSkel::Animation2DNotify(const std::string& Name)
{
}

void CSmallSkel::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		Vector3 DestPos = result.DestObject->GetWorldPos();
		Vector3 Pos = GetWorldPos();
		Pos = Pos - DestPos;
		float Dir;
		if (m_Dir == Object_Dir::Left)
		{
			Dir = 270.f;
		}
		else
		{
			Dir = 90.f;
		}
		//¿ÞÂÊ ¿À¸¥ÂÊ
		m_State = Enemy_State::Attack;
		m_Weapon->Attack(Dir);
	}
}

void CSmallSkel::AnimationFrameEnd(const std::string& Name)
{
}

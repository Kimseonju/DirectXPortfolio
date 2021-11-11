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

CSmallSkel::CSmallSkel()
{
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

	m_AttackRangeCollider2D->SetExtent(55.f, 50.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	m_Sprite->SetWorldScale(100.f, 100.f,0.f);
	m_Animation2D->SetIdleAnimation2D("SmallEnemyIdle");
	m_Animation2D->SetMoveAnimation2D("SmallEnemyMove");
	m_Animation2D->SetAttackAnimation2D("SmallEnemyIdle");

	m_Weapon = m_pScene->SpawnObject<CSkelSmallDagger>("SkelSmallDagger");
	m_Weapon->SetRelativePos(0.f, 0.f, 0.f);
	m_WeaponArm->PushObjectChild(m_Weapon);

	m_Status.SetMoveSpeed(200.f);
	m_Body->SetMoveSpeed(m_Status.GetMoveSpeed());

	return true;
}

void CSmallSkel::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);

	if (m_Weapon->IsAttack())
	{
		return;
	}

	//if (CGlobalValue::MainPlayer)
	//{
	//	CPlayer* player = CGlobalValue::MainPlayer;
	//	Vector3 Pos = player->GetWorldPos() - GetWorldPos();
	//	Pos.Normalize();
	//	float Angle = GetWorldPos().Angle(player->GetWorldPos());
	//
	//	//위
	//	if (Angle > 330.f && Angle < 30.f)
	//	{
	//
	//	}
	//
	//	//아래
	//
	//	else if (Angle > 150.f && Angle < 210.f)
	//	{
	//
	//	}
	//	else
	//	{
	//		Pos.y = 0.f;
	//		Pos.z = 0.f;
	//		Pos.Normalize();
	//		m_Body->SetDir(Pos);
	//
	//		if (Pos.x < 0.f)
	//		{
	//			m_Dir = Object_Dir::Left;
	//			m_Sprite->SetHorizontalReverse2DEnable(true);
	//		}
	//		else
	//		{
	//			m_Dir = Object_Dir::Right;
	//			m_Sprite->SetHorizontalReverse2DEnable(false);
	//		}
	//		m_WeaponArm->SetDir(m_Dir);
	//
	//		if (m_Weapon)
	//		{
	//			m_Weapon->SetDir(m_Dir);
	//			if (m_Weapon->GetWeaponType() == Weapon_Type::Melee)
	//			{
	//				if (m_Dir == Object_Dir::Left)
	//				{
	//					m_WeaponArm->SetRelativeRotationZ(-180.f);
	//					m_Weapon->SetRelativeRotationZ(-180.f);
	//				}
	//				else if (m_Dir == Object_Dir::Right)
	//				{
	//					m_WeaponArm->SetRelativeRotationZ(0);
	//					m_Weapon->SetRelativeRotationZ(0);
	//
	//				}
	//			}
	//			else if (m_Weapon->GetWeaponType() == Weapon_Type::Range)
	//			{
	//				m_Weapon->SetRelativeRotationZ(Angle + m_Weapon->GetRebound());
	//			}
	//		}
	//
	//	}
	//}
}

void CSmallSkel::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
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
		//왼쪽 오른쪽
		m_Weapon->Attack(Dir);
	}
}

void CSmallSkel::AnimationFrameEnd(const std::string& Name)
{
}

void CSmallSkel::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	CEnemy::CollisionBegin(result, Collider);
}

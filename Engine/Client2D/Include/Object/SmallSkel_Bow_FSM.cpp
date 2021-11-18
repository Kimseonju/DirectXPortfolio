#include "SmallSkel_Bow.h"
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


void CSmallSkel_Bow::FindStay()
{
	if (CGlobalValue::MainPlayer)
	{
		CPlayer* player = CGlobalValue::MainPlayer;
		Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
		float Distance = abs(PlayerPos.Distance(Vector2(GetWorldPos().x, GetWorldPos().y)));
		if (Distance > 70.f)
		{
			m_State = Enemy_State::Idle;
		}
		else
		{
			m_PlayerFind = true;
			m_State = Enemy_State::Move;
			m_EnemyFSM.ChangeState("Move");

		}

	}


}

void CSmallSkel_Bow::MoveStart()
{
}
//이 활쟁이는 움직이지않는다 무기각도변경
void CSmallSkel_Bow::MoveStay()
{

	CPlayer* player = CGlobalValue::MainPlayer;
	Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
	Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);

	Vector3 Pos = player->GetWorldPos() - GetWorldPos();
	Pos.Normalize();

	float Angle = EnemyPos.GetAngle(PlayerPos);

	//위
	//if (Angle > 330.f && Angle < 30.f)
	//{
	//	//점프하기
	//}
	////아래
	////else if (Angle > 150.f && Angle < 210.f)
	////{
	////	//내려가야대는데
	////}
	//else
	//{
	Pos.y = 0.f;
	Pos.z = 0.f;
	Pos.Normalize();
	if (Pos.x < 0.f)
	{
		m_Dir = Object_Dir::Left;
		m_Sprite->SetHorizontalReverse2DEnable(true);
	}
	else
	{
		m_Dir = Object_Dir::Right;
		m_Sprite->SetHorizontalReverse2DEnable(false);
	}
	m_WeaponArm->SetDir(m_Dir);

	if (m_Weapon)
	{
		if (m_Weapon->GetWeaponType() == Weapon_Type::Melee)
		{
			if (m_Dir == Object_Dir::Left)
			{
				m_Weapon->SetHorizontalReverse2DEnable(true);
			}
			else if (m_Dir == Object_Dir::Right)
			{
				m_Weapon->SetHorizontalReverse2DEnable(false);
			}
		}
		else if (m_Weapon->GetWeaponType() == Weapon_Type::Range)
		{
			m_Weapon->SetRelativeRotationZ(Angle);
		}
	}
	if (m_Weapon->IsAttack())
	{
		m_State = Enemy_State::Attack;
		m_Weapon->Attack(Angle);
		m_EnemyFSM.ChangeState("Attack");
	}
}


void CSmallSkel_Bow::AttackStart()
{
	m_Animation2D->ChangeIdleAnimation2D();
	SetWorldScale(14.f, 19.f, 0.f);

}

void CSmallSkel_Bow::AttackStay()
{
	if (!m_Weapon->IsAttacking())
		m_State = Enemy_State::Move;
	if (m_State == Enemy_State::Move)
	{
		m_EnemyFSM.ChangeState("Move");
	}
	
}


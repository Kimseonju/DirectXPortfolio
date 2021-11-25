#include "SmallSkel.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"


void CSmallSkel::FindStay()
{
	if (CGlobalValue::MainPlayer)
	{
		CPlayer* player = CGlobalValue::MainPlayer;
		Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
		float Distance = abs(PlayerPos.Distance(Vector2(GetWorldPos().x, GetWorldPos().y)));
		if (Distance > 30.f)
		{
			m_State = Enemy_State::Move;
		}
		else
		{
			m_PlayerFind = true;
		}
		
	}


	if (m_State == Enemy_State::Move)
	{
		m_EnemyFSM.ChangeState("Move");
		m_Animation2D->ChangeMoveAnimation2D();
		SetWorldScale(21.f, 20.f, 0.f);
	}

}

void CSmallSkel::MoveStart()
{
	m_Animation2D->ChangeMoveAnimation2D();
	SetWorldScale(21.f, 20.f, 0.f);
}

void CSmallSkel::MoveStay()
{
	CPlayer* player = CGlobalValue::MainPlayer;
	Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
	Vector3 Pos = player->GetWorldPos() - GetWorldPos();
	Pos.Normalize();
	float Angle = GetWorldPos().Angle(player->GetWorldPos());

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
		m_Body->SetDir(Pos);

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
			m_Weapon->SetDir(m_Dir);
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
			}
		}

	//}


	if (m_State == Enemy_State::Attack)
	{
		m_EnemyFSM.ChangeState("Attack");
	}
}


void CSmallSkel::AttackStart()
{
	m_Animation2D->ChangeIdleAnimation2D();
	SetWorldScale(14.f, 19.f, 0.f);
}

void CSmallSkel::AttackStay()
{
	if (!m_Weapon->IsAttacking())
		m_State = Enemy_State::Move;
	if (m_State == Enemy_State::Move)
	{
		m_EnemyFSM.ChangeState("Move");
	}
}


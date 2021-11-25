#include "Ghost.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"


void CGhost::FindStay()
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
	}

}

void CGhost::MoveStart()
{
	m_Animation2D->ChangeMoveAnimation2D();
}

void CGhost::MoveStay()
{
	CPlayer* player = CGlobalValue::MainPlayer;
	Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
	Vector3 Pos = player->GetWorldPos() - GetWorldPos();
	Pos.z = 0.f;
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

	m_Body->SetDir(Pos);

	Pos.y = 0.f;
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


	//}


	if (m_State == Enemy_State::Attack)
	{
		m_EnemyFSM.ChangeState("Attack");
		m_GhostAttack = true;
	}
}


void CGhost::AttackStart()
{
	m_Animation2D->ChangeAttackAnimation2D();
}

void CGhost::AttackStay()
{
	if (!m_GhostAttack)
	{
		m_State = Enemy_State::Move;
	}
	if (m_State == Enemy_State::Move)
	{
		m_EnemyFSM.ChangeState("Move");
	}
}


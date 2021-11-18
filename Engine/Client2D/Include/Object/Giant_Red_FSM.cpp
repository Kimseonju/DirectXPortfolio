#include "Giant_Red.h"
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
#include "Giant_RedBulletMain.h"

void CGiant_Red::FindStay()
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

void CGiant_Red::MoveStart()
{
	m_Animation2D->ChangeIdleAnimation2D();
	m_Sprite->SetWorldScale(59.f, 36.f, 0.f);
}
//이 활쟁이는 움직이지않는다 무기각도변경
void CGiant_Red::MoveStay()
{

	CPlayer* player = CGlobalValue::MainPlayer;
	Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
	Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);

	Vector3 Pos = player->GetWorldPos() - GetWorldPos();
	
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


	if (m_AttackTimer > m_AttackTimerMax)
	{
		m_AttackTimer = 0.f;
		m_Giant_RedAttack = true;
		m_Bullet = m_pScene->SpawnObject<CGiant_RedBulletMain>("Giant_RedBulletMain");
		m_Bullet->SetWorldPos(GetWorldPos());
	}
	if (m_Giant_RedAttack)
	{
		if (m_Bullet)
		{
			if (m_Bullet->IsAttackReady())
			{

				m_State = Enemy_State::Attack;
				m_EnemyFSM.ChangeState("Attack");
			}
		}
	}
}


void CGiant_Red::AttackStart()
{
	m_Animation2D->ChangeAttackAnimation2D();
	m_Sprite->SetWorldScale(59.f, 41.f, 0.f);
}

void CGiant_Red::AttackStay()
{
	if (!m_Giant_RedAttack)
		m_State = Enemy_State::Move;
	if (m_State == Enemy_State::Move)
	{
		m_EnemyFSM.ChangeState("Move");
	}

}


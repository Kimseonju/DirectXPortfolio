#include "Banshee.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"
#include "BansheeBullet.h"
#include <Scene/SceneResource.h>

void CBanshee::FindStay()
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

void CBanshee::MoveStart()
{
	m_Animation2D->ChangeIdleAnimation2D();

}
//이 활쟁이는 움직이지않는다 무기각도변경
void CBanshee::MoveStay()
{

	CPlayer* player = CGlobalValue::MainPlayer;
	Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
	Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);

	Vector3 Pos = player->GetWorldPos() - GetWorldPos();
	Pos.Normalize();

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
		m_BansheeAttack = true;
		m_State = Enemy_State::Attack;
		m_EnemyFSM.ChangeState("Attack");
	}
}


void CBanshee::AttackStart()
{
	m_Animation2D->ChangeAttackAnimation2D();
	m_pScene->GetResource()->FindSound("BansheeAttack")->Play();
	for (int i = 0; i < 12; ++i)
	{
		float Angle = 30.f * (float)i;

		CBansheeBullet* Bullet = m_pScene->SpawnObject<CBansheeBullet>("BansheeBullet");;
		Bullet->SetWorldPos(GetWorldPos());
		Bullet->SetWorldRotationZ(Angle);

	}
}

void CBanshee::AttackStay()
{
	if (!m_BansheeAttack)
		m_State = Enemy_State::Move;
	if (m_State == Enemy_State::Move)
	{
		m_EnemyFSM.ChangeState("Move");
	}

}


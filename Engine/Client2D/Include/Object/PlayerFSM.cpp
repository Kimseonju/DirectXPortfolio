
#include "Player.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "ShortSword.h"
#include "../GlobalValue.h"
#include "Revolver.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "MetalBoomerang.h"
#include "PlayerDash.h"
#include "../UI/BasicMouse.h"
#include "../UI/UIManager.h"
#include "PlayerDustEffect.h"



void CPlayer::BodyIdleStart()
{
	m_State = ePlayerState::Idle;
	m_Animation2D->ChangeIdleAnimation2D();
	SetRelativeScale(15.f, 20.f, 0.f);
}

void CPlayer::BodyIdleStay()
{
	if (m_Body->IsJump())
	{
		m_BodyFSM.ChangeState("Jump");
	}
	else if (m_RootComponent->GetVelocity().x != 0.f)
	{
 		m_BodyFSM.ChangeState("Move");
	}
}

void CPlayer::BodyMoveStart()
{
	m_State = ePlayerState::Move;
	m_Animation2D->ChangeMoveAnimation2D();
	SetRelativeScale(17.f, 20.f, 0.f);
}

void CPlayer::BodyMoveStay()
{
	if (m_DustCount >= 0.5f)
	{
		m_DustCount -= 0.5f;
		CPlayerDustEffect* Effect = m_pScene->SpawnObject< CPlayerDustEffect>("PlayerDustEffect");
		Effect->SetWorldPos(GetWorldPos());
		Effect->AddWorldPos(0.f, -m_Collider2DVertical->GetRelativeScale().y / 4.f, 0.f);
		Vector3 Velocity=GetVelocity();
		if (Velocity.x<0.f)
		{
			Effect->SetHorizontalReverse2DEnable(true);
		}
		else
		{
			Effect->SetHorizontalReverse2DEnable(false);
		}
	}
	if (m_RootComponent->GetVelocity().y != 0.f)
	{
		m_BodyFSM.ChangeState("Jump");
	}
	else if (m_RootComponent->GetVelocity().x != 0.f)
	{

	}
	else
	{
		m_BodyFSM.ChangeState("Idle");
	}
}


void CPlayer::BodyJumpStart()
{
	m_State = ePlayerState::Jump;
	m_Animation2D->ChangeJumpAnimation2D();
	SetRelativeScale(17.f, 21.f, 0.f);
}

void CPlayer::BodyJumpStay()
{
	if (!m_Body->IsJump())
	{
		if (m_RootComponent->GetVelocity().x != 0.f)
		{
			m_BodyFSM.ChangeState("Move");
		}
		else
		{
			m_BodyFSM.ChangeState("Idle");
		}
	}
}

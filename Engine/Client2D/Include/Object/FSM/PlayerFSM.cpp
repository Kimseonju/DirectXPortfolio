
#include "../Player.h"
#include "Input.h"
#include "../Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "../Weapon.h"
#include "../WeaponArm.h"
#include "../ShortSword.h"
#include "../../GlobalValue.h"
#include "../Revolver.h"
#include "../../UI/PlayerWorldInfoWidget.h"
#include "../MetalBoomerang.h"
#include "../PlayerDash.h"
#include "../../UI/BasicMouse.h"
#include "../../UI/UIManager.h"



void CPlayer::BodyIdleStart()
{
	m_State = ePlayerState::Idle;
	m_Animation2D->ChangeIdleAnimation2D();
	SetRelativeScale(15.f, 20.f, 0.f);
}

void CPlayer::BodyIdleStay()
{
	if (m_RootComponent->GetVelocity().y != 0.f)
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
	if (m_RootComponent->GetVelocity().y == 0.f)
	{
		if (m_RootComponent->GetVelocity().x != 0.f)
		{
			m_BodyFSM.ChangeState("MOVE");
		}
		else
		{
			m_BodyFSM.ChangeState("IDLE");
		}
	}
}

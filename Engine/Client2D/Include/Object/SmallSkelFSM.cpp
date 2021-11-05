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


void CSmallSkel::FindStay()
{
	if (m_RootComponent->GetVelocity().x != 0)
	{
		m_EnemyFSM.ChangeState("Move");
	}

	m_Animation2D->ChangeIdleAnimation2D();
	SetWorldScale(14.f, 19.f, 0.f);
}

void CSmallSkel::MoveStart()
{
	m_Animation2D->ChangeMoveAnimation2D();
	SetWorldScale(21.f, 20.f, 0.f);
}

void CSmallSkel::MoveStay()
{
}


void CSmallSkel::AttackStart()
{
	m_Animation2D->ChangeIdleAnimation2D();
}

void CSmallSkel::AttackStay()
{
	if (m_RootComponent->GetVelocity().x != 0)
	{
		m_EnemyFSM.ChangeState("Move");
	}
}


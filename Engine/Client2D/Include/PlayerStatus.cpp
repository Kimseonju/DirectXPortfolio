#include "PlayerStatus.h"
CPlayerStatus::CPlayerStatus():
	m_DashCount(0),
	m_DashCountMax(2.f),
	m_GracePeriod(0.f)
{
}

CPlayerStatus::~CPlayerStatus()
{
}

void CPlayerStatus::Init()
{
	m_HP = 30;
	m_HPMax = 30;
	m_Dash = 4;
	m_DashMax = 4;
	m_AttackSpeed=1.f;
	m_OldAttackSpeed = 1.f;
	m_ReloadSpeed=0.f;
	m_OldReloadSpeed=0.f;
	m_MoveSpeed = 300;
	m_Damage = 10;
	m_DamageMax = 20;
	m_Armor = 10;
	m_Critical = 10;
	m_Evasion = 10;
	m_DashCount = 0.f;
	m_DashCountMax = 2.f;
}

void CPlayerStatus::Update(float DeltaTime)
{
	if (m_GracePeriod > 0.f)
	{
		m_GracePeriod -= DeltaTime;
	}
	if (m_Dash < m_DashMax)
	{
		m_DashCount += DeltaTime;
		if (m_DashCount >= m_DashCountMax)
		{
			m_DashCount = 0;
			m_Dash++;
		}
	}
}

void CPlayerStatus::SubHP(int HP)
{
	m_GracePeriod = 0.5f;
	m_HP -= HP;
	if (m_HP < 0)
		m_HP = 0;

	
}

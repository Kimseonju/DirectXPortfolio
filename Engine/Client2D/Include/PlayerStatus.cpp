#include "PlayerStatus.h"
CPlayerStatus::CPlayerStatus():
	m_DashCount(0),
	m_DashCountMax(2.f),
	m_GracePeriod(0.f),
	m_Satiety(0),
	m_bShield(false),
	m_ShieldHP(10),
	m_ShieldHPMax(10),
	m_ShieldRecoveryCount(0.f)
{
}

CPlayerStatus::~CPlayerStatus()
{
}

void CPlayerStatus::Init()
{
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
	if (m_ShieldHP < m_ShieldHPMax)
	{
		m_ShieldRecoveryCount += DeltaTime;
		if (m_ShieldRecoveryCount > 1.f)
		{
			m_ShieldRecoveryCount -= 1.f;
			m_ShieldHP++;
		}
	}
}

bool CPlayerStatus::SubHP(int HP)
{
	m_GracePeriod = 0.5f;
	
	if (m_bShield)
	{
		m_ShieldHP -= HP;
		HP = 0;
		if (m_ShieldHP < 0)
		{
			HP=abs(m_ShieldHP);
			m_ShieldHP = 0;
		}
		else
		{
			//HP´Â ¾È±ï¿´´Ù.
			return false;
		}
	}
	//HP±ï¿´´Ù
	m_HP -= HP;
	if (m_HP < 0)
		m_HP = 0;

	return true;
}

bool CPlayerStatus::AddSatiety(int Satiety)
{
	if (m_Satiety + Satiety <= 100)
	{
		m_Satiety += Satiety;
		if (m_Satiety < 0)
			m_Satiety = 0;
		return true;
	}
	return false;
}

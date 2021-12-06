#include "PlayerStatus.h"
CPlayerStatus::CPlayerStatus():
	m_DashCount(0),
	m_DashCountMax(2.f),
	m_GracePeriod(0.f),
	m_Satiety(0)
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
}

void CPlayerStatus::SubHP(int HP)
{
	m_GracePeriod = 0.5f;
	m_HP -= HP;
	if (m_HP < 0)
		m_HP = 0;

	
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

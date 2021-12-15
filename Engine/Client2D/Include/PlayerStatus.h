#pragma once
#include "BasicStatus.h"
class CPlayerStatus :
    public CBasicStatus
{
public:
	CPlayerStatus();
	~CPlayerStatus();

private:
	float m_DashCount;
	float m_DashCountMax;
	float m_GracePeriod;
	int m_ShieldHP;
	int m_ShieldHPMax;
	bool m_bShield;
	int m_Satiety;
	float m_ShieldRecoveryCount;
public:
	void Init();
	void Update(float DeltaTime);
	bool GetGracePeriod()
	{
		if (m_GracePeriod > 0.f)
		{
			return true;
		}
		return false;
	}
	void SetShield(bool bShield)
	{
		m_bShield = bShield;
	}
	int GetShieldHP()const
	{
		return m_ShieldHP;
	}
	int GetShieldHPMax() const
	{
		return m_ShieldHPMax;
	}
	float GetShieldHP_Percent() const
	{
		return (float)m_ShieldHP / (float)m_ShieldHPMax;
	}
	virtual bool SubHP(int HP);
	bool AddSatiety(int Satiety);
	int GetSatiety() const
	{
		return m_Satiety;
	}
};


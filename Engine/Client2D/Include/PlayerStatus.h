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
	int m_Satiety;
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
	virtual void SubHP(int HP);
	bool AddSatiety(int Satiety);
	int GetSatiety() const
	{
		return m_Satiety;
	}
};


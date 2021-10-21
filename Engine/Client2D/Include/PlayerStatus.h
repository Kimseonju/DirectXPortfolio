#pragma once
#include "BasicStatus.h"
class CPlayerStatus :
    public CBasicStatus
{
public:
	CPlayerStatus();
	CPlayerStatus(const CPlayerStatus& status);
	~CPlayerStatus();

private:
	float m_DashCount;
	float m_DashCountMax;
public:
	void Init();
	void Update(float DeltaTime);
};


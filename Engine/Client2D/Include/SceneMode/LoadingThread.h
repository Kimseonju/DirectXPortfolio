#pragma once
#include <Thread.h>
class CLoadingThread :
	public CThread
{
public:
	CLoadingThread();
	~CLoadingThread();
	float m_Percent;
public:
	virtual void Run();
	float GetPercent()
	{
		return m_Percent;
	}
};


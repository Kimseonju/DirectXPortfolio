#pragma once
#include <Thread.h>
class CLoadingThreadScene :
	public CThread
{
public:
	CLoadingThreadScene();
	~CLoadingThreadScene();
	float m_Percent;
public:
	virtual void Run();
	float GetPercent()
	{
		return m_Percent;
	}
};


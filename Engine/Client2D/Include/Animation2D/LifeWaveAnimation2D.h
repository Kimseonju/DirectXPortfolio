#pragma once
#include "Resource/Animation2D.h"
class CLifeWaveAnimation2D :
	public CAnimation2D
{
public:
	CLifeWaveAnimation2D();
	CLifeWaveAnimation2D(const CLifeWaveAnimation2D& anim);
	virtual ~CLifeWaveAnimation2D();
protected:

	bool m_Die;
public:

	void IsDie()
	{
		m_Die = true;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CLifeWaveAnimation2D* Clone();
};



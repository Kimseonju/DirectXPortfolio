#pragma once
#include "Resource/Animation2D.h"
class CMetalBoomerangEffectAnimation2D :
	public CAnimation2D
{
public:
	CMetalBoomerangEffectAnimation2D();
	CMetalBoomerangEffectAnimation2D(const CMetalBoomerangEffectAnimation2D& anim);
	virtual ~CMetalBoomerangEffectAnimation2D();
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
	virtual CMetalBoomerangEffectAnimation2D* Clone();
};



#pragma once
#include "Resource/Animation2D.h"
class CRevolverEffectAnimation2D :
	public CAnimation2D
{
public:
	CRevolverEffectAnimation2D();
	CRevolverEffectAnimation2D(const CRevolverEffectAnimation2D& anim);
	virtual ~CRevolverEffectAnimation2D();
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
	virtual CRevolverEffectAnimation2D* Clone();
};



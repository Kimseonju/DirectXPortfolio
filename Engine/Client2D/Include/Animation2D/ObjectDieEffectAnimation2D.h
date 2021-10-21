#pragma once
#include "Resource/Animation2D.h"
class CObjectDieEffectAnimation2D :
	public CAnimation2D
{
public:
	CObjectDieEffectAnimation2D();
	CObjectDieEffectAnimation2D(const CObjectDieEffectAnimation2D& anim);
	virtual ~CObjectDieEffectAnimation2D();
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
	virtual CObjectDieEffectAnimation2D* Clone();
};



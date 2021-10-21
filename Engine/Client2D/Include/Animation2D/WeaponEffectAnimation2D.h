#pragma once

#include "Resource/Animation2D.h"

class CWeaponEffectAnimation2D :
	public CAnimation2D
{
public:
	CWeaponEffectAnimation2D();
	CWeaponEffectAnimation2D(const CWeaponEffectAnimation2D& anim);
	virtual ~CWeaponEffectAnimation2D();
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
	virtual CWeaponEffectAnimation2D* Clone();
};


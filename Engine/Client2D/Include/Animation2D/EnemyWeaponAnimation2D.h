#pragma once

#include "Resource/Animation2D.h"

class CEnemyWeaponAnimation2D :
	public CAnimation2D
{
public:
	CEnemyWeaponAnimation2D();
	CEnemyWeaponAnimation2D(const CEnemyWeaponAnimation2D& anim);
	virtual ~CEnemyWeaponAnimation2D();
protected:

	bool m_Die;

	Sequence2DInfo* m_Idle;
	Sequence2DInfo* m_Attack;

public:

	void IsDie()
	{
		m_Die = true;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CEnemyWeaponAnimation2D* Clone();
};


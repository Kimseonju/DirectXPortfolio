#pragma once
#include "Resource/Animation2D.h"
class CBelialWeaponChargeAnimation2D :
	public CAnimation2D
{
public:
	CBelialWeaponChargeAnimation2D();
	CBelialWeaponChargeAnimation2D(const CBelialWeaponChargeAnimation2D& anim);
	virtual ~CBelialWeaponChargeAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBelialWeaponChargeAnimation2D* Clone();
};
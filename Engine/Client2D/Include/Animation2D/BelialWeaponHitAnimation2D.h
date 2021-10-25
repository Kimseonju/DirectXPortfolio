#pragma once
#include "Resource/Animation2D.h"
class CBelialWeaponHitAnimation2D :
	public CAnimation2D
{
public:
	CBelialWeaponHitAnimation2D();
	CBelialWeaponHitAnimation2D(const CBelialWeaponHitAnimation2D& anim);
	virtual ~CBelialWeaponHitAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBelialWeaponHitAnimation2D* Clone();
};


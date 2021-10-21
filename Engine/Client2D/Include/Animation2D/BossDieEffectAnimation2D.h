#pragma once

#include "Resource/Animation2D.h"
class CBossDieEffectAnimation2D :
	public CAnimation2D
{
public:
	CBossDieEffectAnimation2D();
	CBossDieEffectAnimation2D(const CBossDieEffectAnimation2D& anim);
	virtual ~CBossDieEffectAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBossDieEffectAnimation2D* Clone();
};



#pragma once
#include "Resource/Animation2D.h"
class CRevolverEffectAnimation2D :
	public CAnimation2D
{
public:
	CRevolverEffectAnimation2D();
	CRevolverEffectAnimation2D(const CRevolverEffectAnimation2D& anim);
	virtual ~CRevolverEffectAnimation2D();
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CRevolverEffectAnimation2D* Clone();
};



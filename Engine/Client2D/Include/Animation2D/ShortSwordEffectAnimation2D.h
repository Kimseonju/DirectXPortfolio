#pragma once
#include "Resource/Animation2D.h"
class CShortSwordEffectAnimation2D :
	public CAnimation2D
{
public:
	CShortSwordEffectAnimation2D();
	CShortSwordEffectAnimation2D(const CShortSwordEffectAnimation2D& anim);
	virtual ~CShortSwordEffectAnimation2D();
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CShortSwordEffectAnimation2D* Clone();
};



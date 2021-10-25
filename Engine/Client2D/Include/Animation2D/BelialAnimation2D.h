#pragma once

#include "Resource/Animation2D.h"
class CBelialAnimation2D :
	public CAnimation2D
{
public:
	CBelialAnimation2D();
	CBelialAnimation2D(const CBelialAnimation2D& anim);
	virtual ~CBelialAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBelialAnimation2D* Clone();
};



#pragma once

#include "Resource/Animation2D.h"
class CBelialHandAnimation2D :
	public CAnimation2D
{
public:
	CBelialHandAnimation2D();
	CBelialHandAnimation2D(const CBelialHandAnimation2D& anim);
	virtual ~CBelialHandAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBelialHandAnimation2D* Clone();
};



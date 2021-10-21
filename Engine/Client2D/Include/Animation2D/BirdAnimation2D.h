#pragma once

#include "Resource/Animation2D.h"

class CBirdAnimation2D :
	public CAnimation2D
{
public:
	CBirdAnimation2D();
	CBirdAnimation2D(const CBirdAnimation2D& anim);
	virtual ~CBirdAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CBirdAnimation2D* Clone();
};


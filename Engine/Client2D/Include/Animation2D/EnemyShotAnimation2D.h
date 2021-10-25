#pragma once

#include "Resource/Animation2D.h"

class CEnemyShotAnimation2D :
	public CAnimation2D
{
public:
	CEnemyShotAnimation2D();
	CEnemyShotAnimation2D(const CEnemyShotAnimation2D& anim);
	virtual ~CEnemyShotAnimation2D();
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CEnemyShotAnimation2D* Clone();
};


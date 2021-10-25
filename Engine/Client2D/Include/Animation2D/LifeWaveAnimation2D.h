#pragma once
#include "Resource/Animation2D.h"
class CLifeWaveAnimation2D :
	public CAnimation2D
{
public:
	CLifeWaveAnimation2D();
	CLifeWaveAnimation2D(const CLifeWaveAnimation2D& anim);
	virtual ~CLifeWaveAnimation2D();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CLifeWaveAnimation2D* Clone();
};



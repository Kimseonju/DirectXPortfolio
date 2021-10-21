#include "LifeWaveAnimation2D.h"	

CLifeWaveAnimation2D::CLifeWaveAnimation2D()
{
}

CLifeWaveAnimation2D::CLifeWaveAnimation2D(const CLifeWaveAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CLifeWaveAnimation2D::~CLifeWaveAnimation2D()
{
}

void CLifeWaveAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CLifeWaveAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("LifeWave");
	//AddAnimationSequence2D("PlayerRun");
	return true;
}

void CLifeWaveAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CLifeWaveAnimation2D* CLifeWaveAnimation2D::Clone()
{
	return new CLifeWaveAnimation2D(*this);
}

#include "RevolverEffectAnimation2D.h"

CRevolverEffectAnimation2D::CRevolverEffectAnimation2D()
{
}

CRevolverEffectAnimation2D::CRevolverEffectAnimation2D(const CRevolverEffectAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CRevolverEffectAnimation2D::~CRevolverEffectAnimation2D()
{
}

void CRevolverEffectAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CRevolverEffectAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("RevolverEffect", false);
	//AddAnimationSequence2D("PlayerRun");
	return true;
}

void CRevolverEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CRevolverEffectAnimation2D* CRevolverEffectAnimation2D::Clone()
{
	return new CRevolverEffectAnimation2D(*this);
}

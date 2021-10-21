#include "MetalBoomerangEffectAnimation2D.h"

CMetalBoomerangEffectAnimation2D::CMetalBoomerangEffectAnimation2D()
{
}

CMetalBoomerangEffectAnimation2D::CMetalBoomerangEffectAnimation2D(const CMetalBoomerangEffectAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CMetalBoomerangEffectAnimation2D::~CMetalBoomerangEffectAnimation2D()
{
}

void CMetalBoomerangEffectAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CMetalBoomerangEffectAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("MetalBoomerangEffect", false);
	//AddAnimationSequence2D("PlayerRun");
	return true;
}

void CMetalBoomerangEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CMetalBoomerangEffectAnimation2D* CMetalBoomerangEffectAnimation2D::Clone()
{
	return new CMetalBoomerangEffectAnimation2D(*this);
}

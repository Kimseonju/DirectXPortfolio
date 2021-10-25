#include "ShortSwordEffectAnimation2D.h"

CShortSwordEffectAnimation2D::CShortSwordEffectAnimation2D()
{
}

CShortSwordEffectAnimation2D::CShortSwordEffectAnimation2D(const CShortSwordEffectAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CShortSwordEffectAnimation2D::~CShortSwordEffectAnimation2D()
{
}

void CShortSwordEffectAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CShortSwordEffectAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("ShortSwordEffect", false);
	//AddAnimationSequence2D("PlayerRun");
	return true;
}

void CShortSwordEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CShortSwordEffectAnimation2D* CShortSwordEffectAnimation2D::Clone()
{
	return new CShortSwordEffectAnimation2D(*this);
}

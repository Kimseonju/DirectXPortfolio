#include "ObjectDieEffectAnimation2D.h"

CObjectDieEffectAnimation2D::CObjectDieEffectAnimation2D()
{
}

CObjectDieEffectAnimation2D::CObjectDieEffectAnimation2D(const CObjectDieEffectAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CObjectDieEffectAnimation2D::~CObjectDieEffectAnimation2D()
{
}

void CObjectDieEffectAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CObjectDieEffectAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("ObjectDieEffect", false);
	//AddAnimationSequence2D("PlayerRun");
	return true;
}

void CObjectDieEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CObjectDieEffectAnimation2D* CObjectDieEffectAnimation2D::Clone()
{
	return new CObjectDieEffectAnimation2D(*this);
}

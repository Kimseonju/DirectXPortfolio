#include "BelialAnimation2D.h"
#include "Component/SpriteComponent.h"

CBelialAnimation2D::CBelialAnimation2D()
{
}

CBelialAnimation2D::CBelialAnimation2D(const CBelialAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CBelialAnimation2D::~CBelialAnimation2D()
{
}

void CBelialAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CBelialAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("BelialHead_Idle");
	AddAnimationSequence2D("BelialHead_Attack", false);

	return true;
}

void CBelialAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
	if (GetFrameEnd())
		ChangeAnimation("BelialHead_Idle");
}

CBelialAnimation2D* CBelialAnimation2D::Clone()
{
	return new CBelialAnimation2D(*this);
}

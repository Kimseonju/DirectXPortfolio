#include "BelialHandAnimation2D.h"
#include "Component/SpriteComponent.h"

CBelialHandAnimation2D::CBelialHandAnimation2D()
{
}

CBelialHandAnimation2D::CBelialHandAnimation2D(const CBelialHandAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CBelialHandAnimation2D::~CBelialHandAnimation2D()
{
}

void CBelialHandAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CBelialHandAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("BelialHand_Idle");
	AddAnimationSequence2D("BelialHand_Attack", false);

	return true;
}

void CBelialHandAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

	if (GetFrameEnd())
		ChangeAnimation("BelialHand_Idle");
}

CBelialHandAnimation2D* CBelialHandAnimation2D::Clone()
{
	return new CBelialHandAnimation2D(*this);
}

#include "BossDieEffectAnimation2D.h"
#include "Component/SpriteComponent.h"

CBossDieEffectAnimation2D::CBossDieEffectAnimation2D()
{
}

CBossDieEffectAnimation2D::CBossDieEffectAnimation2D(const CBossDieEffectAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CBossDieEffectAnimation2D::~CBossDieEffectAnimation2D()
{
}

void CBossDieEffectAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CBossDieEffectAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("PlayerIdle");
	AddAnimationSequence2D("PlayerRun");
	AddAnimationSequence2D("PlayerAttack", false);

	return true;
}

void CBossDieEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

	if (m_Owner->GetVelocity().Length() > 0.f)
	{
		ChangeAnimation("PlayerRun");
	}

	else
	{
		if (GetCurrentSequenceName() != "PlayerAttack")
			ChangeAnimation("PlayerIdle");
	}
}

CBossDieEffectAnimation2D* CBossDieEffectAnimation2D::Clone()
{
	return new CBossDieEffectAnimation2D(*this);
}

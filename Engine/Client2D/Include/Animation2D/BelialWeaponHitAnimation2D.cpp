#include "BelialWeaponHitAnimation2D.h"

CBelialWeaponHitAnimation2D::CBelialWeaponHitAnimation2D()
{
}

CBelialWeaponHitAnimation2D::CBelialWeaponHitAnimation2D(const CBelialWeaponHitAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CBelialWeaponHitAnimation2D::~CBelialWeaponHitAnimation2D()
{
}

void CBelialWeaponHitAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CBelialWeaponHitAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;
	AddAnimationSequence2D("BelialHand_Idle");
	AddAnimationSequence2D("BelialHand_Attack", false);
	return false;
}

void CBelialWeaponHitAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CBelialWeaponHitAnimation2D* CBelialWeaponHitAnimation2D::Clone()
{
	return new CBelialWeaponHitAnimation2D(*this);
}

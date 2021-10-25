#include "BelialWeaponChargeAnimation2D.h"

CBelialWeaponChargeAnimation2D::CBelialWeaponChargeAnimation2D()
{
}

CBelialWeaponChargeAnimation2D::CBelialWeaponChargeAnimation2D(const CBelialWeaponChargeAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CBelialWeaponChargeAnimation2D::~CBelialWeaponChargeAnimation2D()
{
}

void CBelialWeaponChargeAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CBelialWeaponChargeAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;


	AddAnimationSequence2D("Belial_WeaponCharge");

	return true;
}

void CBelialWeaponChargeAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CBelialWeaponChargeAnimation2D* CBelialWeaponChargeAnimation2D::Clone()
{
	return new CBelialWeaponChargeAnimation2D(*this);
}

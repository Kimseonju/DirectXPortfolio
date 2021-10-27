
#include "WeaponEffectAnimation2D.h"
#include "Component/SpriteComponent.h"

CWeaponEffectAnimation2D::CWeaponEffectAnimation2D() :
	m_Die(false)
{
}

CWeaponEffectAnimation2D::CWeaponEffectAnimation2D(const CWeaponEffectAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CWeaponEffectAnimation2D::~CWeaponEffectAnimation2D()
{
}

void CWeaponEffectAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CWeaponEffectAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;


	return true;
}

void CWeaponEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CWeaponEffectAnimation2D* CWeaponEffectAnimation2D::Clone()
{
	return new CWeaponEffectAnimation2D(*this);
}

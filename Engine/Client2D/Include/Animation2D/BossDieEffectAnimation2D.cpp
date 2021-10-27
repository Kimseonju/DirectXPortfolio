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


	return true;
}

void CBossDieEffectAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CBossDieEffectAnimation2D* CBossDieEffectAnimation2D::Clone()
{
	return new CBossDieEffectAnimation2D(*this);
}

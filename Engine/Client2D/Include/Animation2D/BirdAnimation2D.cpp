
#include "BirdAnimation2D.h"
#include "Component/SpriteComponent.h"

CBirdAnimation2D::CBirdAnimation2D()
{
}

CBirdAnimation2D::CBirdAnimation2D(const CBirdAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CBirdAnimation2D::~CBirdAnimation2D()
{
}

void CBirdAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CBirdAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("BirdMove");

	return true;
}

void CBirdAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CBirdAnimation2D* CBirdAnimation2D::Clone()
{
	return new CBirdAnimation2D(*this);
}

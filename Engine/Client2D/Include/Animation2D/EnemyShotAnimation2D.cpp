#include "EnemyShotAnimation2D.h"
#include "Component/SpriteComponent.h"

CEnemyShotAnimation2D::CEnemyShotAnimation2D()
{
}

CEnemyShotAnimation2D::CEnemyShotAnimation2D(const CEnemyShotAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CEnemyShotAnimation2D::~CEnemyShotAnimation2D()
{
}

void CEnemyShotAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CEnemyShotAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	return true;
}

void CEnemyShotAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
	
}

CEnemyShotAnimation2D* CEnemyShotAnimation2D::Clone()
{
	return new CEnemyShotAnimation2D(*this);
}

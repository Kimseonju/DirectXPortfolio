#include "Giant_RedBulletFX.h"
CGiant_RedBulletFX::CGiant_RedBulletFX()
{
}

CGiant_RedBulletFX::CGiant_RedBulletFX(const CGiant_RedBulletFX& obj) :
	CEffectObject(obj)
{
}

CGiant_RedBulletFX::~CGiant_RedBulletFX()
{
}

void CGiant_RedBulletFX::Start()
{
}

bool CGiant_RedBulletFX::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetWorldScale(26.f, 26.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("Giant_RedBulletFX", false);
	m_Animation2D->SetFrameEndFunction<CGiant_RedBulletFX>(this, &CEffectObject::AnimationFrameEnd);

	return true;
}

void CGiant_RedBulletFX::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CGiant_RedBulletFX::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CGiant_RedBulletFX::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CGiant_RedBulletFX::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);

}

CGiant_RedBulletFX* CGiant_RedBulletFX::Clone()
{
	return new CGiant_RedBulletFX(*this);
}

void CGiant_RedBulletFX::Animation2DNotify(const std::string& Name)
{
}

void CGiant_RedBulletFX::AnimationFrameEnd(const std::string& Name)
{
	Active(false);
}

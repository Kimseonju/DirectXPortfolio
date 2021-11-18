#include "BansheeBulletFX.h"
CBansheeBulletFX::CBansheeBulletFX()
{
}

CBansheeBulletFX::CBansheeBulletFX(const CBansheeBulletFX& obj) :
	CEffectObject(obj)
{
}

CBansheeBulletFX::~CBansheeBulletFX()
{
}

void CBansheeBulletFX::Start()
{
}

bool CBansheeBulletFX::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetWorldScale(20.f, 27.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("BansheeBulletFX", false);
	m_Animation2D->SetFrameEndFunction<CBansheeBulletFX>(this, &CEffectObject::AnimationFrameEnd);

	return true;
}

void CBansheeBulletFX::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CBansheeBulletFX::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CBansheeBulletFX::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CBansheeBulletFX::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CBansheeBulletFX* CBansheeBulletFX::Clone()
{
	return new CBansheeBulletFX(*this);
}

void CBansheeBulletFX::Animation2DNotify(const std::string& Name)
{
}

void CBansheeBulletFX::AnimationFrameEnd(const std::string& Name)
{
	Active(false);
}

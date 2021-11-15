#include "BelialBulletEffect.h"
CBelialBulletEffect::CBelialBulletEffect()
{
}

CBelialBulletEffect::CBelialBulletEffect(const CBelialBulletEffect& obj) :
	CEffectObject(obj)
{
}

CBelialBulletEffect::~CBelialBulletEffect()
{
}

void CBelialBulletEffect::Start()
{
}

bool CBelialBulletEffect::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(31.f, 31.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("Belial_BulletFx", false);
	m_Animation2D->SetFrameEndFunction<CBelialBulletEffect>(this, &CEffectObject::AnimationFrameEnd);

	return true;
}

void CBelialBulletEffect::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CBelialBulletEffect::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CBelialBulletEffect::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CBelialBulletEffect::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CBelialBulletEffect* CBelialBulletEffect::Clone()
{
	return new CBelialBulletEffect(*this);
}

void CBelialBulletEffect::Animation2DNotify(const std::string& Name)
{
}

void CBelialBulletEffect::AnimationFrameEnd(const std::string& Name)
{
}

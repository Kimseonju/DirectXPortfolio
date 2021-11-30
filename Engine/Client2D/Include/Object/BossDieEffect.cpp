#include "BossDieEffect.h"
#include <Scene/Scene.h>
#include "BossDieParticle.h"
#include "Belial.h"
#include <Scene/SceneResource.h>
CBossDieEffect::CBossDieEffect()
{
}

CBossDieEffect::CBossDieEffect(const CBossDieEffect& obj) :
	CEffectObject(obj)
{

}

CBossDieEffect::~CBossDieEffect()
{
}

void CBossDieEffect::Start()
{
}

bool CBossDieEffect::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(31.f, 31.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("ObjectDieEffect", false);
	m_Animation2D->SetFrameEndFunction<CBossDieEffect>(this, &CEffectObject::AnimationFrameEnd);
	m_Animation2D->SetSequencePlayRate("ObjectDieEffect", 2.f);

	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);

	return true;
}

void CBossDieEffect::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}


void CBossDieEffect::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CBossDieEffect::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CBossDieEffect::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CBossDieEffect* CBossDieEffect::Clone()
{
	return new CBossDieEffect(*this);
}

void CBossDieEffect::Animation2DNotify(const std::string& Name)
{
}

void CBossDieEffect::AnimationFrameEnd(const std::string& Name)
{
	CEffectObject::AnimationFrameEnd(Name);
}

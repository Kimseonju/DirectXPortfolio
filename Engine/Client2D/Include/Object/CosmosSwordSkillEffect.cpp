#include "CosmosSwordSkillEffect.h"
#include <Resource/ResourceManager.h>
#include <Scene/Scene.h>
CCosmosSwordSkillEffect::CCosmosSwordSkillEffect()
{
}

CCosmosSwordSkillEffect::CCosmosSwordSkillEffect(const CCosmosSwordSkillEffect& obj) :
	CEffectObject(obj)
{
}

CCosmosSwordSkillEffect::~CCosmosSwordSkillEffect()
{
}

void CCosmosSwordSkillEffect::Start()
{
}

bool CCosmosSwordSkillEffect::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(14.f, 20.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Animation2D->SetIdleAnimation2D("ShortSwordEffect", false);
	m_Animation2D->SetSequencePlayRate("ShortSwordEffect", 4.f);
	m_Animation2D->SetFrameEndFunction<CCosmosSwordSkillEffect>(this, &CEffectObject::AnimationFrameEnd);
	return true;
}

void CCosmosSwordSkillEffect::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CCosmosSwordSkillEffect::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CCosmosSwordSkillEffect::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CCosmosSwordSkillEffect::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CCosmosSwordSkillEffect* CCosmosSwordSkillEffect::Clone()
{
	return new CCosmosSwordSkillEffect(*this);
}

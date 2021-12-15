#include "CosmosSwordEffect.h"
#include <Resource/ResourceManager.h>
#include <Scene/Scene.h>
CCosmosSwordEffect::CCosmosSwordEffect()
{
}

CCosmosSwordEffect::CCosmosSwordEffect(const CCosmosSwordEffect& obj) :
	CEffectObject(obj)
{
}

CCosmosSwordEffect::~CCosmosSwordEffect()
{
}

void CCosmosSwordEffect::Start()
{
}

bool CCosmosSwordEffect::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(47.f, 60.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Animation2D->SetIdleAnimation2D("CosmosSwordEffect", false);
	m_Animation2D->SetSequencePlayRate("CosmosSwordEffect", 4.f);
	m_Animation2D->SetFrameEndFunction<CCosmosSwordEffect>(this, &CEffectObject::AnimationFrameEnd);
	return true;
}

void CCosmosSwordEffect::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CCosmosSwordEffect::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CCosmosSwordEffect::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CCosmosSwordEffect::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CCosmosSwordEffect* CCosmosSwordEffect::Clone()
{
	return new CCosmosSwordEffect(*this);
}

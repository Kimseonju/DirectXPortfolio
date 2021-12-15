#include "TaanaShieldEffect.h"
#include <Resource/ResourceManager.h>
#include <Scene/Scene.h>
#include "../GlobalValue.h"
#include "Player.h"
CTaanaShieldEffect::CTaanaShieldEffect()
{
}

CTaanaShieldEffect::CTaanaShieldEffect(const CTaanaShieldEffect& obj) :
	CEffectObject(obj)
{
}

CTaanaShieldEffect::~CTaanaShieldEffect()
{
}

void CTaanaShieldEffect::Start()
{
}

bool CTaanaShieldEffect::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(25.f, 25.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Animation2D->SetIdleAnimation2D("TAANAShield", false);
	m_Animation2D->SetSequencePlayRate("ShortSwordEffect", 4.f);
	m_Animation2D->SetFrameEndFunction<CTaanaShieldEffect>(this, &CEffectObject::AnimationFrameEnd);
	return true;
}

void CTaanaShieldEffect::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CTaanaShieldEffect::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
	SetWorldPos(CGlobalValue::MainPlayer->GetWorldPos());
}

void CTaanaShieldEffect::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CTaanaShieldEffect::PrevRender(float DeltaTime)
{
	CEffectObject::PrevRender(DeltaTime);
}

void CTaanaShieldEffect::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CTaanaShieldEffect* CTaanaShieldEffect::Clone()
{
	return new CTaanaShieldEffect(*this);
}

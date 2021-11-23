#include "PlayerDustEffect.h"
CPlayerDustEffect::CPlayerDustEffect()
{
}

CPlayerDustEffect::CPlayerDustEffect(const CPlayerDustEffect& obj) :
	CEffectObject(obj)
{
}

CPlayerDustEffect::~CPlayerDustEffect()
{
}

void CPlayerDustEffect::Start()
{
}

bool CPlayerDustEffect::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetWorldScale(14.f, 13.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("PlayerDustEffeect", false);
	m_Animation2D->SetFrameEndFunction<CPlayerDustEffect>(this, &CEffectObject::AnimationFrameEnd);

	return true;
}

void CPlayerDustEffect::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CPlayerDustEffect::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CPlayerDustEffect::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CPlayerDustEffect::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);

}

CPlayerDustEffect* CPlayerDustEffect::Clone()
{
	return new CPlayerDustEffect(*this);
}

void CPlayerDustEffect::Animation2DNotify(const std::string& Name)
{
}

void CPlayerDustEffect::SetHorizontalReverse2DEnable(bool Enable)
{
	m_Sprite->SetHorizontalReverse2DEnable(Enable);
}

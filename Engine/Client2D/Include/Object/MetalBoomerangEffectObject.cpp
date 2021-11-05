#include "MetalBoomerangEffectObject.h"
CMetalBoomerangEffectObject::CMetalBoomerangEffectObject()
{
}

CMetalBoomerangEffectObject::CMetalBoomerangEffectObject(const CMetalBoomerangEffectObject& obj) :
	CEffectObject(obj)
{
}

CMetalBoomerangEffectObject::~CMetalBoomerangEffectObject()
{
}

void CMetalBoomerangEffectObject::Start()
{
}

bool CMetalBoomerangEffectObject::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(28.f, 40.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D->SetIdleAnimation2D("MetalBoomerangEffect", false);
	m_Animation2D->SetFrameEndFunction<CMetalBoomerangEffectObject>(this, &CEffectObject::AnimationFrameEnd);

	return true;
}

void CMetalBoomerangEffectObject::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CMetalBoomerangEffectObject::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CMetalBoomerangEffectObject::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CMetalBoomerangEffectObject::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CMetalBoomerangEffectObject* CMetalBoomerangEffectObject::Clone()
{
	return new CMetalBoomerangEffectObject(*this);
}

void CMetalBoomerangEffectObject::Animation2DNotify(const std::string& Name)
{
}

void CMetalBoomerangEffectObject::AnimationFrameEnd(const std::string& Name)
{
}

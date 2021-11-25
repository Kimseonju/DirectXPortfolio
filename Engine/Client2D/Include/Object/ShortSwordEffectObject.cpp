#include "ShortSwordEffectObject.h"
CShortSwordEffectObject::CShortSwordEffectObject()
{
}

CShortSwordEffectObject::CShortSwordEffectObject(const CShortSwordEffectObject& obj) :
	CEffectObject(obj)
{
}

CShortSwordEffectObject::~CShortSwordEffectObject()
{
}

void CShortSwordEffectObject::Start()
{
}

bool CShortSwordEffectObject::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(14.f, 20.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	
	m_Animation2D->SetIdleAnimation2D("ShortSwordEffect", false);
	m_Animation2D->SetSequencePlayRate("ShortSwordEffect",4.f);
	m_Animation2D->SetFrameEndFunction<CShortSwordEffectObject>(this, &CEffectObject::AnimationFrameEnd);

	return true;
}

void CShortSwordEffectObject::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CShortSwordEffectObject::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CShortSwordEffectObject::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CShortSwordEffectObject::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CShortSwordEffectObject* CShortSwordEffectObject::Clone()
{
	return new CShortSwordEffectObject(*this);
}

void CShortSwordEffectObject::Animation2DNotify(const std::string& Name)
{
}

#include "ObjectDieEffectObject.h"
CObjectDieEffectObject::CObjectDieEffectObject()
{
}

CObjectDieEffectObject::CObjectDieEffectObject(const CObjectDieEffectObject& obj) :
	CEffectObject(obj)
{
}

CObjectDieEffectObject::~CObjectDieEffectObject()
{
}

void CObjectDieEffectObject::Start()
{
}

bool CObjectDieEffectObject::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(28.f, 40.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Animation2D->SetIdleAnimation2D("ObjectDieEffect", false);
	m_Animation2D->SetFrameEndFunction< CObjectDieEffectObject>(this, &CEffectObject::AnimationFrameEnd);
	return true;
}

void CObjectDieEffectObject::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CObjectDieEffectObject::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CObjectDieEffectObject::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CObjectDieEffectObject::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CObjectDieEffectObject* CObjectDieEffectObject::Clone()
{
	return new CObjectDieEffectObject(*this);
}

void CObjectDieEffectObject::Animation2DNotify(const std::string& Name)
{
}

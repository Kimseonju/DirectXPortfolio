#include "RevolverEffectObject.h"
CRevolverEffectObject::CRevolverEffectObject()
{
}

CRevolverEffectObject::CRevolverEffectObject(const CRevolverEffectObject& obj) :
	CEffectObject(obj)
{
}

CRevolverEffectObject::~CRevolverEffectObject()
{
}

void CRevolverEffectObject::Start()
{
}

bool CRevolverEffectObject::Init()
{
	if (!CEffectObject::Init())
		return false;

	m_Sprite->SetRelativeScale(Vector3(28.f, 40.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	CSharedPtr<CMaterial> SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->AddTexture("PlayerTex", TEXT("teemo.png"));

	m_Animation2D->SetIdleAnimation2D("RevolverEffect", false);
	m_Animation2D->SetSequencePlayRate("RevolverEffect", 4.f);
	m_Animation2D->SetFrameEndFunction<CRevolverEffectObject>(this, &CEffectObject::AnimationFrameEnd);
	return true;
}

void CRevolverEffectObject::Update(float DeltaTime)
{
	CEffectObject::Update(DeltaTime);
}

void CRevolverEffectObject::PostUpdate(float DeltaTime)
{
	CEffectObject::PostUpdate(DeltaTime);
}

void CRevolverEffectObject::Collision(float DeltaTime)
{
	CEffectObject::Collision(DeltaTime);
}

void CRevolverEffectObject::Render(float DeltaTime)
{
	CEffectObject::Render(DeltaTime);
}

CRevolverEffectObject* CRevolverEffectObject::Clone()
{
	return new CRevolverEffectObject(*this);
}

void CRevolverEffectObject::Animation2DNotify(const std::string& Name)
{
}

void CRevolverEffectObject::AnimationFrameEnd(const std::string& Name)
{
}

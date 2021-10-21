#include "ObjectDieEffectObject.h"
#include "../Animation2D/ObjectDieEffectAnimation2D.h"
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
	CSharedPtr<CMaterial> SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->AddTexture("PlayerTex", TEXT("teemo.png"));
	m_Sprite->CreateAnimation2D<CObjectDieEffectAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->SetSequencePlayRate("RevolverEffect", 4.f);
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

void CObjectDieEffectObject::AnimationFrameEnd(const std::string& Name)
{
}

#include "ShortSwordEffectObject.h"
#include "../Animation2D/ShortSwordEffectAnimation2D.h"
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

	m_Sprite->SetRelativeScale(Vector3(28.f, 40.f, 1.f));
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	CSharedPtr<CMaterial> SpriteMtrl = m_Sprite->GetMaterial(0);
	m_Sprite->CreateAnimation2D<CShortSwordEffectAnimation2D>();
	
	m_Animation2D = m_Sprite->GetAnimation2D();
	
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

void CShortSwordEffectObject::AnimationFrameEnd(const std::string& Name)
{
}

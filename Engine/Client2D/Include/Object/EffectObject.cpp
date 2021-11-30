#include "EffectObject.h"
#include <Resource/Material.h>
CEffectObject::CEffectObject() :
	m_Animation2D(nullptr)
{
}

CEffectObject::CEffectObject(const CEffectObject& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CEffectObject::~CEffectObject()
{
}

void CEffectObject::Start()
{
	CGameObject::Start();
}

bool CEffectObject::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();
	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();
	return true;
}

void CEffectObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CEffectObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEffectObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEffectObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEffectObject* CEffectObject::Clone()
{
	return new CEffectObject(*this);
}

void CEffectObject::Animation2DNotify(const std::string& Name)
{
}

void CEffectObject::AnimationFrameEnd(const std::string& Name)
{
	Active(false);
}

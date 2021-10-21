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
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");

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
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	SetRootComponent(m_Sprite);

	return true;
}

void CEffectObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Animation2D)
	{
		if (m_Animation2D->GetFrameEnd())
			Active(false);
	
	}
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
}

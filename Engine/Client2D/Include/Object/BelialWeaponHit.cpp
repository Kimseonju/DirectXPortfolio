#include "BelialWeaponHit.h"
CBelialWeaponHit::CBelialWeaponHit()
{
}

CBelialWeaponHit::CBelialWeaponHit(const CBelialWeaponHit& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBelialWeaponHit::~CBelialWeaponHit()
{
}

void CBelialWeaponHit::Start()
{
	CGameObject::Start();
}

bool CBelialWeaponHit::Init()
{
	if (!CGameObject::Init())
		return false;

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();
	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();
	return true;
}

void CBelialWeaponHit::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Animation2D->GetFrameEnd())
	{
		Active(false);
	}
}

void CBelialWeaponHit::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelialWeaponHit::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialWeaponHit::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialWeaponHit* CBelialWeaponHit::Clone()
{
	return new CBelialWeaponHit(*this);
}

#include "BelialWeaponCharge.h"
CBelialWeaponCharge::CBelialWeaponCharge()
{
}

CBelialWeaponCharge::CBelialWeaponCharge(const CBelialWeaponCharge& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBelialWeaponCharge::~CBelialWeaponCharge()
{
}

void CBelialWeaponCharge::Start()
{
	CGameObject::Start();
}

bool CBelialWeaponCharge::Init()
{
	if (!CGameObject::Init())
		return false;
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);
	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();
	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();
	m_Animation2D->SetIdleAnimation2D("Belial_WeaponCharge");
	m_Sprite->SetRelativeScale(65.f, 21.f,1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CBelialWeaponCharge::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBelialWeaponCharge::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelialWeaponCharge::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialWeaponCharge::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialWeaponCharge* CBelialWeaponCharge::Clone()
{
	return new CBelialWeaponCharge(*this);
}

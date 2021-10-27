#include "BelialWeaponCharge.h"
#include "../Animation2D/BelialWeaponChargeAnimation2D.h"
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
	m_Sprite->CreateAnimation2D<CBelialWeaponChargeAnimation2D>();
	m_Sprite->SetRelativeScale(65.f, 21.f,1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	SetRootComponent(m_Sprite);

	m_Animation2D = m_Sprite->GetAnimation2D();
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

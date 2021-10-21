
#include "WeaponArm.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "Weapon.h"
CWeaponArm::CWeaponArm() :
	m_Fire(false),
	m_FireTime(0.f),
	m_FireTimeMax(0.2f)
{
}

CWeaponArm::CWeaponArm(const CWeaponArm& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CWeaponArm::~CWeaponArm()
{
}

void CWeaponArm::Start()
{
	CGameObject::Start();
}

bool CWeaponArm::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	return true;
}

void CWeaponArm::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Dir == Object_Dir::Left)
	{
		m_Sprite->SetRelativePos(-20.f, 0.f, 0.f);
	}
	else if (m_Dir == Object_Dir::Right)
	{
		m_Sprite->SetRelativePos(20.f, 0.f, 0.f);
	}
}

void CWeaponArm::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CWeaponArm::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CWeaponArm::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CWeaponArm* CWeaponArm::Clone()
{
	return new CWeaponArm(*this);
}

void CWeaponArm::Animation2DNotify(const std::string& Name)
{
}

void CWeaponArm::Fire(float DeltaTime)
{
}
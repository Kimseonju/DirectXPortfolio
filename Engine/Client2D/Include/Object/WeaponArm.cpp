
#include "WeaponArm.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
CWeaponArm::CWeaponArm():
	m_Dir(Object_Dir::End),
	m_Animation2D(nullptr),
	m_DirPos(0.f,0.f,0.f)
{
}

CWeaponArm::CWeaponArm(const CWeaponArm& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Dir = obj.m_Dir;
	m_Animation2D = obj.m_Animation2D->Clone();
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
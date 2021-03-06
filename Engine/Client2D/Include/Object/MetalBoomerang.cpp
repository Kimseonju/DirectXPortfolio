
#include "MetalBoomerang.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "MetalBoomerangEffectObject.h"
#include "MetalBoomerangBullet.h"
#include <Scene/SceneResource.h>
CMetalBoomerang::CMetalBoomerang()
{
	SetItemTexture("MetalBoomerang", TEXT("Weapon/Range/MetalBoomerang.png"));
	m_WeaponType = Weapon_Type::Range;
	m_Type = ITEM_TYPE::Weapon_Two_Hand;
	m_Rank = ITEM_RANK::Normal;
	SetStatus("MetalBoomerang");
	m_ItemName = TEXT("부메랑");
	m_ItemText = TEXT("\"부메랑은 돌아오지만 사랑은 돌아오지 않는다.\"");
}

CMetalBoomerang::CMetalBoomerang(const CMetalBoomerang& obj) :
	CWeapon(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CMetalBoomerang::~CMetalBoomerang()
{
}

void CMetalBoomerang::Start()
{
	CWeapon::Start();
}

bool CMetalBoomerang::Init()
{
	CWeapon::Init();

	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	m_Sprite->SetWorldScale(31.f, 31.f, 0.f);
	SpriteMtrl->AddTexture("MetalBoomerang", TEXT("Weapon/Range/MetalBoomerang.png"));
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CMetalBoomerang::Update(float DeltaTime)
{
	CWeapon::Update(DeltaTime);

}

void CMetalBoomerang::PostUpdate(float DeltaTime)
{
	CWeapon::PostUpdate(DeltaTime);
}

void CMetalBoomerang::Collision(float DeltaTime)
{
	CWeapon::Collision(DeltaTime);
}

void CMetalBoomerang::Render(float DeltaTime)
{
	CWeapon::Render(DeltaTime);
}

CMetalBoomerang* CMetalBoomerang::Clone()
{
	return new CMetalBoomerang(*this);
}

void CMetalBoomerang::Animation2DNotify(const std::string& Name)
{
}

bool CMetalBoomerang::Attack(float Angle)
{
	if (!CWeapon::Attack(Angle))
	{
		return false;
	}
	if (!IsEnable())
	{
		return false;
	}

	Enable(false);
	
	m_pScene->GetResource()->FindSound("MetalBoomerangAttack")->Play();

	CMetalBoomerangEffectObject* obj = m_pScene->SpawnObject<CMetalBoomerangEffectObject>("MetalBoomerangEffectObject");

	obj->SetWorldPos(GetWorldPos());

	CMetalBoomerangBullet* pBullet = m_pScene->SpawnObject<CMetalBoomerangBullet>("Bullet");
	pBullet->SetComeback(true);
	pBullet->SetWeapon(this);
	pBullet->SetRelativePos(obj->GetWorldPos());
	pBullet->SetRelativeRotationZ(Angle - 90.f);
	pBullet->SetCollisionProfile("PlayerAttack");
	pBullet->AddRelativePos(pBullet->GetAxis(AXIS_Y) * 30.f);
	return true;
}

void CMetalBoomerang::Dash(CPlayer* player)
{
}

void CMetalBoomerang::Reload(CPlayer* player)
{
}

void CMetalBoomerang::GetHit()
{
}

void CMetalBoomerang::Equip()
{
	if (m_Owner)
	{
		m_Owner->SetRelativeRotationZ(0.f);
		SetRelativeRotationZ(0.f);
	}
	else
	{
	}
}


#include "Revolver.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "RevolverEffectObject.h"
#include "Bullet.h"
CRevolver::CRevolver()
{
	m_WeaponType = Weapon_Type::Range;
	SetItemTexture("Revolver", TEXT("Weapon/Range/Revolver.png"));
	m_Type = ITEM_TYPE::Weapon_One_Hand;
	m_Rank = ITEM_RANK::Normal;
	m_ItemName = TEXT("리볼버");
	m_ItemText = TEXT("\"휴대하기 좋고 순간적으로 빠르게 쏠 수 있는 총\"");
	m_Status.SetDamage(5);
	m_Status.SetDamageMax(8);
	m_Status.SetAttackSpeed(8.03f);
	m_price = 1000;
	SetMagazine(10);
}

CRevolver::CRevolver(const CRevolver& obj) :
	CWeapon(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CRevolver::~CRevolver()
{
}

void CRevolver::Start()
{
	CWeapon::Start();
}

bool CRevolver::Init()
{
	CWeapon::Init();

	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture("Revolver", TEXT("Weapon/Range/Revolver.png"));
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CRevolver::Update(float DeltaTime)
{
	CWeapon::Update(DeltaTime);
	
}

void CRevolver::PostUpdate(float DeltaTime)
{
	CWeapon::PostUpdate(DeltaTime);
}

void CRevolver::Collision(float DeltaTime)
{
	CWeapon::Collision(DeltaTime);
}

void CRevolver::Render(float DeltaTime)
{
	CWeapon::Render(DeltaTime);
}

CRevolver* CRevolver::Clone()
{
	return new CRevolver(*this);
}

void CRevolver::Animation2DNotify(const std::string& Name)
{
}

bool CRevolver::Attack(float Angle)
{
	if (!CWeapon::Attack(Angle))
		return false;
	
	if (m_Dir == Object_Dir::Left)
	{
		m_Rebound = -30.f;
	}
	else
	{
		m_Rebound = 30.f;
	}
	CRevolverEffectObject* obj = m_pScene->SpawnObject<CRevolverEffectObject>("ShortSwordEffectObject");

	obj->SetWorldPos(GetWorldPos());
	obj->SetRelativeRotationZ(Angle);
	Vector3 Axis = Vector3::AxisY(Angle - 90.f);
	obj->AddRelativePos(Axis * 50.f);

	CBullet* pBullet = m_pScene->SpawnObject<CBullet>("Bullet");

	pBullet->SetRelativePos(obj->GetWorldPos());
	pBullet->SetRelativeRotationZ(Angle- 90.f);
	pBullet->SetCollisionProfile("PlayerAttack");
	return true;
}

void CRevolver::Dash(CPlayer* player)
{
}

void CRevolver::Reload(CPlayer* player)
{
}

void CRevolver::GetHit()
{
}

void CRevolver::Equip()
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


#include "Weapon.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/PlayerAnimation2D.h"
#include "Engine.h"
#include "EffectObject.h"
CWeapon::CWeapon() :
	m_PlayAttack(false),
	m_WeaponType(Weapon_Type::Melee),
	m_Rebound(0.f),
	m_Dir(Object_Dir::Right)
{
	Enable(false);
}

CWeapon::CWeapon(const CWeapon& obj) :
	CItem(obj)
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::Start()
{
	CItem::Start();
}

bool CWeapon::Init()
{
	CItem::Init();


	return true;
}

void CWeapon::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);

	if (!m_MapDrop)
	{
		if (m_Reload)
		{
			m_CurrentReloadDelay += DeltaTime;
		}
		m_CurrentAttackDelay += DeltaTime;

		if (m_BulletMaxCount != 0 && m_BulletCount == 0)
		{
			Reload();
		}

		if (m_WeaponType == Weapon_Type::Range)
		{
			if (m_Rebound > 0.1f)
			{
				m_Rebound -= DeltaTime * 100.f;
			}
			else if (m_Rebound < -0.1f)
				m_Rebound += DeltaTime * 100.f;
			else if (m_Rebound > 30.f || m_Rebound < 30.f || m_Rebound<0.1f || m_Rebound>-0.1f)
			{
				m_Rebound = 0.f;
			}
		}

		//if (m_Dir == Object_Dir::Left)
		//{
		//	m_Sprite->SetRelativePos(10.f, 0.f, 0.f);
		//	m_Sprite->SetVerticalReverse2DEnable(true);
		//}
		//else if (m_Dir == Object_Dir::Right)
		//{
		//	m_Sprite->SetRelativePos(-10.f, 0.f, 0.f);
		//	m_Sprite->SetVerticalReverse2DEnable(false);
		//}
	}
	
}

void CWeapon::PostUpdate(float DeltaTime)
{
	CItem::PostUpdate(DeltaTime);
}

void CWeapon::Collision(float DeltaTime)
{
	CItem::Collision(DeltaTime);
}

void CWeapon::Render(float DeltaTime)
{
	CItem::Render(DeltaTime);
}

CWeapon* CWeapon::Clone()
{
	return new CWeapon(*this);
}

void CWeapon::Animation2DNotify(const std::string& Name)
{
}

bool CWeapon::Attack(float Angle)
{
	float AttackSpeed=1.f/GetAttackSpeed();
	float ReloadSpeed = GetReloadSpeed();
	if (m_CurrentAttackDelay >= AttackSpeed)
	{
		if (m_Reload)
		{
			if (m_CurrentReloadDelay < ReloadSpeed)
				return false;
			else
			{
				m_Reload = false;
			}
		}
		m_CurrentAttackDelay = 0.f;

		if (m_BulletMaxCount != 0)
		{
			m_BulletCount--;
		}
		return true;
	}
	else
	{
		return false;
	}
}

void CWeapon::Dash(CPlayer* player)
{
}

void CWeapon::Reload()
{
	m_Reload = true;
	m_CurrentReloadDelay = 0.f;
	m_BulletCount = m_BulletMaxCount;
}

void CWeapon::GetHit()
{
}

void CWeapon::Equip()
{
}

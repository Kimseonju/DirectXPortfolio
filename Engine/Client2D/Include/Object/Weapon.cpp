
#include "Weapon.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include <Resource/ResourceManager.h>
#include <Resource/Sound.h>
#include <Scene/SceneResource.h>
CWeapon::CWeapon() :
	m_PlayAttacking(false),
	m_WeaponType(Weapon_Type::Melee),
	m_Rebound(0.f),
	m_Dir(Object_Dir::Right),
	m_ReloadEffect(false),
	m_Animation2D(nullptr),
	m_CurrentAttackDelay(0.f),
	m_CurrentReloadDelay(0.f),
	m_Reload(false)
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
		if (m_Skill)
		{
			m_SkillDelay += DeltaTime;
			if (m_SkillDelay >= m_SkillDelayMax)
			{
				m_SkillDelay = m_SkillDelayMax;
			}
		}
		if (m_Reload)
		{
			m_CurrentReloadDelay += DeltaTime;
			float ReloadSpeed = GetReloadSpeed();

			if (m_CurrentReloadDelay >= ReloadSpeed)
			{
				m_CurrentReloadDelay = 0.f;
				m_Reload = false;
				m_ReloadEffect = true;
				m_Status->Reload();
				m_pScene->GetResource()->FindSound("Reload2")->Play();
				//사운드재생
			}

		}
		else
		{
			if (IsMagazine() && GetMagazine() == 0)
			{
				Reload();
			}
		}
		m_CurrentAttackDelay += DeltaTime;

		

		if (m_WeaponType == Weapon_Type::Range)
		{
			if (m_Rebound > 0.1f)
			{
				m_Rebound -= DeltaTime * 100.f;
			}
			else if (m_Rebound<0.1f || m_Rebound>-0.1f)
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
	float AttackSpeed = 1.f / GetAttackSpeed();
	float ReloadSpeed = GetReloadSpeed();
	if (m_CurrentAttackDelay >= AttackSpeed)
	{
		if (m_Reload)
		{
			return false;
		}
		m_CurrentAttackDelay = 0.f;

		if (IsMagazine())
		{
			m_Status->MagazineFire();
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool CWeapon::SkillAttack(float Angle)
{
	float AttackSpeed = 1.f / GetAttackSpeed();
	float ReloadSpeed = GetReloadSpeed();
	if (m_CurrentAttackDelay >= AttackSpeed)
	{
		if (m_Reload)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	if (m_SkillDelay >= m_SkillDelayMax)
	{
		m_SkillDelay = 0.f;
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

	//사운드재생

	m_pScene->GetResource()->FindSound("Reload")->Play();
}

void CWeapon::GetHit()
{
}

void CWeapon::Equip()
{
}

bool CWeapon::IsAttack()
{
	float AttackSpeed = 1.f / GetAttackSpeed();
	float ReloadSpeed = GetReloadSpeed();
	if (m_CurrentAttackDelay >= AttackSpeed)
	{
		if (m_Reload)
		{
			return false;
		}
		return true;
	}
	return false;
}

void CWeapon::SetSKillTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTexture(Name, FileName, PathName);

		m_SkillImage = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_SkillImage = CResourceManager::GetInst()->FindTexture(Name);
	}
}
#include "BasicStatus.h"
#include "GlobalValue.h"
#include "EngineMath.h"
CBasicStatus::CBasicStatus() :
	m_HP(0),
	m_HPMax(9999),
	m_Dash(0),
	m_DashMax(0),
	m_AttackSpeed(1.f),
	m_OldAttackSpeed(1.f),
	m_ReloadSpeed(1.f),
	m_OldReloadSpeed(1.f),
	m_MoveSpeed(0.f),
	m_Damage(0),
	m_DamageMax(0),
	m_Armor(0),
	m_Critical(0),
	m_Evasion(0),
	m_Magazine(0),
	m_MagazineMax(0),
	m_Price(1000)
{
}

CBasicStatus::~CBasicStatus()
{
}

void CBasicStatus::Dash()
{
	m_Dash--;
}

bool CBasicStatus::SubHP(int HP)
{
	m_HP -= HP;
	return true;
}

void CBasicStatus::SetHP(int HP)
{
	m_HP = HP;
	if (m_HP > m_HPMax)
		m_HP = m_HPMax;
}

void CBasicStatus::SetHPMax(int HP)
{
	m_HPMax = HP;
}

void CBasicStatus::SetDash(int Dash)
{
	m_Dash = Dash;
}

void CBasicStatus::SetDashMax(int Dash)
{
	m_DashMax = Dash;
}

void CBasicStatus::SetAttackSpeed(float Attack)
{
	m_AttackSpeed = Attack;
}

void CBasicStatus::SetReloadSpeed(float Reload)
{
	m_ReloadSpeed = Reload;
}

void CBasicStatus::SetMoveSpeed(float MoveSpeed)
{
	m_MoveSpeed = MoveSpeed;
}

void CBasicStatus::SetDamage(int Damage)
{
	m_Damage = Damage;
}

void CBasicStatus::SetDamageMax(int Damage)
{
	m_DamageMax = Damage;
}

void CBasicStatus::SetArmor(int Armor)
{
	m_Armor = Armor;
}

void CBasicStatus::SetCritical(int Critical)
{
	m_Critical = Critical;
}

void CBasicStatus::SetEvasion(int Evasion)
{
	m_Evasion = Evasion;
}

int CBasicStatus::GetHP() const
{
	return m_HP;
}

int CBasicStatus::GetHPMax() const
{
	return m_HPMax;
}

int CBasicStatus::GetDash() const
{
	return m_Dash;
}

int CBasicStatus::GetDashMax() const
{
	return m_DashMax;
}

float CBasicStatus::GetAttackSpeed() const
{
	return m_AttackSpeed;
}

float CBasicStatus::GetReloadSpeed() const
{
	return m_ReloadSpeed;
}

float CBasicStatus::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

int CBasicStatus::GetAttackDamage() const
{
	return GetRandom(m_Damage, m_DamageMax);
}

int CBasicStatus::GetDamage() const
{
	return m_Damage;
}

int CBasicStatus::GetDamageMax() const
{
	return m_DamageMax;
}

int CBasicStatus::GetArmor() const
{
	return m_Armor;
}

int CBasicStatus::GetCritical() const
{
	return m_Critical;
}

int CBasicStatus::GetEvasion() const
{
	return m_Evasion;
}

void CBasicStatus::AttachWeapon(CBasicStatus* Weapon)
{
	m_OldAttackSpeed = m_AttackSpeed;
	m_OldReloadSpeed = m_ReloadSpeed;
	m_AttackSpeed = Weapon->m_AttackSpeed;
	m_ReloadSpeed = Weapon->m_ReloadSpeed;
	m_Damage += Weapon->m_Damage;
	m_DamageMax += Weapon->m_DamageMax;
}

void CBasicStatus::DetachWeapon(CBasicStatus* Weapon)
{
	m_AttackSpeed = m_OldAttackSpeed;
	m_ReloadSpeed = m_OldReloadSpeed;
	m_Damage -= Weapon->m_Damage;
	m_DamageMax -= Weapon->m_DamageMax;
}

CBasicStatus* CBasicStatus::Clone()
{
	return new CBasicStatus(*this);
}

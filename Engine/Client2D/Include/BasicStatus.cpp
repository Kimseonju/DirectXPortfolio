#include "BasicStatus.h"
#include "GlobalValue.h"
CBasicStatus::CBasicStatus() :
	m_HP(0.f),
	m_HPMax(0.f),
	m_Dash(0.f),
	m_DashMax(0.f),
	m_AttackSpeed(1.f),
	m_OldAttackSpeed(1.f),
	m_ReloadSpeed(1.f),
	m_OldReloadSpeed(1.f),
	m_MoveSpeed(0.f),
	m_Damage(0.f),
	m_DamageMax(0.f),
	m_Armor(0.f),
	m_Critical(0.f),
	m_Evasion(0.f)
{
}

CBasicStatus::CBasicStatus(const CBasicStatus& status)
{
	m_HP = status.m_HP;
	m_HPMax = status.m_HPMax;
	m_Dash = status.m_Dash;
	m_DashMax = status.m_DashMax;
	m_AttackSpeed = status.m_AttackSpeed;
	m_ReloadSpeed = status.m_ReloadSpeed;
	m_MoveSpeed = status.m_MoveSpeed;
	m_Damage = status.m_Damage;
	m_DamageMax = status.m_DamageMax;
	m_Armor = status.m_Armor;
	m_Critical = status.m_Critical;
	m_Evasion = status.m_Evasion;
}

CBasicStatus::~CBasicStatus()
{
}

void CBasicStatus::Dash()
{
	m_Dash--;
}

void CBasicStatus::SetHP(int HP)
{
	m_HP = HP;
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
	int Damage=m_DamageMax - m_Damage;
	Damage=CGlobalValue::GetRandom(Damage);

	return m_Damage+Damage;
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

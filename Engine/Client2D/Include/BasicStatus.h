#pragma once
class CBasicStatus
{

public:
	CBasicStatus();
	~CBasicStatus();

protected:
	int m_HP;
	int m_HPMax;
	int m_Dash;
	int m_DashMax;
	//초당 몇번공격하는지
	float m_AttackSpeed; //0~1
	float m_OldAttackSpeed;

	float m_ReloadSpeed; //0~1
	float m_OldReloadSpeed;
	float m_MoveSpeed;
	int m_Damage;
	int m_DamageMax;
	int m_Armor; //방어력
	int m_Critical;
	int m_Evasion; //회피
	
public:
	void Dash();
public:

	void SetHP(int HP);
	void SetHPMax(int HP);
	void SetDash(int Dash);
	void SetDashMax(int Dash);
	void SetAttackSpeed(float Attack);
	void SetReloadSpeed(float Reload);
	void SetMoveSpeed(float MoveSpeed);
	void SetDamage(int Damage);
	void SetDamageMax(int Damage);
	void SetArmor(int Armor);
	void SetCritical(int Critical);
	void SetEvasion(int Evasion);


	int GetHP()			 const;
	int GetHPMax()		 const;
	int GetDash()		 const;
	int GetDashMax()	 const;
	float GetAttackSpeed()		 const;
	float GetReloadSpeed()		 const;
	float GetMoveSpeed()	 const;
	int GetAttackDamage()		const;
	int GetDamage()		const;
	int GetDamageMax()	 const;
	int GetArmor()		 const;
	int GetCritical()	 const;
	int GetEvasion()	 const;

public:

	void AttachWeapon(CBasicStatus* Weapon);
	void DetachWeapon(CBasicStatus* Weapon);
	 CBasicStatus* Clone();
};


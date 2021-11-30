#pragma once

#include "Item.h"
#include "../GlobalValue.h"
#include "../Animation2D/Animation2D_FSM.h"
/*

������ݽ� 90�� �����̸鼭 �����Ѵ�.
�ѹ� �����Ҷ� 90�� �÷��� ���̳ʽ� ���ָ� �� Arm������
�� �ٶ󺸴¹��� 45��+-
������ġ�� ĳ������ġ���� ���� ��,�ڷ�
*/
class CWeapon :
	public CItem
{
	friend class CScene;

protected:
	CWeapon();
	CWeapon(const CWeapon& obj);
	virtual ~CWeapon();

protected:
	CAnimation2D_FSM* m_Animation2D;
	float m_CurrentAttackDelay; 
	float m_CurrentReloadDelay;
	bool m_Reload;
	//�ִϸ��̼Ǿ��� ����������Ȯ��
	bool m_PlayAttacking;
	Weapon_Type m_WeaponType;
	float m_Rebound;
	Object_Dir m_Dir;
	bool m_ReloadEffect;
public:

	bool IsReloadEffect()
	{
		return m_ReloadEffect;
	}
	void SetReloadEffect(bool Effect)
	{
		m_ReloadEffect = Effect;
	}
	void SetDir(Object_Dir Dir)
	{
		m_Dir = Dir;
	}
	float GetRebound() const
	{
		return m_Rebound;
	}

	float GetCurrentAttackDelay() const
	{
		return m_CurrentAttackDelay;
	}
	float GetReloadPercent()
	{
		if (m_Reload)
		{
			float ReloadSpeed = GetReloadSpeed();
			float Percent = m_CurrentReloadDelay / ReloadSpeed;
			return Percent > 1.f ? 1.f : Percent;
		}
		else
		{
			return 0.f;
		}
	}
	bool IsAttacking() const
	{
		return m_PlayAttacking;
	}
	void SetCurrentAttackDelay(float Delay)
	{
		m_CurrentAttackDelay = Delay;
	}
	void SetWeaponType(Weapon_Type Type)
	{
		m_WeaponType = Type;
	}
	Weapon_Type GetWeaponType() const
	{
		return m_WeaponType;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CWeapon* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	virtual bool Attack(float Angle);
	virtual void Dash(CPlayer* player);
	virtual void Reload();
	// �ǰ�
	virtual void GetHit();
	// ������ ����
	virtual void Equip();
	bool IsAttack();

};

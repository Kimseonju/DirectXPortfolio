#pragma once

#include "Item.h"
#include "../GlobalValue.h"
#include "../Animation2D/Animation2D_FSM.h"
/*

무기공격시 90도 움직이면서 공격한다.
한번 공격할때 90도 플러스 마이너스 해주면 됨 Arm에서만
즉 바라보는방향 45도+-
무기위치는 캐릭터위치에서 조금 앞,뒤로
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
	//애니메이션쓸때 공격중인지확인
	bool m_PlayAttacking;
	Weapon_Type m_WeaponType;
	float m_Rebound;
	Object_Dir m_Dir;
	bool m_ReloadEffect;
	float m_SkillDelay;
	float m_SkillDelayMax;
	bool m_Skill;
	CTexture* m_SkillImage;

public:

	CTexture* GetSkillTexture()
	{
		return m_SkillImage;
	}
	float GetSkillDelayMax()const
	{
		return m_SkillDelayMax;
	}
	float GetSkillDelay() const
	{
		return m_SkillDelay;
	}
	bool IsSkill()
	{
		return m_Skill;
	}
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
	virtual bool SkillAttack(float Angle);
	virtual void Dash(CPlayer* player);
	virtual void Reload();
	// 피격
	virtual void GetHit();
	// 아이템 장착
	virtual void Equip();
	bool IsAttack();
	void SetSKillTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName= TEXTURE_PATH);
};

#pragma once

#include "Item.h"
#include "Component/SpriteComponent.h"
#include "../GlobalValue.h"
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
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_Animation2D;
	
protected:
	float m_CurrentAttackDelay; 
	int m_BulletMaxCount; 
	int m_BulletCount; 
	float m_CurrentReloadDelay;
	bool m_Reload;
	//�ִϸ��̼Ǿ��� ����������Ȯ��
	bool m_PlayAttack;
	Weapon_Type m_WeaponType;
	float m_Rebound;
	Object_Dir m_Dir;
public:


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

	bool IsAttack() const
	{
		return m_PlayAttack;
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

};

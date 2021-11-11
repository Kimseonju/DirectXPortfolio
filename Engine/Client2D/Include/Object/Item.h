#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "../BasicStatus.h"
#include "../GlobalValue.h"
#include "Component/SpriteComponent.h"
#include <Component/RigidBodyComponent.h>
#include "Component/ColliderBox2D.h"
class CPlayer;


class CItem :
    public CGameObject
{
	friend class CScene;

protected:
	CItem();
	CItem(const CItem& obj);
	virtual ~CItem();

protected:
	CBasicStatus m_Status;
	//아이템이름은 Ref에서 들고있게
	const TCHAR* m_ItemName;
	const TCHAR* m_ItemText;
	int m_price; // 가격
	bool    m_Fire;
	float   m_FireTime;
	float   m_FireTimeMax;
	ITEM_TYPE m_Type;
	ITEM_RANK m_Rank;
	class CTexture* m_ItemImage;
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CRigidBodyComponent> m_Body;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	float	m_UpdateDelay;
	//맵에 뿌린상태
	bool m_MapDrop;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CItem* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	// 피격
	virtual void GetHit(); 
	// 아이템 장착
	virtual void Equip(); 
	ITEM_TYPE GetType() const
	{
		return m_Type;
	}
	ITEM_RANK GetRank() const
	{
		return m_Rank;
	}
	int GetPrice() const  
	{ 
		return m_price; 
	}
	CBasicStatus* GetStatus()  
	{
		return &m_Status;
	}
public:

	const TCHAR* GetItemName() const;
	const TCHAR* GetItemRank() const;
	const TCHAR* GetItemType() const;
	const TCHAR* GetItemText() const;

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
	void SetItemTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);

	
	int GetHP()			 const;
	int GetHPMax()		 const;
	int GetDash()		 const;
	int GetDashMax()	 const;
	float GetAttackSpeed()		 const;
	float GetReloadSpeed()		 const;
	float GetMoveSpeed()	 const;
	int GetDamage()		const;
	int GetDamageMax()	 const;
	int GetArmor()		 const;
	int GetCritical()	 const;
	int GetEvasion()	 const;
	CTexture* GetItemTexture() const;
public:
	
	void DropCollisionBegin(const HitResult& result, CCollider* Collider);
	void SetHorizontalReverse2DEnable(bool Enable);
public:
	//동전이 드랍됬을때
	void Drop(float Angle, float Power);
	void Drop();
	//플레이어가 아이템과 충돌시
	virtual void StatePlayerItem();
};


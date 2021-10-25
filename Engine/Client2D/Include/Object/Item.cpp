#include "Item.h"
#include <Resource/ResourceManager.h>
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Resource/Texture.h>
CItem::CItem() :
	m_ItemImage(nullptr),
	m_Type(ITEM_TYPE::End),
	m_Rank(ITEM_RANK::End),
	m_ItemName(nullptr),
	m_ItemText(nullptr),
	m_price(0),
	m_Fire(false),
	m_FireTime(0.f),
	m_FireTimeMax(10.f)
{
}

CItem::CItem(const CItem& obj) :
	CGameObject(obj)
{
	m_ItemImage = obj.m_ItemImage;
	m_Type = obj.m_Type;
	m_Rank = obj.m_Rank;
	m_ItemName = obj.m_ItemName;
	m_ItemText = obj.m_ItemText;
	m_price = obj.m_price;
	m_Fire = obj.m_Fire;
	m_FireTime = obj.m_FireTime;
	m_FireTimeMax = obj.m_FireTimeMax;
}

CItem::~CItem()
{
}

void CItem::Start()
{
	CGameObject::Start();
}

bool CItem::Init()
{
	CGameObject::Init();
	return true;
}

void CItem::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CItem::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CItem::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CItem::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CItem* CItem::Clone()
{
	return nullptr;
}

void CItem::Animation2DNotify(const std::string& Name)
{
}


void CItem::GetHit()
{
}

void CItem::Equip()
{
}

const TCHAR* CItem::GetItemName() const
{
	return m_ItemName;
}

const TCHAR* CItem::GetItemRank() const
{
	switch (m_Rank)
	{
	case ITEM_RANK::Normal:
		return TEXT("일반 아이템");
		break;
	case ITEM_RANK::High:
		return TEXT("고급 아이템");
		break;
	case ITEM_RANK::Rare:
		return TEXT("희귀 아이템");
		break;
	case ITEM_RANK::Legend:
		return TEXT("전설 아이템");
		break;
	}
	return nullptr;
}

const TCHAR* CItem::GetItemType() const
{
	switch (m_Type)
	{
	case ITEM_TYPE::Weapon_One_Hand:
		return TEXT("한손");
		break;
	case ITEM_TYPE::Weapon_Two_Hand:
		return TEXT("양손");
		break;
	case ITEM_TYPE::Acc:
		return TEXT("액세사리");
		break;
	case ITEM_TYPE::End:
		break;
	default:
		break;
	}
	return nullptr;
}

const TCHAR* CItem::GetItemText() const
{
	return m_ItemText;
}

void CItem::SetHP(int HP)
{
	m_Status.SetHP(HP);
}

void CItem::SetHPMax(int HP)
{
	m_Status.SetHPMax(HP);
}

void CItem::SetDash(int Dash)
{
	m_Status.SetDash(Dash);
}

void CItem::SetDashMax(int Dash)
{
	m_Status.SetDashMax(Dash);
}

void CItem::SetAttackSpeed(float Attack)
{
	m_Status.SetAttackSpeed(Attack);
}

void CItem::SetReloadSpeed(float Reload)
{
	m_Status.SetReloadSpeed(Reload);
}

void CItem::SetMoveSpeed(float MoveSpeed)
{
	m_Status.SetMoveSpeed(MoveSpeed);
}

void CItem::SetDamage(int Damage)
{
	m_Status.SetDamage(Damage);
}

void CItem::SetDamageMax(int Damage)
{
	m_Status.SetDamageMax(Damage);
}

void CItem::SetArmor(int Armor)
{
	m_Status.SetArmor(Armor);
}

void CItem::SetCritical(int Critical)
{
	m_Status.SetCritical(Critical);
}

void CItem::SetEvasion(int Evasion)
{
	m_Status.SetEvasion(Evasion);
}

void CItem::SetItemTexture(const std::string& Name, const TCHAR* FileName,
	const std::string& PathName)
{
	if (m_pScene)
	{
		m_pScene->GetResource()->LoadTexture(Name, FileName, PathName);
		
		m_ItemImage = m_pScene->GetResource()->FindTexture(Name);
	}

	else
	{
		CResourceManager::GetInst()->LoadTexture(Name, FileName, PathName);

		m_ItemImage = CResourceManager::GetInst()->FindTexture(Name);
	}
}

int CItem::GetHP() const
{
	return m_Status.GetHP();
}

int CItem::GetHPMax() const
{
	return m_Status.GetHPMax();
}

int CItem::GetDash() const
{
	return m_Status.GetDash();
}

int CItem::GetDashMax() const
{
	return m_Status.GetDashMax();
}

float CItem::GetAttackSpeed() const
{
	return m_Status.GetAttackSpeed();
}

float CItem::GetReloadSpeed() const
{
	return m_Status.GetReloadSpeed();
}

float CItem::GetMoveSpeed() const
{
	return m_Status.GetMoveSpeed();
}

int CItem::GetDamage() const
{
	return m_Status.GetDamage();
}

int CItem::GetDamageMax() const
{
	return m_Status.GetDamageMax();
}

int CItem::GetArmor() const
{
	return m_Status.GetArmor();
}

int CItem::GetCritical() const
{
	return m_Status.GetCritical();
}

int CItem::GetEvasion() const
{
	return m_Status.GetEvasion();
}

CTexture* CItem::GetItemTexture() const
{
	return m_ItemImage;
}

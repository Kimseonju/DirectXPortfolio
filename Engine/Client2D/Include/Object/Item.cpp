#include "Item.h"
#include <Resource/ResourceManager.h>
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Resource/Texture.h>
#include "../ObjectStatusManager.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
#include "../UI/UIManager.h"
#include "../UI/Inventory.h"
#include <Scene/SceneResource.h>
CItem::CItem() :
	m_ItemImage(nullptr),
	m_Type(ITEM_TYPE::End),
	m_Rank(ITEM_RANK::End),
	m_ItemName(nullptr),
	m_ItemText(nullptr),
	m_Fire(false),
	m_MapDrop(false),
	m_UpdateDelay(0.f),
	m_Status(nullptr),
	m_bTileHit(false)
{
}

CItem::CItem(const CItem& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_ItemImage = obj.m_ItemImage;
	m_Type = obj.m_Type;
	m_Rank = obj.m_Rank;
	m_ItemName = obj.m_ItemName;
	m_ItemText = obj.m_ItemText;
	m_Fire = obj.m_Fire;
}

CItem::~CItem()
{
	SAFE_DELETE(m_Status);
}

void CItem::Start()
{
	CGameObject::Start();
}

bool CItem::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default2);
	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Body->SetGravityPower(500.f);
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");

	SetRootComponent(m_Sprite);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->AddChild(m_Body);

	m_Sprite->SetRelativeScale(38.f, 14.f, 1.f);
	m_Collider2D->SetCollisionProfile("Item");
	m_Collider2D->AddCollisionCallbackFunction<CItem>(Collision_State::Begin, this,
		&CItem::DropCollisionBegin);
	m_Collider2D->SetExtent(10.f, 10.f);

	m_Sprite->AddChild(m_Collider2D);
	m_Body->SetGravity(true);
	m_Body->SetGravityPower(500.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	return true;
}

void CItem::Update(float DeltaTime)
{
	if (m_UpdateDelay > 1.f)
	{
		CGameObject::Update(DeltaTime);
	}
	else
		m_UpdateDelay += DeltaTime;

	AddRelativePos(m_Body->GetMove());
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

void CItem::ItemUpdate(float DeltaTime)
{
}

void CItem::SetStatus(const std::string& Name)
{
	CBasicStatus* Status = CObjectStatusManager::GetInst()->FindStatus(Name);
	if (Status)
	{
		SAFE_DELETE(m_Status);
		m_Status = Status->Clone();;
	}

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
	m_Status->SetHP(HP);
}

void CItem::SetHPMax(int HP)
{
	m_Status->SetHPMax(HP);
}

void CItem::SetDash(int Dash)
{
	m_Status->SetDash(Dash);
}

void CItem::SetDashMax(int Dash)
{
	m_Status->SetDashMax(Dash);
}

void CItem::SetAttackSpeed(float Attack)
{
	m_Status->SetAttackSpeed(Attack);
}

void CItem::SetReloadSpeed(float Reload)
{
	m_Status->SetReloadSpeed(Reload);
}

void CItem::SetMoveSpeed(float MoveSpeed)
{
	m_Status->SetMoveSpeed(MoveSpeed);
}

void CItem::SetDamage(int Damage)
{
	m_Status->SetDamage(Damage);
}

void CItem::SetDamageMax(int Damage)
{
	m_Status->SetDamageMax(Damage);
}

void CItem::SetArmor(int Armor)
{
	m_Status->SetArmor(Armor);
}

void CItem::SetCritical(int Critical)
{
	m_Status->SetCritical(Critical);
}

void CItem::SetEvasion(int Evasion)
{
	m_Status->SetEvasion(Evasion);
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

void CItem::SetMagazine(int Magazine)
{
	m_Status->SetMagazine(Magazine);
}

int CItem::GetHP() const
{
	return m_Status->GetHP();
}

int CItem::GetHPMax() const
{
	return m_Status->GetHPMax();
}

int CItem::GetDash() const
{
	return m_Status->GetDash();
}

int CItem::GetDashMax() const
{
	return m_Status->GetDashMax();
}

float CItem::GetAttackSpeed() const
{
	return m_Status->GetAttackSpeed();
}

float CItem::GetReloadSpeed() const
{
	return m_Status->GetReloadSpeed();
}

float CItem::GetMoveSpeed() const
{
	return m_Status->GetMoveSpeed();
}

int CItem::GetDamage() const
{
	return m_Status->GetDamage();
}

int CItem::GetDamageMax() const
{
	return m_Status->GetDamageMax();
}

int CItem::GetArmor() const
{
	return m_Status->GetArmor();
}

int CItem::GetCritical() const
{
	return m_Status->GetCritical();
}

int CItem::GetEvasion() const
{
	return m_Status->GetEvasion();
}

int CItem::GetMagazine() const
{
	return m_Status->GetMagazine();
}

bool CItem::IsMagazine() const
{
	return m_Status->IsMagazine();
}

CTexture* CItem::GetItemTexture() const
{
	return m_ItemImage;
}

void CItem::DropCollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_bTileHit = true;
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		if (m_bTileHit)
		{
			if (CUIManager::GetInst()->GetInventory()->AddInventoryItem(this))
			{
				StateNoMapItem();
				m_pScene->GetResource()->FindSound("GetItem")->Play();
				CStage* CurStage = CStageManager::GetInst()->GetCurStage();
				CurStage->DeleteObject(this);
			}
		}
	}
}

void CItem::DropCollisionMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
	}
}

void CItem::ColDirVertical(float Angle, CCollider* Col)
{
	Vector3 Velocity = GetVelocity();
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2D->GetRelativeScale() / 2.f;
	Vector3 ColCheckPos = PlayerPos - ColPos;

	Vector3 WorldPos = GetWorldPos() - PlayerPos;

	//아래
	if (180.f <= Angle && Angle < 360.f)
	{
		m_Body->StopForceY();
		m_Body->StopForceX();
		m_Body->SetGravity(false);
		m_Body->SetJump(false);
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y += y;
		PlayerPos.y = XMove.y;
	}
	//위
	else if (0.f <= Angle && Angle < 180.f)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y -= y;
		PlayerPos.y = XMove.y;
	}

	SetWorldPos(PlayerPos + WorldPos);
}

void CItem::SetHorizontalReverse2DEnable(bool Enable)
{
	m_Sprite->SetHorizontalReverse2DEnable(Enable);
}

void CItem::SetVerticalReverse2DEnable(bool Enable)
{
	m_Sprite->SetVerticalReverse2DEnable(Enable);
}

void CItem::Drop(float Angle, float Power)
{
	m_Body->SetForce2D(Angle, Power);
	m_Body->SetGravity(true);
	Drop();
}

void CItem::Drop()
{
	m_MapDrop = true;
	m_UpdateDelay = 1.f;
}

void CItem::StateNoMapItem()
{
	m_MapDrop = false;
	m_Body->SetGravity(false);
	m_Collider2D->Enable(false);
	m_Sprite->SetPivot(0.f, 0.5f, 0.f);
	SetWorldPos(0.f, 0.f, 0.f);
	Enable(false);
}

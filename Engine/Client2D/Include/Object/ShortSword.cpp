
#include "ShortSword.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include "../BasicStatus.h"
#include "ShortSwordEffectObject.h"
#include "PlayerAttack.h"
#include <Scene/SceneResource.h>
CShortSword::CShortSword() 
{
	SetItemTexture("ShortSword", TEXT("Weapon/Melee/ShortSword.png"));
	m_Type = ITEM_TYPE::Weapon_One_Hand;
	m_Rank = ITEM_RANK::Normal;
	SetStatus("ShortSword");
	m_ItemName=TEXT("¼ô¼Òµå");
	m_ItemText= TEXT("\"°¡º±°í ÈÖµÎ¸£±â ÆíÇÑ °Ë\"");
}

CShortSword::CShortSword(const CShortSword& obj) :
	CWeapon(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CShortSword::~CShortSword()
{
}

void CShortSword::Start()
{
	CWeapon::Start();
}

bool CShortSword::Init()
{
	CWeapon::Init();
	m_Sprite->SetRelativeScale(19.f, 7.f, 0.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture("ShortSword", TEXT("Weapon/Melee/ShortSword.png"));
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CShortSword::Update(float DeltaTime)
{
	CWeapon::Update(DeltaTime);

	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CShortSword::PostUpdate(float DeltaTime)
{
	CWeapon::PostUpdate(DeltaTime);
}

void CShortSword::Collision(float DeltaTime)
{
	CWeapon::Collision(DeltaTime);
}

void CShortSword::Render(float DeltaTime)
{
	CWeapon::Render(DeltaTime);
}

CShortSword* CShortSword::Clone()
{
	return new CShortSword(*this);
}

void CShortSword::Animation2DNotify(const std::string& Name)
{
}

bool CShortSword::Attack(float Angle)
{
	if (!CWeapon::Attack(Angle))
	{
		return false;
	}

	CShortSwordEffectObject* obj = m_pScene->SpawnObject<CShortSwordEffectObject>("EffectAttack");
	if (m_Owner)
	{
		obj->SetWorldPos(m_Owner->GetWorldPos());
	}
	m_pScene->GetResource()->FindSound("SwordAttack")->Play();


	CPlayerAttack* pPlayerAttack = m_pScene->SpawnObject<CPlayerAttack>("CollisionPlayerAttack");
	pPlayerAttack->SetWorldPos(GetWorldPos());
	pPlayerAttack->SetRelativeRotationZ(Angle - 90.f);
	pPlayerAttack->AddRelativePos(pPlayerAttack->GetAxis(AXIS_Y) * 10.f);
	obj->SetRelativeRotationZ(Angle);
	Vector3 Axis = Vector3::AxisY(Angle - 90.f);
	obj->AddRelativePos(Axis * 10.f);
	return true;

}

void CShortSword::Dash(CPlayer* player)
{
}

void CShortSword::Reload(CPlayer* player)
{
}

void CShortSword::GetHit()
{
}

void CShortSword::Equip()
{
}

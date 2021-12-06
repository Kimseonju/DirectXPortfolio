
#include "CosmosSword.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include "../BasicStatus.h"
#include "ShortSwordEffectObject.h"
#include "PlayerAttack.h"
#include <Scene/SceneResource.h>
CCosmosSword::CCosmosSword()
{
	SetItemTexture("CosmosSwordIcon", TEXT("Weapon/Melee/CosmosSwordIcon.png"));
	m_Type = ITEM_TYPE::Weapon_One_Hand;
	m_Rank = ITEM_RANK::Normal;
	SetStatus("CosmosSword");
	m_ItemName = TEXT("우주검");
	m_ItemText = TEXT("\"이 검이 내뿜는 우주의 신비한 빛.\"");
	m_Skill = true;
	m_SkillDelayMax = 5.f;
	m_SkillDelay = 5.f;
	SetSKillTexture("cosmosSwordSkill");
}

CCosmosSword::CCosmosSword(const CCosmosSword& obj) :
	CWeapon(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CCosmosSword::~CCosmosSword()
{
}

void CCosmosSword::Start()
{
	CWeapon::Start();
}

bool CCosmosSword::Init()
{
	CWeapon::Init();
	m_Sprite->SetRelativeScale(19.f, 7.f, 0.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture("ShortSword", TEXT("Weapon/Melee/ShortSword.png"));
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CCosmosSword::Update(float DeltaTime)
{
	CWeapon::Update(DeltaTime);

	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CCosmosSword::PostUpdate(float DeltaTime)
{
	CWeapon::PostUpdate(DeltaTime);
}

void CCosmosSword::Collision(float DeltaTime)
{
	CWeapon::Collision(DeltaTime);
}

void CCosmosSword::Render(float DeltaTime)
{
	CWeapon::Render(DeltaTime);
}

CCosmosSword* CCosmosSword::Clone()
{
	return new CCosmosSword(*this);
}

void CCosmosSword::Animation2DNotify(const std::string& Name)
{
}

bool CCosmosSword::Attack(float Angle)
{
	if (!CWeapon::Attack(Angle))
	{
		return false;
	}

	CCosmosSwordEffectObject* obj = m_pScene->SpawnObject<CCosmosSwordEffectObject>("EffectAttack");
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

bool CCosmosSword::SkillAttack(float Angle)
{
	if (!CWeapon::SkillAttack(Angle))
	{
		return false;
	}
	//스킬사용!


	return true;
}

void CCosmosSword::Dash(CPlayer* player)
{
}

void CCosmosSword::Reload(CPlayer* player)
{
}

void CCosmosSword::GetHit()
{
}

void CCosmosSword::Equip()
{
}

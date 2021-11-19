
#include "SmallSkelBow.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EnemyArrow.h"
#include "../Animation2D/Animation2D_FSM.h"
CSmallSkelBow::CSmallSkelBow() :
	m_AttackAngle(0.f)
{
	Enable(true);
	m_WeaponType = Weapon_Type::Range;
	SetStatus("SmallSkelBow");
}

CSmallSkelBow::CSmallSkelBow(const CSmallSkelBow& obj) :
	CWeapon(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CSmallSkelBow::~CSmallSkelBow()
{
}

void CSmallSkelBow::Start()
{
	CWeapon::Start();
}

bool CSmallSkelBow::Init()
{
	CWeapon::Init();

	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//µå¶øÅÛ¾Æ´Ô
	m_Body->SetGravity(false);
	m_Collider2D->Enable(false);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("ShortSword", TEXT("MeleeWeapon/ShortSword.png"));
	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();
	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();
	m_Animation2D->SetIdleAnimation2D("SmallEnemyBowIdle");
	m_Animation2D->SetAttackAnimation2D("SmallEnemyBowAttack", false);
	m_Animation2D->SetFrameEndFunction<CSmallSkelBow>(this, &CSmallSkelBow::AnimationFrameEnd);
	m_Sprite->SetWorldScale(18.f, 13.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	return true;
}

void CSmallSkelBow::Update(float DeltaTime)
{
	CWeapon::Update(DeltaTime);

	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CSmallSkelBow::PostUpdate(float DeltaTime)
{
	CWeapon::PostUpdate(DeltaTime);
}

void CSmallSkelBow::Collision(float DeltaTime)
{
	CWeapon::Collision(DeltaTime);
}

void CSmallSkelBow::Render(float DeltaTime)
{
	CWeapon::Render(DeltaTime);
}

CSmallSkelBow* CSmallSkelBow::Clone()
{
	return new CSmallSkelBow(*this);
}

void CSmallSkelBow::Animation2DNotify(const std::string& Name)
{
	if (Name == "Attack")
	{
		CEnemyArrow* EnemyArrow = m_pScene->SpawnObject<CEnemyArrow>("EnemyArrow");
		EnemyArrow->SetWorldPos(GetWorldPos());
		EnemyArrow->SetWorldRotationZ(m_AttackAngle);

	}
}

bool CSmallSkelBow::Attack(float Angle)
{
	if (!CWeapon::Attack(Angle))
	{
		return false;
	}
	m_Animation2D->ChangeAttackAnimation2D();
	m_PlayAttacking = true;
	m_AttackAngle = Angle - 90.f;
	return true;

}

void CSmallSkelBow::Dash(CPlayer* player)
{
}

void CSmallSkelBow::Reload(CPlayer* player)
{
}

void CSmallSkelBow::GetHit()
{
}

void CSmallSkelBow::Equip()
{
}

void CSmallSkelBow::AnimationFrameEnd(const std::string& Name)
{
	m_PlayAttacking = false;
	m_Animation2D->ChangeIdleAnimation2D();
}

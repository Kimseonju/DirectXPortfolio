
#include "SkelSmallDagger.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include "EnemyAttack.h"
#include "../Animation2D/Animation2D_FSM.h"
#include <Scene/SceneResource.h>
CSkelSmallDagger::CSkelSmallDagger() 
{
	Enable(true);
	m_WeaponType = Weapon_Type::Melee;
	SetStatus("SkelSmallDagger");
}

CSkelSmallDagger::CSkelSmallDagger(const CSkelSmallDagger& obj) :
	CWeapon(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CSkelSmallDagger::~CSkelSmallDagger()
{
}

void CSkelSmallDagger::Start()
{
	CWeapon::Start();
}

bool CSkelSmallDagger::Init()
{
	CWeapon::Init();

	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//����۾ƴ�
	m_Body->SetGravity(false);
	m_Collider2D->Enable(false);
		
	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("ShortSword", TEXT("MeleeWeapon/ShortSword.png"));
	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();
	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();
	m_Animation2D->SetIdleAnimation2D("SmallEnemyDaggerIdle");
	m_Animation2D->SetAttackAnimation2D("SmallEnemyDaggerAttack", false);
	m_Animation2D->SetFrameEndFunction<CSkelSmallDagger>(this, &CSkelSmallDagger::AnimationFrameEnd);
	m_Sprite->SetWorldScale(26.f, 30.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f,0.f);
	return true;
}

void CSkelSmallDagger::Update(float DeltaTime)
{
	CWeapon::Update(DeltaTime);
	
	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CSkelSmallDagger::PostUpdate(float DeltaTime)
{
	CWeapon::PostUpdate(DeltaTime);
}

void CSkelSmallDagger::Collision(float DeltaTime)
{
	CWeapon::Collision(DeltaTime);
}

void CSkelSmallDagger::Render(float DeltaTime)
{
	CWeapon::Render(DeltaTime);
}

CSkelSmallDagger* CSkelSmallDagger::Clone()
{
	return new CSkelSmallDagger(*this);
}

void CSkelSmallDagger::Animation2DNotify(const std::string& Name)
{
	if (Name == "Attack")
	{
		m_pScene->GetResource()->FindSound("SkelSwordAttack1")->Play();
		CEnemyAttack* pEnemyAttack = m_pScene->SpawnObject<CEnemyAttack>("CollisionEnemyAttack");
		pEnemyAttack->SetDamage(m_Status->GetAttackDamage());
		pEnemyAttack->SetWorldPos(GetWorldPos());
	}
}

bool CSkelSmallDagger::Attack(float Angle)
{
	if (!CWeapon::Attack(Angle))
	{
		return false;
	}
	m_Animation2D->ChangeAnimation("SmallEnemyDaggerAttack");
	m_PlayAttacking = true;
	return true;
}

void CSkelSmallDagger::Dash(CPlayer* player)
{
}

void CSkelSmallDagger::Reload(CPlayer* player)
{
}

void CSkelSmallDagger::GetHit()
{
}

void CSkelSmallDagger::Equip()
{
}

void CSkelSmallDagger::AnimationFrameEnd(const std::string& Name)
{
	m_PlayAttacking = false;
	m_Animation2D->ChangeIdleAnimation2D();
}

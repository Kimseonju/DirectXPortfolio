
#include "Enemy.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/EnemyAnimation2D.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"
#include "ObjectDieEffectObject.h"
CEnemy::CEnemy() :
	m_ChildFire(false),
	m_ChildFireTime(0.f),
	m_ChildFireTimeMax(0.2f),
	m_StartGravity(false),
	m_State(Enemy_State::Idle),
	m_EnemyInfoWidget(nullptr)
{
}

CEnemy::CEnemy(const CEnemy& obj) :
	CGameObject(obj)
{
	m_ChildFire = false;

	m_Body = (CRigidBodyComponent*)FindSceneComponent("Body");
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
	m_AttackRangeCollider2D = (CColliderBox2D*)FindSceneComponent("AttackRangeCollider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_EnemyInfoWidgetComponent = (CWidgetComponent*)FindSceneComponent("InfoWidget");

	m_Status = obj.m_Status;
	
}

CEnemy::~CEnemy()
{
}

void CEnemy::Start()
{
	CGameObject::Start();
}

bool CEnemy::Init()
{
	CGameObject::Init();

	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_AttackRangeCollider2D = CreateSceneComponent<CColliderBox2D>("AttackRangeCollider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_EnemyInfoWidgetComponent = CreateSceneComponent<CWidgetComponent>("InfoWidget");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);

	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_Sprite->SetRelativePos(200.f, 300.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	//CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	//m_Sprite->CreateAnimation2D<CEnemyAnimation2D>();
	//m_Animation2D = m_Sprite->GetAnimation2D();


	m_Collider2D->SetExtent(50.f, 50.f);
	m_Collider2D->SetCollisionProfile("Enemy");
	m_Collider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionBegin);
	m_Sprite->AddChild(m_Collider2D);


	m_EnemyInfoWidget =m_EnemyInfoWidgetComponent->CreateWidget<CEnemyWorldInfoWidget>("EnemyWorldInfoWidget");
	m_EnemyInfoWidget->Enable(false);
	m_EnemyInfoWidgetComponent->SetRelativePos(-100.f, -100.f, 0.f);
	m_EnemyInfoWidgetComponent->SetRelativeScale(200.f, 70.f, 1.f);
	//
	m_Sprite->AddChild(m_EnemyInfoWidgetComponent);

	m_WeaponArm = m_pScene->SpawnObject<CWeaponArm>("basicWeaponArm");
	m_WeaponArm->SetRelativePos(0.f, 0.f, 0.f);
	PushObjectChild(m_WeaponArm);

	m_Status.SetMoveSpeed(200.f);
	m_Body->SetMoveSpeed(m_Status.GetMoveSpeed());
	m_Status.SetHP(30);
	m_Status.SetHPMax(30);
	return true;
}

void CEnemy::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (!m_StartGravity)
	{
		m_StartGravity = true;
		m_Body->SetJump(true);
	}
	m_EnemyInfoWidget->SetHPBar((float)m_Status.GetHP() / (float)m_Status.GetHPMax());


	if (m_Status.GetHP() <= 0)
	{
		CObjectDieEffectObject* Effect=m_pScene->SpawnObject<CObjectDieEffectObject>("DieEffect");
		Effect->SetWorldPos(GetWorldPos());
		Active(false);
	}


	//if (m_Weapon->IsAttack())
	//{
	//	return;
	//}
}

void CEnemy::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEnemy::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEnemy::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEnemy* CEnemy::Clone()
{
	return new CEnemy(*this);
}

void CEnemy::Animation2DNotify(const std::string& Name)
{
	
}

void CEnemy::AnimationFrameEnd(const std::string& Name)
{
}

void CEnemy::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		m_Body->SetJump(false);
	}

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status.SetHP(m_Status.GetHP()- CGlobalValue::MainPlayer->GetStatus().GetAttackDamage());
		m_EnemyInfoWidget->Enable(true);
	}

}

void CEnemy::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		Vector3 DestPos=result.DestObject->GetWorldPos();
		Vector3 Pos = GetWorldPos();
		Pos=Pos - DestPos;
		float Dir;
		if (m_Dir == Object_Dir::Left)
		{
			Dir = 270.f;
		}
		else
		{
			Dir = 90.f;
		}
		//¿ÞÂÊ ¿À¸¥ÂÊ
		m_Weapon->Attack(Dir);
	}

}

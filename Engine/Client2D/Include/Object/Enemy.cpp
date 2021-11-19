
#include "Enemy.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"
#include "ObjectDieEffectObject.h"
#include "ProgressBarObject.h"
#include "../ObjectStatusManager.h"
CEnemy::CEnemy() :
	m_ChildFire(false),
	m_ChildFireTime(0.f),
	m_ChildFireTimeMax(0.2f),
	m_State(Enemy_State::Idle),
	m_WallCol(false),
	m_StartGravity(false),
	m_Status(nullptr)
{
}

CEnemy::CEnemy(const CEnemy& obj) :
	CGameObject(obj)
{
	m_ChildFire = false;

	m_Body = (CRigidBodyComponent*)FindSceneComponent("Body");
	m_Collider2DHorizon = (CColliderBox2D*)FindSceneComponent("Collider2DHorizon");
	m_Collider2DVertical = (CColliderBox2D*)FindSceneComponent("Collider2DVertical");
	m_AttackRangeCollider2D = (CColliderBox2D*)FindSceneComponent("AttackRangeCollider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

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
	m_Collider2DHorizon = CreateSceneComponent<CColliderBox2D>("Collider2DHorizon");
	m_Collider2DVertical = CreateSceneComponent<CColliderBox2D>("Collider2DVertical");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_AttackRangeCollider2D = CreateSceneComponent<CColliderBox2D>("AttackRangeCollider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	//�׽�Ʈ�� 
	m_Status->SetHP(1);
	m_Status->SetHPMax(1);


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Collider2DHorizon);
	m_Sprite->AddChild(m_Collider2DVertical);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_AttackRangeCollider2D);

	m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	//CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();
	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();


	m_Collider2DHorizon->SetExtent(10.f, 1.f);
	m_Collider2DVertical->SetExtent(1.f, 10.f);
	m_Collider2D->SetExtent(10.f, 10.f);
	m_Collider2D->SetCollisionProfile("Enemy");
	m_Collider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionBegin);

	m_Collider2DHorizon->SetCollisionProfile("TileCheckCollsion");
	m_Collider2DVertical->SetCollisionProfile("TileCheckCollsion");
	m_Collider2DHorizon->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionHorizonBegin);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CEnemy>(Collision_State::Middle, this,
		&CEnemy::CollisionHorizonMiddle);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CEnemy>(Collision_State::End, this,
		&CEnemy::CollisionHorizonEnd);

	m_Collider2DVertical->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionVerticalBegin);
	m_Collider2DVertical->AddCollisionCallbackFunction<CEnemy>(Collision_State::Middle, this,
		&CEnemy::CollisionVerticalMiddle);
	m_Collider2DVertical->AddCollisionCallbackFunction<CEnemy>(Collision_State::End, this,
		&CEnemy::CollisionVerticalEnd);


	m_WeaponArm = m_pScene->SpawnObject<CWeaponArm>("basicWeaponArm");
	m_WeaponArm->SetRelativePos(0.f, 0.f, 0.f);
	PushObjectChild(m_WeaponArm);

	m_Status->SetMoveSpeed(200.f);
	m_Body->SetMoveSpeed(m_Status->GetMoveSpeed());
	m_Status->SetHP(30);
	m_Status->SetHPMax(30);


	m_EnemyFSM.CreateState("Find", this, &CEnemy::FindStay, &CEnemy::FindStart, &CEnemy::FindEnd);
	m_EnemyFSM.CreateState("Move", this, &CEnemy::MoveStay, &CEnemy::MoveStart, &CEnemy::MoveEnd);
	m_EnemyFSM.CreateState("Attack", this, &CEnemy::AttackStay, &CEnemy::AttackStart, &CEnemy::AttackEnd);
	m_EnemyFSM.CreateState("Die", this, &CEnemy::DieStay, &CEnemy::DieStart, &CEnemy::DieEnd);
	m_EnemyFSM.ChangeState("Find");


	//���α׷�����
	m_ProgressBar =m_pScene->SpawnObject<CProgressBarObject>("EnemyProgressBar");
	m_ProgressBar->SetOwner(this);
	m_ProgressBar->AddRelativePos(0.f, -10.f, 0.f);
	return true;
}

void CEnemy::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
	else
	{
		if (!m_StartGravity)
		{
			m_StartGravity = true;
			m_Body->SetGravity(true);
		}
	}
	m_EnemyFSM.Update();
	Vector3 Pos = GetWorldPos();
	Pos.y -= 10.f;
	m_ProgressBar->SetWorldPos(Pos);
	m_WallCol= false;
	m_ProgressBar->SetHPBar((float)m_Status->GetHP() / (float)m_Status->GetHPMax());


	


	//if (m_Weapon->IsAttack())
	//{
	//	return;
	//}
}

void CEnemy::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
}

void CEnemy::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
}

void CEnemy::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
}

CEnemy* CEnemy::Clone()
{
	return new CEnemy(*this);
}

void CEnemy::Animation2DNotify(const std::string& Name)
{
	
}

void CEnemy::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Sprite->Enable(bEnable);
	m_Collider2DHorizon->Enable(bEnable);
	m_Collider2DVertical->Enable(bEnable);
	m_Collider2D->Enable(bEnable);
	m_AttackRangeCollider2D->Enable(bEnable);
	m_Body->Enable(bEnable);
	m_ProgressBar->Enable(bEnable);
	m_Sprite->Enable(bEnable);
}

void CEnemy::SetStatus(const std::string& Name)
{
	CBasicStatus* Status=CObjectStatusManager::GetInst()->FindStatus(Name);
	if (Status)
	{
		m_Status = Status;
	}
}

void CEnemy::AnimationFrameEnd(const std::string& Name)
{
}

void CEnemy::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		Vector3 DestPos = result.DestObject->GetWorldPos();
		Vector3 Pos = GetWorldPos();
		Pos = Pos - DestPos;
		float Dir;
		if (m_Dir == Object_Dir::Left)
		{
			Dir = 270.f;
		}
		else
		{
			Dir = 90.f;
		}
		//���� ������
		m_Weapon->Attack(Dir);
	}

}

void CEnemy::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status->SetHP(m_Status->GetHP() - CGlobalValue::MainPlayer->GetStatus().GetAttackDamage());
		m_ProgressBar->Enable(true);
		if (m_Status->GetHP() <= 0)
		{
			CObjectDieEffectObject* Effect = m_pScene->SpawnObject<CObjectDieEffectObject>("DieEffect");
			Effect->SetWorldPos(GetWorldPos());
			Active(false);
			m_ProgressBar->Active(false);
		}

	}
}


void CEnemy::CollisionHorizonBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
	}

}

void CEnemy::CollisionHorizonMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
	}

}

void CEnemy::CollisionHorizonEnd(const HitResult& result, CCollider* Collider)
{

}

void CEnemy::CollisionVerticalBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}

}

void CEnemy::CollisionVerticalMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}

}

void CEnemy::CollisionVerticalEnd(const HitResult& result, CCollider* Collider)
{

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		if (!m_WallCol)
		{
			m_Body->SetGravity(true);
			m_Body->SetJump(true);
		}
	}
}


void CEnemy::ColDirHorizon(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2DHorizon->GetRelativeScale() / 2.f;


	if (90.f <= Angle && Angle < 270.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x += x;
		PlayerPos.x = XMove.x;

	}
	//�����ʹ���
	else if (270.f <= Angle || Angle < 90.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x -= x;
		PlayerPos.x = XMove.x;

	}

	SetWorldPos(PlayerPos);
}

void CEnemy::ColDirVertical(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2DVertical->GetRelativeScale() / 2.f;


	//�Ʒ�
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
	//��
	else if (0.f < Angle || Angle < 180.f || 360.f <= Angle)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y -= y;
		PlayerPos.y = XMove.y;
	}

	SetWorldPos(PlayerPos);
}



void CEnemy::DieStart()
{
	//������ ����Ʈ���� �� ����
}

void CEnemy::DieStay()
{
	Active(false);
}

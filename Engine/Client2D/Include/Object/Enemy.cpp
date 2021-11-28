
#include "Enemy.h"
#include "Input.h"
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
#include "TextObject.h"
#include "../UI/UIManager.h"
#include "../UI/MiniMap.h"
CEnemy::CEnemy() :
	m_ChildFire(false),
	m_ChildFireTime(0.f),
	m_ChildFireTimeMax(0.2f),
	m_State(Enemy_State::Idle),
	m_WallCol(false),
	m_StartGravity(false),
	m_Status(nullptr),
	m_EnemyHit(0.f)
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
	SAFE_DELETE(m_Status);
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


	m_EnemyInfoWidgetComponent = CreateSceneComponent<CWidgetComponent>("InfoWidget");
	m_EnemyInfoWidgetComponent->SetWorldPos(0.f, 0.f, 0.f);
	m_EnemyInfoWidget = m_EnemyInfoWidgetComponent->CreateWidget<CEnemyWorldInfoWidget>("EnemyWorldInfoWidget");
	//m_EnemyInfoWidget->Enable(false);
	m_EnemyInfoWidgetComponent->SetRelativePos(-90.f, -60.f, 0.f);
	//

	//테스트용 
	m_Status->SetHP(1);
	m_Status->SetHPMax(1);


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Collider2DHorizon);
	m_Sprite->AddChild(m_Collider2DVertical);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_AttackRangeCollider2D);
	m_Sprite->AddChild(m_EnemyInfoWidgetComponent);

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


	//프로그래스바
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
	m_WallCol= false;


	m_EnemyInfoWidget->SetHPBar((float)m_Status->GetHP() / (float)m_Status->GetHPMax());
	
	CMaterial* Material=m_Sprite->GetMaterial(0);
	if (m_EnemyHit > 0.f)
	{
		Material->SetBaseColor(1.f, 0.f, 0.f, 1.f);
		m_EnemyHit -= DeltaTime;
	}
	else
	{
		Material->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	}
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

void CEnemy::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 4.f), Vector4(1.f,0.f,0.f,1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);

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
	m_Sprite->Enable(bEnable);
}

void CEnemy::SetStatus(const std::string& Name)
{
	CBasicStatus* Status=CObjectStatusManager::GetInst()->FindStatus(Name);
	if (Status)
	{
		SAFE_DELETE(m_Status);
		m_Status = Status->Clone();
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
		//왼쪽 오른쪽
		m_Weapon->Attack(Dir);
	}

}

void CEnemy::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_EnemyHit = 0.3f;
		int CriticalCheck = GetRandom(0, 100);
		bool bCritical = false;
		if (CGlobalValue::MainPlayer->GetStatus().GetCritical() > CriticalCheck)
		{
			bCritical = true;
		}
		int Damage = CGlobalValue::MainPlayer->GetAttackDamage(bCritical);
		m_Status->SetHP(m_Status->GetHP() - Damage);
		m_EnemyInfoWidget->Enable(true);
		CTextObject* TextObj = m_pScene->SpawnObject<CTextObject>("TextObject");
		TextObj->SetText(std::to_string(Damage));
		TextObj->SetWorldPos(GetWorldPos());
		TextObj->Damage(bCritical);
		if (m_Status->GetHP() <= 0)
		{
			CObjectDieEffectObject* Effect = m_pScene->SpawnObject<CObjectDieEffectObject>("DieEffect");
			Effect->SetWorldPos(GetWorldPos());
			Active(false);
			if (m_Weapon)
			{
				m_Weapon->Active(false);
			}
			DropGold();
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
	//오른쪽방향
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
	//죽으면 이펙트생성 후 삭제
}

void CEnemy::DieStay()
{
	Active(false);
}

#include "Ghost.h"
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
#include "EnemyAttack.h"
#include "Gold.h"
CGhost::CGhost() :
	m_PlayerFind(false)
{
	SetStatus("Ghost");
}

CGhost::CGhost(const CGhost& obj) :
	CEnemy(obj)
{
}

CGhost::~CGhost()
{
}

void CGhost::Start()
{
	CEnemy::Start();
}

bool CGhost::Init()
{
	CEnemy::Init();

	m_Collider2D->SetExtent(8.f, 10.f);
	m_AttackRangeCollider2D->SetExtent(7.f, 9.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	SetWorldScale(20.f, 20.f, 0.f);
	m_Animation2D->SetIdleAnimation2D("GhostMove");
	m_Animation2D->SetMoveAnimation2D("GhostMove");
	m_Animation2D->SetAttackAnimation2D("GhostAttack", false);
	m_Animation2D->ChangeIdleAnimation2D();
	m_Status->SetMoveSpeed(50.f);
	m_Body->SetMoveSpeed(m_Status->GetMoveSpeed());
	m_Body->SetGravityNo();
	return true;
}

void CGhost::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);
	if (m_StartTimer > 0.f)
		return;


	AddRelativePos(m_Body->GetMove());
}

void CGhost::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
}

void CGhost::Collision(float DeltaTime)
{
	CEnemy::Collision(DeltaTime);
}

void CGhost::Render(float DeltaTime)
{
	CEnemy::Render(DeltaTime);
}

CGhost* CGhost::Clone()
{
	return new CGhost(*this);
}

void CGhost::Animation2DNotify(const std::string& Name)
{
	if (Name == "Attack")
	{
		
	m_GhostAttack = false;

	CEnemyAttack* pEnemyAttack = m_pScene->SpawnObject<CEnemyAttack>("CollisionEnemyAttack");
	pEnemyAttack->SetWorldPos(GetWorldPos());
	}
}

void CGhost::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
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
		m_GhostAttack = true;
		m_State = Enemy_State::Attack;
	}
}

void CGhost::DropGold()
{
	int DropCount = GetRandom(0, 4);
	for (int i = 0; i < DropCount; ++i)
	{
		CGold* Gold = m_pScene->SpawnObject<CGold>("Gold");
		Gold->SetWorldPos(GetWorldPos());
		Gold->AddWorldPos(0.f, 20.f, 0.f);
		Gold->Drop((float)GetRandom(0, 180), 300.f);
	}
}

void CGhost::AnimationFrameEnd(const std::string& Name)
{
}

void CGhost::CollisionHorizonBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
	}
}

void CGhost::CollisionHorizonMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
	}
}

void CGhost::CollisionHorizonEnd(const HitResult& result, CCollider* Collider)
{
}

void CGhost::CollisionVerticalBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
}

void CGhost::CollisionVerticalMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
}

void CGhost::CollisionVerticalEnd(const HitResult& result, CCollider* Collider)
{
}

void CGhost::ColDirHorizon(float Angle, CCollider* Col)
{
	Vector3 Velocity = GetVelocity();
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

void CGhost::ColDirVertical(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2DVertical->GetRelativeScale() / 2.f;


	//아래
	if (180.f <= Angle && Angle < 360.f)
	{
		m_Body->StopForceY();
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

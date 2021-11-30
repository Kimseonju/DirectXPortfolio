#include "GoldBullion.h"
#include <Input.h>
#include "TextObject.h"
#include "Scene/Scene.h"
#include "Player.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
#include <Scene/SceneResource.h>
CGoldBullion::CGoldBullion() :
	m_Open(false),
	m_WallCol(false)
{
}

CGoldBullion::CGoldBullion(const CGoldBullion& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CGoldBullion::~CGoldBullion()
{
}

void CGoldBullion::Start()
{
	CGameObject::Start();

}

bool CGoldBullion::Init()
{
	CGameObject::Init();
	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Collider2DHorizon = CreateSceneComponent<CColliderBox2D>("Collider2DHorizon");
	m_Collider2DVertical = CreateSceneComponent<CColliderBox2D>("Collider2DVertical");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Collider2DHorizon);
	m_Sprite->AddChild(m_Collider2DVertical);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(20.f, 9.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("GoldBullion");

	m_Collider2DHorizon->SetCollisionProfile("Object");
	m_Collider2DVertical->SetCollisionProfile("Object");

	m_Collider2DHorizon->AddCollisionCallbackFunction<CGoldBullion>(Collision_State::Begin, this,
		&CGoldBullion::CollisionHorizonBegin);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CGoldBullion>(Collision_State::Middle, this,
		&CGoldBullion::CollisionHorizonMiddle);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CGoldBullion>(Collision_State::End, this,
		&CGoldBullion::CollisionHorizonEnd);

	m_Collider2DVertical->AddCollisionCallbackFunction<CGoldBullion>(Collision_State::Begin, this,
		&CGoldBullion::CollisionVerticalBegin);
	m_Collider2DVertical->AddCollisionCallbackFunction<CGoldBullion>(Collision_State::Middle, this,
		&CGoldBullion::CollisionVerticalMiddle);
	m_Collider2DVertical->AddCollisionCallbackFunction<CGoldBullion>(Collision_State::End, this,
		&CGoldBullion::CollisionVerticalEnd);
	m_Collider2DVertical->SetExtent(1.f, 4.5f);
	m_Collider2DHorizon->SetExtent(10.f, 1.f);
	m_Body->SetGravity(true);
	m_Body->SetGravityPower(100.f);

	CStage* Stage = CStageManager::GetInst()->GetCurStage();
	Stage->PushObject(this);

	return true;
}

void CGoldBullion::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddRelativePos(m_Body->GetMove());
	m_WallCol = false;
}

void CGoldBullion::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CGoldBullion::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CGoldBullion::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CGoldBullion* CGoldBullion::Clone()
{
	return new CGoldBullion(*this);
}


void CGoldBullion::Drop(float Angle, float Power)
{
	m_Body->SetForce2D(Angle, Power);
}


void CGoldBullion::CollisionHorizonBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass
		|| result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
		
	}

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		//플레이어의 골드를 증가시켜주고 사운드 재생
		CPlayer* Player = CGlobalValue::MainPlayer;
		Player->AddCoin(100);
		CTextObject* TextObj = m_pScene->SpawnObject<CTextObject>("TextObject");
		TextObj->SetText(std::to_string(100)+"G");
		TextObj->SetWorldPos(GetWorldPos());
		TextObj->Gold();
		m_pScene->GetResource()->FindSound("GetGold")->Play();
		Active(false);
	}

}

void CGoldBullion::CollisionHorizonMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass
		|| result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirHorizon(Angle, result.DestCollider);
		
	}

}

void CGoldBullion::CollisionHorizonEnd(const HitResult& result, CCollider* Collider)
{

}

void CGoldBullion::CollisionVerticalBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass
		|| result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector3 PlayerPos3 = GetWorldPos() - GetVelocity();
		Vector2 PlayerPos = Vector2(PlayerPos3.x, PlayerPos3.y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		//플레이어의 골드를 증가시켜주고 사운드 재생
		CPlayer* Player = CGlobalValue::MainPlayer;
		Player->AddCoin(100);
		CTextObject* TextObj = m_pScene->SpawnObject<CTextObject>("TextObject");
		TextObj->SetText(std::to_string(100) + "G");
		TextObj->SetWorldPos(GetWorldPos());
		TextObj->Gold();
		m_pScene->GetResource()->FindSound("GetGold")->Play();
		Active(false);
	}
}

void CGoldBullion::CollisionVerticalMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector3 PlayerPos3 = GetWorldPos() - GetVelocity();
		Vector2 PlayerPos = Vector2(PlayerPos3.x, PlayerPos3.y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);


		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
}

void CGoldBullion::CollisionVerticalEnd(const HitResult& result, CCollider* Collider)
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


void CGoldBullion::ColDirHorizon(float Angle, CCollider* Col)
{
	Vector3 Velocity = GetVelocity();
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = m_Collider2DHorizon->GetWorldPos();
	Vector3 PlayerScale = m_Collider2DHorizon->GetRelativeScale() / 2.f;

	Vector3 ColCheckPos = PlayerPos - ColPos;

	//방향바꾸기
	Velocity.Normalize();
	Velocity.x = -Velocity.x;
	Velocity.y = -Velocity.y;

	//ColCheckPos의 y값이 음수라면 ColPos가 위쪽에있다는뜻인데..
	// 
	//왼쪽


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

void CGoldBullion::ColDirVertical(float Angle, CCollider* Col)
{
	Vector3 Velocity = GetVelocity();
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
	else if (0.f <= Angle && Angle < 180.f)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y -= y;
		PlayerPos.y = XMove.y;
	}

	SetWorldPos(PlayerPos);
}



#include "BelialDeadMouth.h"
#include <Component/Collider.h>
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
CBelialDeadMouth::CBelialDeadMouth() :
	m_Rotation(false),
	m_RotationTimer(0.f)
{
}

CBelialDeadMouth::CBelialDeadMouth(const CBelialDeadMouth& obj) :
	CGameObject(obj)
{
	m_RotationTimer = obj.m_RotationTimer;
}

CBelialDeadMouth::~CBelialDeadMouth()
{
}

void CBelialDeadMouth::Start()
{
	CGameObject::Start();
}

bool CBelialDeadMouth::Init()
{
	CGameObject::Init();
	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Back2);
	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->AddTexture("BelialDeadMouth", TEXT("boss/Belial/Dead/mouth.png"));
	m_Sprite->SetRelativeScale(49.f, 31.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Collider2D->SetExtent(10.f, 10.f);
	m_Collider2D->SetCollisionProfile("Object");
	m_Sprite->AddChild(m_Collider2D);


	m_Collider2D->Enable(true);

	m_Collider2D->AddCollisionCallbackFunction<CBelialDeadMouth>(Collision_State::Begin, this,
		&CBelialDeadMouth::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CBelialDeadMouth>(Collision_State::Middle, this,
		&CBelialDeadMouth::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CBelialDeadMouth>(Collision_State::End, this,
		&CBelialDeadMouth::CollisionEnd);

	m_Body->SetGravity(true);
	CStage* Stage = CStageManager::GetInst()->GetCurStage();
	Stage->PushObject(this);
	return true;
}

void CBelialDeadMouth::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddRelativePos(m_Body->GetMove());

}

void CBelialDeadMouth::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelialDeadMouth::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialDeadMouth::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialDeadMouth* CBelialDeadMouth::Clone()
{
	return new CBelialDeadMouth(*this);
}

void CBelialDeadMouth::Animation2DNotify(const std::string& Name)
{

}

void CBelialDeadMouth::AnimationFrameEnd(const std::string& Name)
{
}
void CBelialDeadMouth::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = EnemyPos.GetAngle(ColPos);
		ColDirMiddle(Angle, result.DestCollider);
	}
}
void CBelialDeadMouth::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = EnemyPos.GetAngle(ColPos);
		ColDirMiddle(Angle, result.DestCollider);
	}
}

void CBelialDeadMouth::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider == nullptr || result.DestCollider == nullptr)
		return;
}

void CBelialDeadMouth::ColDirStart(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = m_Collider2D->GetWorldPos();
	Vector3 PlayerScale = m_Collider2D->GetRelativeScale() / 2.f;

	Vector3 ColCheckPos = PlayerPos - ColPos;

	m_Body->StopForceY();
	m_Body->StopForceX();
	m_Body->SetGravity(false);
	float y = (PlayerScale.y + ColScale.y);
	Vector3 XMove = ColPos;
	XMove.y += y;
	PlayerPos.y = XMove.y;
	SetWorldPos(PlayerPos);
	m_Body->SetGravity(false);
	m_Body->SetJump(false);
}

void CBelialDeadMouth::ColDirMiddle(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = m_Collider2D->GetWorldPos();
	Vector3 PlayerScale = m_Collider2D->GetRelativeScale() / 2.f;

	Vector3 ColCheckPos = PlayerPos - ColPos;

	//ColCheckPos의 y값이 음수라면 ColPos가 위쪽에있다는뜻인데..
	// 
	//왼쪽


	m_Body->StopForceY();
	m_Body->StopForceX();
	m_Body->SetGravity(false);
	float y = (PlayerScale.y + ColScale.y);
	Vector3 XMove = ColPos;
	XMove.y += y;
	PlayerPos.y = XMove.y;
	SetWorldPos(PlayerPos);
	m_Body->SetGravity(false);
	m_Body->SetJump(false);
}

void CBelialDeadMouth::ColDirEnd(CCollider* Col)
{
}

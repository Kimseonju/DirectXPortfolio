#include "BelialDeadHead.h"
#include <Component/Collider.h>
CBelialDeadHead::CBelialDeadHead() :
	m_Rotation(false),
	m_RotationTimer(0.f)
{
}

CBelialDeadHead::CBelialDeadHead(const CBelialDeadHead& obj) :
	CGameObject(obj)
{
}

CBelialDeadHead::~CBelialDeadHead()
{
}

void CBelialDeadHead::Start()
{
	CGameObject::Start();
}

bool CBelialDeadHead::Init()
{
	CGameObject::Init();
	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->AddTexture("BelialDeadHead", TEXT("boss/Belial/Dead/head.png"));
	m_Sprite->SetRelativeScale(70.f, 77.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Collider2D->SetExtent(10.f, 10.f);
	m_Collider2D->SetCollisionProfile("Object");
	m_Sprite->AddChild(m_Collider2D);


	m_Collider2D->Enable(true);

	m_Collider2D->AddCollisionCallbackFunction<CBelialDeadHead>(Collision_State::Begin, this,
		&CBelialDeadHead::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CBelialDeadHead>(Collision_State::Middle, this,
		&CBelialDeadHead::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CBelialDeadHead>(Collision_State::End, this,
		&CBelialDeadHead::CollisionEnd);

	m_Body->SetGravity(true);
	return true;
}

void CBelialDeadHead::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddRelativePos(m_Body->GetMove());

}

void CBelialDeadHead::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelialDeadHead::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialDeadHead::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialDeadHead* CBelialDeadHead::Clone()
{
	return new CBelialDeadHead(*this);
}

void CBelialDeadHead::Animation2DNotify(const std::string& Name)
{

}

void CBelialDeadHead::AnimationFrameEnd(const std::string& Name)
{
}
void CBelialDeadHead::CollisionBegin(const HitResult& result, CCollider* Collider)
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
void CBelialDeadHead::CollisionMiddle(const HitResult& result, CCollider* Collider)
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

void CBelialDeadHead::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider == nullptr || result.DestCollider == nullptr)
		return;
}

void CBelialDeadHead::ColDirStart(float Angle, CCollider* Col)
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

void CBelialDeadHead::ColDirMiddle(float Angle, CCollider* Col)
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

void CBelialDeadHead::ColDirEnd(CCollider* Col)
{
}

#include "BossTresure.h"
#include <Input.h>
#include "KeyboardUIObject.h"
CBossTresure::CBossTresure() :
	m_Open(false)
{
}

CBossTresure::CBossTresure(const CBossTresure& obj)
{
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CBossTresure::~CBossTresure()
{
}

void CBossTresure::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Sprite->Enable(bEnable);
	m_Collider2D->Enable(bEnable);
}

void CBossTresure::Start()
{
	CGameObject::Start();

}

bool CBossTresure::Init()
{
	CGameObject::Init();
	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(43.f, 30.f, 0.f);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->AddTexture("BossTresureClosed", TEXT("NPC/BossTresureClosed.png"));

	m_Collider2D->SetCollisionProfile("Object");

	m_Collider2D->AddCollisionCallbackFunction<CBossTresure>(Collision_State::Begin, this,
		&CBossTresure::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CBossTresure>(Collision_State::Middle, this,
		&CBossTresure::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CBossTresure>(Collision_State::End, this,
		&CBossTresure::CollisionEnd);

	m_Collider2D->SetExtent(20.f, 15.f);
	m_Sprite->AddChild(m_Collider2D);



	m_KeyUIObject = m_pScene->SpawnObject<CKeyboardUIObject>("KeyUIObject");
	m_KeyUIObject->SetKey("F");
	m_KeyUIObject->SetWorldPos(GetWorldPos());
	m_KeyUIObject->AddWorldPos(-0.f, 30.f, 0.f);
	m_KeyUIObject->Enable(false);

	return true;
}

void CBossTresure::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddRelativePos(m_Body->GetMove());
}

void CBossTresure::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossTresure::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBossTresure::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBossTresure* CBossTresure::Clone()
{
	return new CBossTresure(*this);
}


void CBossTresure::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = EnemyPos.GetAngle(ColPos);
		ColDirStart(Angle, result.DestCollider);
	}

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		if (!m_Open)
		{
			m_KeyUIObject->Enable(true);
		}
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::InteractionInputKey)
	{
		if (!m_Open)
		{
			m_Open = true;
			m_KeyUIObject->Enable(false);
			CMaterial* Material = m_Sprite->GetMaterial(0);
			Material->AddTexture("BossTresureOpened", TEXT("NPC/BossTresureOpened.png"));
			Material->SetTexture("BossTresureOpened", TEXT("NPC/BossTresureOpened.png"));
			//골드드랍



		}
	}

}
void CBossTresure::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = EnemyPos.GetAngle(ColPos);
		ColDirStart(Angle, result.DestCollider);
	}


}

void CBossTresure::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider == nullptr || result.DestCollider == nullptr)
		return;

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		if (!m_Open)
		{
			m_KeyUIObject->Enable(false);
		}
	}
}


void CBossTresure::ColDirStart(float Angle, CCollider* Col)
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

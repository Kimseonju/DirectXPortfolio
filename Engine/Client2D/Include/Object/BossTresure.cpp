#include "BossTresure.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "../UI/UIManager.h"
#include "../UI/MiniMap.h"
#include <Scene/SceneResource.h>
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
#include "Firefly.h"
#include "Player.h"
#include "Gold.h"
#include "GoldBullion.h"
CBossTresure::CBossTresure() :
	m_Open(false),
	m_KeyUIObject(nullptr),
	m_GoldCount(0),
	m_GoldCountMax(100)
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
	m_Body->SetGravity(true);
	return true;
}

void CBossTresure::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddRelativePos(m_Body->GetMove());
	if (m_Open)
	{
		if (m_GoldCount < m_GoldCountMax)
		{
			m_GoldDropTimer += DeltaTime;
			if (m_GoldDropTimer >= m_GoldDropTimerMax)
			{
				m_GoldDropTimer -= m_GoldDropTimerMax;
				m_GoldCount++;
				int Select = GetRandom(0, 1);

				if (Select == 0)
				{
					CGold* Gold = m_pScene->SpawnObject<CGold>("Gold");
					Gold->SetWorldPos(GetWorldPos());
					Gold->Drop((float)GetRandom(0, 180), 50.f);
				}
				else
				{
					CGoldBullion* GoldBullion = m_pScene->SpawnObject<CGoldBullion>("GoldBullion");
					GoldBullion->SetWorldPos(GetWorldPos());
					GoldBullion->Drop((float)GetRandom(0, 180), 50.f);
				}
			}
		}
	}
}

void CBossTresure::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBossTresure::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBossTresure::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 4.f), Vector4(0.f / 255.f, 0.f / 255.f, 255.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);

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
			CCamera* Camera=m_pScene->GetCameraManager()->GetCurrentCamera();

			Camera->AddCameraShake(2.f, 2.f, 0.4f);
			m_pScene->GetResource()->FindSound("BossTresureBox")->Play();
			Vector3 Pos = GetWorldPos();
			CUIManager::GetInst()->GetFadeInOut_WhiteUI()->SetFadeIn();
			for (int i = 0; i < 20; ++i)
			{
				CFirefly* Firefly=m_pScene->SpawnObject<CFirefly>("Firefly" + std::to_string(i));
				Firefly->SetWorldPos(Pos);
				Firefly->SetOldPos(Vector2(Pos.x, Pos.y));
				
				Vector2 NextPos = Vector2(Pos.x, Pos.y);
				NextPos.x+=(float)GetRandom(-100, 100);
				NextPos.y+=(float)GetRandom(-50, 100);
				Firefly->SetNextPos(NextPos);
			}
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

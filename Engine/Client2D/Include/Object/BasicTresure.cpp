#include "BasicTresure.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Gold.h"
#include "GoldBullion.h"
#include "HPFairy.h"
#include "Player.h"
#include "../Object/ShortSword.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Item.h"
#include "../GlobalValue.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Revolver.h"
#include "../Object/Player.h"
#include "../Stage/StageManager.h"
#include "../Stage/Stage.h"
#include "../UI/UIManager.h"
#include "../UI/MiniMap.h"
#include <Scene/SceneResource.h>
CBasicTresure::CBasicTresure():
	m_Open(false),
	m_KeyUIObject(nullptr)
{
}

CBasicTresure::CBasicTresure(const CBasicTresure& obj)
{
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CBasicTresure::~CBasicTresure()
{
}

void CBasicTresure::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Sprite->Enable(bEnable);
	m_Collider2D->Enable(bEnable);
}

void CBasicTresure::Start()
{
	CGameObject::Start();

}

bool CBasicTresure::Init()
{
	CGameObject::Init();
	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");


	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_Body);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(43.f, 30.f, 1.f);
	CMaterial* Material=m_Sprite->GetMaterial(0);
	Material->AddTexture("BossTresureClosed", TEXT("NPC/BossTresureClosed.png"));

	m_Collider2D->SetCollisionProfile("Object");

	m_Collider2D->AddCollisionCallbackFunction<CBasicTresure>(Collision_State::Begin, this,
		&CBasicTresure::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CBasicTresure>(Collision_State::Middle, this,
		&CBasicTresure::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CBasicTresure>(Collision_State::End, this,
		&CBasicTresure::CollisionEnd);

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

void CBasicTresure::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	AddRelativePos(m_Body->GetMove());

	//CPlayer* Player = CGlobalValue::MainPlayer;
	//if (Player)
	//{
	//	SetWorldPos(Player->GetWorldPos());
	//}
}

void CBasicTresure::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBasicTresure::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBasicTresure::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f, 4.f), Vector4(0.f / 255.f, 0.f / 255.f, 255.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);

}

void CBasicTresure::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBasicTresure* CBasicTresure::Clone()
{
	return new CBasicTresure(*this);
}


void CBasicTresure::CollisionBegin(const HitResult& result, CCollider* Collider)
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
			CStage* CurStage=CStageManager::GetInst()->GetCurStage();
			CMaterial* Material = m_Sprite->GetMaterial(0);
			Material->AddTexture("BossTresureOpened", TEXT("NPC/BossTresureOpened.png"));
			Material->SetTexture("BossTresureOpened", TEXT("NPC/BossTresureOpened.png"));

			//CHPFairy* HPFairy = m_pScene->SpawnObject<CHPFairy>("HPFairy");
			//HPFairy->SetWorldPos(GetWorldPos());
			//HPFairy->AddWorldPos(0.f, 100.f, 0.f);
			//CurStage->PushObject(HPFairy);
			//골드드랍
			for (int i = 0; i < 5; ++i)
			{
				CGold* Gold = m_pScene->SpawnObject<CGold>("Gold");
				Gold->SetWorldPos(GetWorldPos());
				Gold->Drop((float)GetRandom(0, 180), 50.f);
			}
			for (int i = 0; i < 5; ++i)
			{
				CGoldBullion* GoldBullion = m_pScene->SpawnObject<CGoldBullion>("GoldBullion");
				GoldBullion->SetWorldPos(GetWorldPos());
				GoldBullion->Drop((float)GetRandom(0, 180), 50.f);
			}


			CItem* Item = nullptr;
			int SelectWeapon = GetRandom(0, Weapons::End - 1);

			std::string str = std::to_string(333);
			switch (SelectWeapon)
			{
			case ShortSword:
				Item = m_pScene->SpawnObject<CShortSword>("ShortSwordShop" + str);
				break;
			case MetalBoomerang:
				Item = m_pScene->SpawnObject<CMetalBoomerang>("MetalBoomerangShop" + str);
				break;
			case Revolver:
				Item = m_pScene->SpawnObject<CRevolver>("RevolverShop" + str);
				break;
			}
			Item->SetWorldPos(GetWorldPos());
			Item->Drop();
			Item->Enable(true);
			Item->Drop((float)GetRandom(0, 180), 50.f);
			CurStage->PushObject(Item);
			m_pScene->GetResource()->FindSound("TresureBoxOpen")->Play();
		}
	}

}
void CBasicTresure::CollisionMiddle(const HitResult& result, CCollider* Collider)
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
}

void CBasicTresure::CollisionEnd(const HitResult& result, CCollider* Collider)
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


void CBasicTresure::ColDirStart(float Angle, CCollider* Col)
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

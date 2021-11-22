#include "Giant_Red.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SmallSkelBow.h"
#include "Giant_RedBulletMain.h"
#include "ProgressBarObject.h"
#include "ObjectDieEffectObject.h"
#include "TextObject.h"
#include "Gold.h"
#include "GoldBullion.h"
CGiant_Red::CGiant_Red() :
	m_PlayerFind(false),
	m_AttackTimer(0.f),
	m_AttackTimerMax(5.f),
	m_Bullet(nullptr),
	m_Giant_RedAttack(false)
{
	SetStatus("Giant_Red");
}

CGiant_Red::CGiant_Red(const CGiant_Red& obj) :
	CEnemy(obj)
{
}

CGiant_Red::~CGiant_Red()
{
}

void CGiant_Red::Active(bool bActive)
{
	CEnemy::Active(bActive);
	if (m_Bullet)
	{
		m_Bullet->Active(bActive);
	}
}

void CGiant_Red::Start()
{
	CEnemy::Start();
	m_Body->SetGravity(false);
}

bool CGiant_Red::Init()
{
	CEnemy::Init();

	m_Collider2D->SetExtent(20.f, 15.f);
	m_AttackRangeCollider2D->SetExtent(7.f, 9.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	m_Sprite->SetWorldScale(59.f, 36.f, 0.f);
	m_Animation2D->SetIdleAnimation2D("Giant_RedIdle");
	m_Animation2D->SetMoveAnimation2D("Giant_RedIdle");
	m_Animation2D->SetAttackAnimation2D("Giant_RedAttack");
	m_Animation2D->ChangeIdleAnimation2D();


	return true;
}

void CGiant_Red::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);
	if (m_StartTimer > 0.f)
		return;
	if(!m_Giant_RedAttack)
		m_AttackTimer += DeltaTime;

}

void CGiant_Red::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
}

void CGiant_Red::Collision(float DeltaTime)
{
	CEnemy::Collision(DeltaTime);
}

void CGiant_Red::Render(float DeltaTime)
{
	CEnemy::Render(DeltaTime);
}

CGiant_Red* CGiant_Red::Clone()
{
	return new CGiant_Red(*this);
}

void CGiant_Red::Animation2DNotify(const std::string& Name)
{
	if (Name == "Attack")
	{
		if (m_Bullet)
		{
			CPlayer* player = CGlobalValue::MainPlayer;	
			Vector2 PlayerPos = Vector2(player->GetWorldPos().x, player->GetWorldPos().y);
			Vector2 EnemyPos = Vector2(GetWorldPos().x, GetWorldPos().y);

			float Angle = EnemyPos.GetAngle(PlayerPos);
			//플레이어위치구해서 회전
			m_Bullet->SetWorldRotationZ(Angle-90.f);
			m_Bullet->MoveStart();
			m_Bullet = nullptr;
		}
		m_Giant_RedAttack = false;
	}
}

void CGiant_Red::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status->SetHP(m_Status->GetHP() - CGlobalValue::MainPlayer->GetStatus().GetAttackDamage());
		m_EnemyInfoWidget->Enable(true);
		CTextObject* TextObj = m_pScene->SpawnObject<CTextObject>("TextObject");
		TextObj->SetText(std::to_string(CGlobalValue::MainPlayer->GetStatus().GetAttackDamage()));
		TextObj->SetWorldPos(GetWorldPos());
		TextObj->Damage();
		if (m_Status->GetHP() <= 0)
		{
			CObjectDieEffectObject* Effect = m_pScene->SpawnObject<CObjectDieEffectObject>("DieEffect");
			Effect->SetWorldPos(GetWorldPos());
			Active(false);
			DropGold();

		}

	}
}

void CGiant_Red::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
	}
}

void CGiant_Red::AnimationFrameEnd(const std::string& Name)
{
}

void CGiant_Red::DropGold()
{
	int DropCount = GetRandom(0, 4);
	for (int i = 0; i < DropCount; ++i)
	{
		CGold* Gold = m_pScene->SpawnObject<CGold>("Gold");
		Gold->SetWorldPos(GetWorldPos());
		Gold->AddWorldPos(0.f, 20.f, 0.f);
		Gold->Drop((float)GetRandom(0, 180), 300.f);
	}
	DropCount = GetRandom(0, 3);
	for (int i = 0; i < DropCount; ++i)
	{
		CGoldBullion* Gold = m_pScene->SpawnObject<CGoldBullion>("GoldBullion");
		Gold->SetWorldPos(GetWorldPos());
		Gold->AddWorldPos(0.f, 20.f, 0.f);
		Gold->Drop((float)GetRandom(0, 180), 300.f);
	}
}

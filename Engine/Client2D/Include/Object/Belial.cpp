#include "Belial.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Player.h"
#include "BelialHand.h"
#include "BelialWeapon.h"
#include "BelialWeaponCharge.h"
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
#include "../UI/UIManager.h"
#include "../UI/BossSpawnUI.h"
#include <Input.h>
#include "BelialBullet.h"
#include "BossDieEffectStart.h"
#include <time.h>
#include <Engine.h>
#include "../UI/UIManager.h"
#include "BelialDeadHead.h"
#include "BelialDeadMouth.h"
#include "../ObjectStatusManager.h"
#include "BelialBackParticle.h"
#include <Scene/SceneResource.h>
CBelial::CBelial() :
	m_AttackTimer(0.f),
	m_AttackTimerMax(3.f),
	m_Attacking(false),
	m_Pattern(Belial_Pattern::End),
	m_LeftHand(nullptr),
	m_RightHand(nullptr),
	m_PatternTimer(0.f),\
	m_SwordSpawnTimerMax(0.2f),
	m_SwordSpawnTimer(0.f),
	m_SwordSpawn(false),
	m_Spawn(false),
	m_Alpha(0.f),
	m_HandAlpha(0.f),
	m_AlphaUpdate(false),
	m_BulletAngle(0.f),
	m_BulletFireCount(0.f),
	m_PatternStop(false),
	m_EffectEnd(false),
	m_EffectEndTimer(0.f),
	m_EffectEndStart(false),
	m_SpawnEnd(false),
	m_LaserCountMax(2),
	m_HitTimer(0.f),
	m_BulletFireCountMax(0.2f),
	m_BackParticleObject(nullptr)
	
{
	SetStatus("Belial");
}


CBelial::~CBelial()
{
	SAFE_DELETE(m_Status);
}

void CBelial::Start()
{
	CGameObject::Start();

	m_LeftHand = m_pScene->SpawnObject<CBelialHand>("BelialLeftHand");
	Vector3 Pos = GetWorldPos();
	Pos.x -= 100.f;
	m_LeftHand->SetRelativePos(Pos);
	m_RightHand = m_pScene->SpawnObject<CBelialHand>("BelialRightHand");
	m_RightHand->SetHorizontalReverse2DEnable(true);
	Pos = GetWorldPos();
	Pos.x += 100.f;
	m_RightHand->SetRelativePos(Pos);
	m_BasicWorldPos = GetWorldPos();

}

bool CBelial::Init()
{
	CGameObject::Init();
	m_SpawnColliderBox2D = CreateSceneComponent<CColliderBox2D>("SpawnColliderBox2D");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_BackSprite = CreateSceneComponent<CSpriteComponent>("BackSprite");

	SetRootComponent(m_Sprite);

	m_Sprite->AddChild(m_SpawnColliderBox2D);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_BackSprite);

	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Sprite->SetRelativeScale(70.f, 96.f, 1.f);
	m_Sprite->SetPivot(0.6f, 0.3f, 0.f);

	m_Collider2D->SetPivot(0.6f, 0.3f, 0.f);

	m_Animation2D = (CAnimation2D*)m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("BelialHead_Idle");
	m_Animation2D->AddAnimationSequence2D("BelialHead_Attack", false);
	m_Animation2D->SetFrameEndFunction<CBelial>(this, &CBelial::AnimationFrameEnd);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha);
	Material->SetOpacity(1.f);

	m_BackSprite->SetRelativeScale(50.f, 50.f, 1.f);
	m_BackSprite->SetPivot(0.5f, 0.5f, 0.f);
	m_BackSprite->CreateAnimation2D < CAnimation2D_FSM>();
	m_BackSprite->SetRender2DType(Render_Type_2D::RT2D_Back2);
	m_BackAnimation2D = (CAnimation2D_FSM*)m_BackSprite->GetAnimation2D();
	m_BackAnimation2D->AddAnimationSequence2D("Belial_Circle");
	Material = m_BackSprite->GetMaterial(0);
	Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha);
	Material->SetOpacity(1.f);


	m_Collider2D->SetExtent(30.f, 30.f);
	m_Collider2D->Enable(false);
	m_Collider2D->SetCollisionProfile("Enemy");
	m_Collider2D->AddCollisionCallbackFunction<CBelial>(Collision_State::Begin, this,
		&CBelial::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CBelial>(Collision_State::Middle, this,
		&CBelial::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CBelial>(Collision_State::End, this,
		&CBelial::CollisionEnd);


	m_SpawnColliderBox2D->SetExtent(2.f, 1000);
	m_SpawnColliderBox2D->SetCollisionProfile("BossSpawn");
	m_SpawnColliderBox2D->AddCollisionCallbackFunction<CBelial>(Collision_State::Begin, this, &CBelial::CollisionBossSpawnBegin);
	//m_Collider2D->SetExtent(30.f, 30.f);
	Enable(true);

	return true;
}

void CBelial::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (!m_Spawn)
		return;
	else 
	{
		//서서히나타나기
		AlphaUpdate(DeltaTime);
	}
	if (m_PatternStop)
	{
		m_Animation2D->StopPlay();
		if(m_LeftHand)
			m_LeftHand->StopAnimation();
		if(m_RightHand)
			m_RightHand->StopAnimation();
		if (m_EffectEnd)
			EffectEndUpdate(DeltaTime);
	}
	else
	{
		if(m_SpawnEnd)
			PatternUpdate(DeltaTime);
	}
	m_HitTimer -= DeltaTime;

	CMaterial* Material = m_Sprite->GetMaterial(0);
	if (m_HitTimer > 0.f)
	{
		Material->SetBaseColor(1.f, 0.f, 0.f, m_Alpha);
	}
	else
	{
		m_HitTimer = 0.f;
		Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha);
	}
}

void CBelial::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelial::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelial::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelial* CBelial::Clone()
{
	return new CBelial(*this);
}

void CBelial::Animation2DNotify(const std::string& Name)
{
}

void CBelial::SetStatus(const std::string& Name)
{
	CBasicStatus* Status = CObjectStatusManager::GetInst()->FindStatus(Name);
	if (Status)
	{
		SAFE_DELETE(m_Status);
		m_Status = Status->Clone();;
	}
}

void CBelial::AttackSword(float DeltaTime)
{
	Vector3 Pos = GetWorldPos();
	Pos.y += 50.f;
	Pos.x -= 50.f;
	if (m_BelialWeapon.size() < 5 && m_SwordSpawn==false)
	{	
		m_SwordSpawnTimer += DeltaTime;
		if (m_SwordSpawnTimer > m_SwordSpawnTimerMax)
		{
			m_SwordSpawnTimer -= m_SwordSpawnTimerMax;
			std::string str;
			str = std::to_string(m_BelialWeapon.size());

			CBelialWeapon* Weapon = m_pScene->SpawnObject<CBelialWeapon>("BelialSword" + str);
			Weapon->SetAttackTimerMax(1.f + m_BelialWeapon.size() * 0.2f);
			Vector3 WeaponPos = Pos;
			WeaponPos.x += 30.f * (float)m_BelialWeapon.size() - 3;
			Weapon->SetWorldPos(WeaponPos);

			CBelialWeaponCharge* Charge = m_pScene->SpawnObject<CBelialWeaponCharge>("BelialCharge" + str);
			Weapon->SetCharge(Charge);
			m_BelialWeapon.push_back(Weapon);
		}
	}
	else
	{
		m_SwordSpawn = true;
		m_BelialWeapon.clear();
		m_Attacking = false;
	}

}

void CBelial::AttackBullet(float DeltaTime)
{
	m_Animation2D->ChangeAnimation("BelialHead_Attack");
	m_Sprite->SetWorldScale(70.f, 128.f, 0.f);
	m_PatternTimer += DeltaTime;
	if (m_PatternTimer > 5.f)
	{
		m_PatternTimer = 0.f;
		m_Attacking = false;
		m_Animation2D->ChangeAnimation("BelialHead_Idle");
		m_Sprite->SetRelativeScale(70.f, 96.f, 1.f);
		m_BulletAngle = 0.f;
		return;
	}
	else if (m_Animation2D->GetFrameEnd())
	{
		m_BulletFireCount += DeltaTime;
		if (m_BulletFireCount > m_BulletFireCountMax)
		{
			m_BulletFireCount -= m_BulletFireCountMax;
			for (int i = 0; i < 4; ++i)
			{
				CBelialBullet* Bullet = m_pScene->SpawnObject<CBelialBullet>("BelialBullet");
				Bullet->SetWorldRotationZ(m_BulletAngle + i * 90.f);
				Bullet->SetWorldPos(GetWorldPos());
			}
			m_pScene->GetResource()->FindSound("BelialBullet")->Play();
		}

		m_BulletAngle += DeltaTime*90.f;

	}

}

void CBelial::AttackLaser(float DeltaTime)
{
	if (!m_LeftHand->Attack())
	{
		m_RightHand->Attack();
	}
	m_PatternTimer = 0.f;
	m_Attacking = false;
	m_LaserCount++;
	m_AttackTimer = 2.f;
	if (m_LaserCount > m_LaserCountMax)
	{
		m_LaserCount = 0;
		m_PatternTimer = 0.f;
		m_AttackTimer = 0.f;
	}
}

void CBelial::EffectEndUpdate(float DeltaTime)
{
	m_EffectEndTimer += DeltaTime;
	//오브젝트 삭제 후
	if (!m_EffectEndStart)
	{
		//부셔진 해골 오브젝트 생성 후 본인 오브젝트 싹다 Enable를 false로 만들어놓기
		m_EffectEndStart = true;
		m_Sprite->Enable(false);
		m_BackSprite->Enable(false);
		m_Collider2D->SetExtent(0.f, 0.f);
		m_Collider2D->Enable(false);
		m_LeftHand->Active(false);
		m_LeftHand = nullptr;
		m_RightHand->Active(false);
		m_RightHand = nullptr;
		m_BackParticleObject->Active(false);
		CBelialDeadHead* Head=m_pScene->SpawnObject<CBelialDeadHead>("BelialDeadHead");
		Head->SetWorldPos(GetWorldPos());

		CBelialDeadMouth* Mouth = m_pScene->SpawnObject<CBelialDeadMouth>("BelialDeadMouth");
		Head->SetWorldPos(GetWorldPos());
		Head->AddWorldPos(0.f, -30.f, 0.f);
		
	}
	if (m_EffectEndTimer > 3.f)
	{
		//돈을 뿌리면서 카메라흔들림, 카메라무브 원래대로
		CUIManager::GetInst()->GetBossUI()->Enable(false);
		CCamera* Camera=m_pScene->GetCameraManager()->GetCurrentCamera();
		Camera->CameraCurrentMoveStop();
		Camera->CameraCurrentShakeStop();
		Active(false);
	}
}

void CBelial::AlphaUpdate(float DeltaTime)
{
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();
	if (m_AlphaUpdate)
	{
		m_Alpha += DeltaTime;
		if (m_Alpha > 1.f)
		{
			m_HandAlpha += DeltaTime;
			if (m_HandAlpha > 1.f)
			{

				Camera->AddCameraMove2D(Vector2(GetWorldPos().x, GetWorldPos().y), 5.f);
				CUIManager::GetInst()->GetBossSpawnUI()->Spawn();
				m_AlphaUpdate = false;
				m_SpawnEnd = true;
			}
		}
		CMaterial* Material = m_Sprite->GetMaterial(0);
		Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha);

		Material = m_BackSprite->GetMaterial(0);
		Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha); 

		m_LeftHand->SetOpaacity(m_Alpha);
		m_RightHand->SetOpaacity(m_Alpha);

		Material = m_LeftHand->GetMaterial();
		Material->SetBaseColor(1.f, 1.f, 1.f, m_HandAlpha);

		Material = m_RightHand->GetMaterial();
		Material->SetBaseColor(1.f, 1.f, 1.f, m_HandAlpha);
		m_Collider2D->Enable(true);
	}
}

void CBelial::PatternUpdate(float DeltaTime)
{
#pragma region BossMoving
	if (m_Animation2D->GetName() == "BelialHead_Idle")
	{
		int Frame = m_Animation2D->GetFrame();
		int FrameSize = m_Animation2D->GetFrameSize() / 2;
		Vector3 Pos = m_BasicWorldPos;
		if (Frame < FrameSize)
		{
			Pos.y += Frame * 4.f;
			SetWorldPos(Pos);
		}
		else
		{
			Pos.y += (FrameSize - Frame) * 4.f;
			SetWorldPos(Pos);
		}
	}
#pragma endregion

	if (m_Attacking)
	{
#pragma region PatternPlay_Stay
		switch (m_Pattern)
		{
		case Belial_Pattern::Sword:
			AttackSword(DeltaTime);
			break;
		case Belial_Pattern::Laser:
			AttackLaser(DeltaTime);
			break;
		case Belial_Pattern::Bullet:
			AttackBullet(DeltaTime);
			break;
		case Belial_Pattern::End:
			break;
		default:
			break;
		}
#pragma endregion
	}
	else
		m_AttackTimer += DeltaTime;

	if (m_AttackTimer >= m_AttackTimerMax)
	{
		m_AttackTimer -= m_AttackTimerMax;
		m_Attacking = true;
		if (m_LaserCount != 0)
			m_Pattern = Belial_Pattern::Laser;
		else
		{
			m_Pattern = (Belial_Pattern)GetRandom(0, (int)Belial_Pattern::End - 1);
			if (m_Pattern == Belial_Pattern::Laser)
				m_LaserCountMax = GetRandom(1, 2);
		}
		m_AttackTimer = 0.f;
		m_SwordSpawn = false;
	}
}


void CBelial::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
}

void CBelial::CollisionBossSpawnBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_pScene->GetResource()->FindSound("belial_laugh")->Play();
		m_pScene->GetResource()->FindSound("Boss")->Play();
		m_SpawnColliderBox2D->Enable(false);
		m_Collider2D->Enable(true);
		m_Spawn = true;
		m_AlphaUpdate = true;
		CInput::GetInst()->SetUpdate(false);
		CUIManager::GetInst()->GetBossSpawnUI()->Enable(true);
		m_BackParticleObject =m_pScene->SpawnObject<CBelialBackParticle>("BelialBackParticle");
		m_BackParticleObject->SetWorldPos(GetWorldPos());
	}

}

void CBelial::AnimationFrameEnd(const std::string& Name)
{
}

void CBelial::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status->SetHP(m_Status->GetHP() - CGlobalValue::MainPlayer->GetStatus()->GetAttackDamage());
		CUIManager::GetInst()->GetBossUI()->SetProgressBarPercent((float)m_Status->GetHP() / (float)m_Status->GetHPMax());
		
		if (m_Status->GetHP() < 0.f)
		{
			m_PatternStop = true;
			CBossDieEffectStart* Obj=m_pScene->SpawnObject<CBossDieEffectStart>("BossDieEffectStart");
			Obj->SetWorldPos(GetWorldPos());
			Obj->SetBelial(this);
			CEngine::GetInst()->SetTimeScale(0.5f);
			CUIManager::GetInst()->GetBossDieUI()->Enable(true);
			m_pScene->GetResource()->FindSound("Boss")->Stop();
		
		}
		else
		{
			m_HitTimer += 0.2f;
			m_pScene->GetResource()->FindSound("Hit_Enemy")->Play();
			if (m_Status->GetHP() < 30.f)
			{
				m_AttackTimerMax = 2.5f;
				m_SwordSpawnTimerMax = 0.15f;
				m_BulletFireCountMax = 0.1f;
			}
		}


	}
}

void CBelial::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CBelial::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

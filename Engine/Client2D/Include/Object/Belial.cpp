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
CBelial::CBelial() :
	m_AttackTimer(0.f),
	m_AttackTimerMax(5.f),
	m_Attacking(false),
	m_Pattern(Belial_Pattern::End),
	m_LeftHand(nullptr),
	m_RightHand(nullptr),
	m_PatternTimer(0.f),
	m_SwordSpawnTimerMax(0.2f),
	m_SwordSpawnTimer(0.f),
	m_SwordSpawn(false),
	m_Spawn(false),
	m_Alpha(0.f),
	m_HandAlpha(0.f),
	m_AlphaUpdate(false),
	m_BulletAngle(0.f),
	m_BulletFireCount(0.f)
	
{
	m_StartGravity = true;
	m_Status.SetHP(150);
	m_Status.SetHPMax(150);
}

CBelial::CBelial(const CBelial& obj) :
	CEnemy(obj)
{
	m_AttackTimer = obj.m_AttackTimer;
	m_AttackTimerMax = obj.m_AttackTimerMax;
	m_Attacking = obj.m_Attacking;
	m_Pattern = obj.m_Pattern;
	m_LeftHand = nullptr;
	m_RightHand = nullptr;
}

CBelial::~CBelial()
{
}

void CBelial::Start()
{
	CEnemy::Start();

	m_LeftHand = m_pScene->SpawnObject<CBelialHand>("BelialLeftHand");
	Vector3 Pos = GetWorldPos();
	Pos.x -= 100.f;
	m_LeftHand->SetRelativePos(Pos);
	m_RightHand = m_pScene->SpawnObject<CBelialHand>("BelialRightHand");
	m_RightHand->SetHorizontalReverse2DEnable(true);
	Pos = GetWorldPos();
	Pos.x += 100.f;
	m_RightHand->SetRelativePos(Pos);

}

bool CBelial::Init()
{
	CEnemy::Init();
	m_SpawnColliderBox2D = CreateSceneComponent<CColliderBox2D>("SpawnColliderBox2D");
	m_RootComponent->AddChild(m_SpawnColliderBox2D);

	m_SpawnColliderBox2D->SetExtent(2.f, 1000);
	m_SpawnColliderBox2D->SetCollisionProfile("BossSpawn");
	m_SpawnColliderBox2D->AddCollisionCallbackFunction<CBelial>(Collision_State::Begin, this, &CBelial::CollisionBossSpawnBegin);
	m_Sprite->SetRelativeScale(70.f, 96.f, 1.f);
	m_BasicWorldPos = GetWorldPos();
	m_Animation2D->SetIdleAnimation2D("BelialHead_Idle");
	m_Animation2D->SetAttackAnimation2D("BelialHead_Attack", false);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha);
	Material->SetOpacity(1.f);
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
				}
			}
			CMaterial* Material = m_Sprite->GetMaterial(0);
			Material->SetBaseColor(1.f, 1.f, 1.f, m_Alpha);
			m_LeftHand->SetOpaacity(m_Alpha);
			m_RightHand->SetOpaacity(m_Alpha);

			Material =m_LeftHand->GetMaterial();
			Material->SetBaseColor(1.f, 1.f, 1.f, m_HandAlpha);

			Material = m_RightHand->GetMaterial();
			Material->SetBaseColor(1.f, 1.f, 1.f, m_HandAlpha);
		}
	}
	if (m_Animation2D->GetName() == "BelialHead_Idle")
	{
		int Frame=m_Animation2D->GetFrame();
		int FrameSize=m_Animation2D->GetFrameSize()/2;
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

	if (m_Attacking)
	{
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
	}
	else
	{
		m_AttackTimer += DeltaTime;
	}
	if (m_AttackTimer >= m_AttackTimerMax)
	{
		m_AttackTimer -= m_AttackTimerMax;
		m_Attacking=true;
		m_Pattern = (Belial_Pattern)GetRandom(0, (int)Belial_Pattern::End - 1);
		//m_Pattern = Belial_Pattern::Sword;
		m_AttackTimer = 0.f;
		m_SwordSpawn = false;
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

void CBelial::AttackSword(float DeltaTime)
{
	Vector3 Pos = GetWorldPos();
	Pos.y += 50.f;
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
	m_Animation2D->ChangeAttackAnimation2D();
	m_Sprite->SetWorldScale(70.f, 128.f, 0.f);
	m_PatternTimer += DeltaTime;
	if (m_PatternTimer > 5.f)
	{
		m_PatternTimer = 0.f;
		m_Attacking = false;
		m_Animation2D->ChangeIdleAnimation2D();
		m_BulletAngle = 0.f;
		return;
	}
	if (m_Animation2D->GetFrameEnd())
	{
		m_BulletFireCount += DeltaTime;
		if (m_BulletFireCount > 0.3f)
		{
			m_BulletFireCount -= 0.3f;
			for (int i = 0; i < 4; ++i)
			{
				CBelialBullet* Bullet = m_pScene->SpawnObject<CBelialBullet>("BelialBullet");
				Bullet->SetWorldRotationZ(m_BulletAngle + i * 90.f);
				Bullet->SetWorldPos(GetWorldPos());
			}
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
	m_Attacking = false;
	m_PatternTimer = 0.f;
}

void CBelial::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
}

void CBelial::CollisionBossSpawnBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		m_SpawnColliderBox2D->Enable(false);
		m_Collider2D->Enable(true);
		m_Spawn = true;
		m_AlphaUpdate = true;
		CInput::GetInst()->StopInput();
	}

}

void CBelial::AnimationFrameEnd(const std::string& Name)
{
}

void CBelial::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status.SetHP(m_Status.GetHP() - CGlobalValue::MainPlayer->GetStatus().GetAttackDamage());
		if (m_Status.GetHP() < 0.f)
		{

		}
	}
}

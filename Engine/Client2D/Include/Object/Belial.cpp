#include "Belial.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/BelialAnimation2D.h"
#include "Player.h"
#include "BelialHand.h"
#include "BelialWeapon.h"
#include "BelialWeaponCharge.h"
CBelial::CBelial() :
	m_AttackTimer(0.f),
	m_AttackTimerMax(10.f),
	m_Attacking(false),
	m_Pattern(Belial_Pattern::End),
	m_LeftHand(nullptr),
	m_RightHand(nullptr),
	m_PatternTimer(0.f),
	m_PatternTimerMax(2.f),
	m_SwordSpawnTimerMax(0.2f),
	m_SwordSpawnTimer(0.f),
	m_SwordSpawn(false)
	
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
	Pos.x -= 200.f;
	m_LeftHand->SetRelativePos(Pos);

	m_RightHand = m_pScene->SpawnObject<CBelialHand>("BelialRightHand");
	m_RightHand->SetHorizontalReverse2DEnable(true);
	Pos = GetWorldPos();
	Pos.x += 200.f;
	m_RightHand->SetRelativePos(Pos);

}

bool CBelial::Init()
{
	CEnemy::Init();
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	m_Sprite->CreateAnimation2D<CBelialAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Sprite->SetRelativeScale(280.f, 512.f, 1.f);
	return true;
}

void CBelial::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Attacking)
	{
		switch (m_Pattern)
		{
		case Belial_Pattern::Sword:
			AttackSword(DeltaTime);
			break;
		case Belial_Pattern::Laser:
			break;
		case Belial_Pattern::Bullet:
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
		m_Pattern = Belial_Pattern::Sword;
		m_PatternTimerMax = 5.f;
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
	Pos.y += 150.f;
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
			WeaponPos.x += 100.f * (float)m_BelialWeapon.size() - 2;
			Weapon->SetWorldPos(WeaponPos);

			CBelialWeaponCharge* Charge = m_pScene->SpawnObject<CBelialWeaponCharge>("BelialCharge" + str);
			Weapon->SetCharge(Charge);
			m_BelialWeapon.push_back(Weapon);
		}
	}
	else
	{
		m_SwordSpawn = true;
	}

}

void CBelial::AttackBullet(float DeltaTime)
{
}

void CBelial::AttackLaser(float DeltaTime)
{
}

void CBelial::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
}

void CBelial::AnimationFrameEnd(const std::string& Name)
{
}

void CBelial::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status.SetHP(m_Status.GetHP() - CGlobalValue::MainPlayer->GetStatus().GetAttackDamage());
	}
}

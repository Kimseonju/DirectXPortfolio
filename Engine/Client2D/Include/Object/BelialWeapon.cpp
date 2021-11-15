#include "BelialWeapon.h"
#include "Resource/Material.h"
#include "BelialWeaponCharge.h"
#include "Player.h"
#include "../GlobalValue.h"
CBelialWeapon::CBelialWeapon() :
	m_Belial(nullptr),
	m_TextureUpdate(false),
	m_Charge(nullptr),
	m_Attacking(false),
	m_AttackTimer(0.f),
	m_AttackTimerMax(1.f),
	m_StartAttack(false),
	m_AcitveTime(0.f)
{
}

CBelialWeapon::CBelialWeapon(const CBelialWeapon& obj) :
	CEnemy(obj)
{
	m_Attacking = obj.m_Attacking;
	m_TextureUpdate = obj.m_TextureUpdate;
	m_Belial = nullptr;
	m_Charge = nullptr;
}

CBelialWeapon::~CBelialWeapon()
{
}

void CBelialWeapon::Start()
{
	CEnemy::Start();
}

bool CBelialWeapon::Init()
{
	CEnemy::Init();
	m_Sprite->DeleteAnimation2D();
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->AddTexture("BelialWeapon", TEXT("boss/Belial/Sword/default.png"));
	m_Sprite->SetRelativeScale(65.f, 21.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	m_Collider2D->Enable(false);
	return true;
}

void CBelialWeapon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (!m_StartAttack)
	{
		m_AttackTimer += DeltaTime;
		CPlayer* Player = CGlobalValue::MainPlayer;
		Vector2 Pos;
		Pos.x = Player->GetWorldPos().x;
		Pos.y = Player->GetWorldPos().y;
		Vector2 Pos2 = Vector2(GetWorldPos().x, GetWorldPos().y);
		float angle = Pos2.GetAngle(Pos);
		SetRelativeRotationZ(angle);
	}
	if (m_Charge)
	{
		m_Charge->SetRelativePos(GetRelativePos());
		m_Charge->SetRelativeRotation(GetRelativeRotation());
	}
	if (m_AttackTimer > m_AttackTimerMax)
	{
		SetTarget();
		m_StartAttack = true;
		m_Attacking = true;
		m_TextureUpdate = true;
		m_AttackTimer = 0.f;
	}
	if (m_Attacking)
	{
		AddRelativePos(m_TargetMove * 100.f * DeltaTime);
	}

	if (!m_Attacking && m_StartAttack)
	{
		m_AcitveTime += DeltaTime;
		if (m_AcitveTime > 2.f)
			Active(false);
	}
}

void CBelialWeapon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	if (m_TextureUpdate)
	{
		if (m_Attacking)
		{
			CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
			SpriteMtrl->AddTexture("BelialWeaponShoot", TEXT("boss/Belial/Sword/shoot.png"));
			SpriteMtrl->SetTexture("BelialWeaponShoot", TEXT("boss/Belial/Sword/shoot.png"));
			if (m_Charge)
			{
				//공격시작 Charge끝
				m_Charge->Active(false);
				m_Charge = nullptr;
			}
		}
		m_TextureUpdate = false;
	}
	
}

void CBelialWeapon::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialWeapon::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialWeapon* CBelialWeapon::Clone()
{
	return new CBelialWeapon(*this);
}

void CBelialWeapon::Animation2DNotify(const std::string& Name)
{
}

void CBelialWeapon::SetTarget()
{
	CPlayer* Player = CGlobalValue::MainPlayer;
	Vector2 Pos;
	Pos.x = Player->GetWorldPos().x;
	Pos.y = Player->GetWorldPos().y;
	Vector2 Pos2 = Vector2(GetWorldPos().x, GetWorldPos().y);
	float angle = Pos2.GetAngle(Pos);
	Pos -= Pos2;
	Pos.Normalize();
	m_TargetMove = Vector3(Pos.x, Pos.y,0.f);
	SetRelativeRotationZ(angle);
	m_Collider2D->Enable(true);
}

void CBelialWeapon::SetBelial(CBelial* Belial)
{
	m_Belial = Belial;
}

void CBelialWeapon::SetCharge(CBelialWeaponCharge* Charge)
{
	m_Charge = Charge;
}


void CBelialWeapon::SetHorizontalReverse2DEnable(bool Enable)
{
	if (m_Sprite)
	{
		m_Sprite->SetHorizontalReverse2DEnable(Enable);
	}
}


void CBelialWeapon::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{

}

void CBelialWeapon::AnimationFrameEnd(const std::string& Name)
{
}

void CBelialWeapon::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		m_Attacking = false;
		m_Collider2D->Enable(false);
		CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
		SpriteMtrl->SetTexture("BelialWeapon", TEXT("boss/Belial/Sword/default.png"));
	}
}

void CBelialWeapon::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
}

void CBelialWeapon::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

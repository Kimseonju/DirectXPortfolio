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
	m_StartAttack(false)
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
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->AddTexture("BelialWeapon", TEXT("Boss/Belial/Sword/Default.png"));
	m_Sprite->SetRelativeScale(65.f, 21.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	return true;
}

void CBelialWeapon::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if(!m_StartAttack)
		m_AttackTimer += DeltaTime;
	if (m_Charge)
	{
		m_Charge->SetRelativePos(GetRelativePos());
		m_Charge->SetRelativeRotation(GetRelativeRotation());
	}
	if (m_AttackTimer > m_AttackTimerMax)
	{
		//m_StartAttack = true;
		//m_Attacking = true;
		//m_TextureUpdate = true;
		m_AttackTimer = 0.f;
	}
	CPlayer* Player=CGlobalValue::MainPlayer;
	Vector2 Pos;
	Pos.x = Player->GetWorldPos().x;
	Pos.y = Player->GetWorldPos().y;
	Vector2 Pos2 = Vector2(GetWorldPos().x, GetWorldPos().y);
	float angle = Pos2.GetAngle(Pos);
	SetRelativeRotationZ(angle);
}

void CBelialWeapon::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	if (m_TextureUpdate)
	{
		if (m_Attacking)
		{
			CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
			SpriteMtrl->SetTexture("BelialWeaponShoot", TEXT("boss/Belial/Sword/shoot.png"));
			if (m_Charge)
			{
				//공격시작 Charge끝
				m_Charge->Active(false);
				m_Charge = nullptr;
			}
		}
		else
		{
			CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
			SpriteMtrl->SetTexture("BelialWeapon", TEXT("boss/Belial/Sword/Default.png"));
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

void CBelialWeapon::SetBelial(CBelial* Belial)
{
	m_Belial = Belial;
}

void CBelialWeapon::SetCharge(CBelialWeaponCharge* Charge)
{
	m_Charge = Charge;
}

void CBelialWeapon::Attack()
{
	m_Attacking = true;
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
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
	}
}

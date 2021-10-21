#include "Belial.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/EnemyAnimation2D.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"

CBelial::CBelial()
{
}

CBelial::CBelial(const CBelial& obj) :
	CEnemy(obj)
{
}

CBelial::~CBelial()
{
}

void CBelial::Start()
{
	CEnemy::Start();
}

bool CBelial::Init()
{
	CEnemy::Init();
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	m_Sprite->CreateAnimation2D<CEnemyAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();

	m_AttackRangeCollider2D->SetExtent(55.f, 50.f);
	m_AttackRangeCollider2D->SetCollisionProfile("Enemy");
	m_AttackRangeCollider2D->AddCollisionCallbackFunction<CEnemy>(Collision_State::Begin, this,
		&CEnemy::CollisionAttackRangeBegin);
	m_Sprite->AddChild(m_AttackRangeCollider2D);



	m_Status.SetMoveSpeed(200.f);
	m_Body->SetMoveSpeed(m_Status.GetMoveSpeed());

	return true;
}

void CBelial::Update(float DeltaTime)
{
	CEnemy::Update(DeltaTime);

	if (m_Weapon->IsAttack())
	{
		return;
	}

	if (CGlobalValue::MainPlayer)
	{
		CPlayer* player = CGlobalValue::MainPlayer;
		Vector3 Pos = player->GetWorldPos() - GetWorldPos();
		Pos.Normalize();
		float Angle = GetWorldPos().Angle(player->GetWorldPos());

		//위
		if (Angle > 330.f && Angle < 30.f)
		{

		}

		//아래

		else if (Angle > 150.f && Angle < 210.f)
		{

		}
		else
		{
			Pos.y = 0.f;
			Pos.z = 0.f;
			Pos.Normalize();
			m_Body->SetDir(Pos);

			if (Pos.x < 0.f)
			{
				m_Dir = Object_Dir::Left;
				m_Sprite->SetHorizontalReverse2DEnable(true);
			}
			else
			{
				m_Dir = Object_Dir::Right;
				m_Sprite->SetHorizontalReverse2DEnable(false);
			}
			m_WeaponArm->SetDir(m_Dir);

			if (m_Weapon)
			{
				m_Weapon->SetDir(m_Dir);
				if (m_Weapon->GetWeaponType() == Weapon_Type::Melee)
				{
					if (m_Dir == Object_Dir::Left)
					{
						m_WeaponArm->SetRelativeRotationZ(-180.f);
						m_Weapon->SetRelativeRotationZ(-180.f);
					}
					else if (m_Dir == Object_Dir::Right)
					{
						m_WeaponArm->SetRelativeRotationZ(0);
						m_Weapon->SetRelativeRotationZ(0);

					}
				}
				else if (m_Weapon->GetWeaponType() == Weapon_Type::Range)
				{
					m_Weapon->SetRelativeRotationZ(Angle + m_Weapon->GetRebound());
				}
			}

		}
	}
}

void CBelial::PostUpdate(float DeltaTime)
{
	CEnemy::PostUpdate(DeltaTime);
}

void CBelial::Collision(float DeltaTime)
{
	CEnemy::Collision(DeltaTime);
}

void CBelial::Render(float DeltaTime)
{
	CEnemy::Render(DeltaTime);
}

CBelial* CBelial::Clone()
{
	return new CBelial(*this);
}

void CBelial::Animation2DNotify(const std::string& Name)
{
}

void CBelial::Attack1()
{
}

void CBelial::Attack2()
{
}

void CBelial::Attack3()
{
}

void CBelial::Attack4()
{
}

void CBelial::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
	{
		Vector3 DestPos = result.DestObject->GetWorldPos();
		Vector3 Pos = GetWorldPos();
		Pos = Pos - DestPos;
		float Dir;
		if (m_Dir == Object_Dir::Left)
		{
			Dir = 270.f;
		}
		else
		{
			Dir = 90.f;
		}
		//왼쪽 오른쪽
		m_Weapon->Attack(Dir);
	}
}

void CBelial::AnimationFrameEnd(const std::string& Name)
{
}

void CBelial::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	CEnemy::CollisionBegin(result, Collider);
}

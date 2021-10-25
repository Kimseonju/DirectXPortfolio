#include "BelialHand.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "../Animation2D/BelialHandAnimation2D.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"

CBelialHand::CBelialHand() :
	m_Belial(nullptr),
	m_Attacking(false)
{
}

CBelialHand::CBelialHand(const CBelialHand& obj) :
	CEnemy(obj)
{
	m_Belial = nullptr;
	m_Attacking = false;
}

CBelialHand::~CBelialHand()
{
}

void CBelialHand::Start()
{
	CEnemy::Start();
}

bool CBelialHand::Init()
{
	CEnemy::Init();
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	m_Sprite->CreateAnimation2D<CBelialHandAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Sprite->SetRelativeScale(228.f, 268.f, 1.f);

	return true;
}

void CBelialHand::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CBelialHand::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBelialHand::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialHand::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialHand* CBelialHand::Clone()
{
	return new CBelialHand(*this);
}

void CBelialHand::Animation2DNotify(const std::string& Name)
{
}

void CBelialHand::SetBelial(CBelial* Belial)
{
	m_Belial = Belial;
}

void CBelialHand::Attack()
{
}

void CBelialHand::SetHorizontalReverse2DEnable(bool Enable)
{
	if (m_Sprite)
	{
		m_Sprite->SetHorizontalReverse2DEnable(Enable);
	}
}


void CBelialHand::CollisionAttackRangeBegin(const HitResult& result, CCollider* Collider)
{
	
}

void CBelialHand::AnimationFrameEnd(const std::string& Name)
{
}

void CBelialHand::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::PlayerAttack)
	{
		m_Status.SetHP(m_Status.GetHP() - CGlobalValue::MainPlayer->GetStatus().GetAttackDamage());
		m_EnemyInfoWidget->Enable(true);
	}
}

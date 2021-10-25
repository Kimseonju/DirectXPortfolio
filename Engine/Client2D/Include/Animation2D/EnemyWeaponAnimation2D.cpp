#include "EnemyWeaponAnimation2D.h"
#include "Component/SpriteComponent.h"

CEnemyWeaponAnimation2D::CEnemyWeaponAnimation2D() :
	m_Die(false),
	m_Idle(nullptr),
	m_Attack(nullptr)
{
}

CEnemyWeaponAnimation2D::CEnemyWeaponAnimation2D(const CEnemyWeaponAnimation2D& anim) :
	CAnimation2D(anim)
{
	m_Die = false;
	m_Idle = nullptr;
	m_Attack = nullptr;
}

CEnemyWeaponAnimation2D::~CEnemyWeaponAnimation2D()
{
}

void CEnemyWeaponAnimation2D::Start()
{
	CAnimation2D::Start();
	AddAnimationSequence2D("SmallEnemyDaggerAttack", false);
	m_Attack = FindSequence("SmallEnemyDaggerAttack");
	AddAnimationSequence2D("SmallEnemyDaggerIdle");
	m_Idle = FindSequence("SmallEnemyDaggerIdle");
	ChangeAnimation(m_Idle);
}

bool CEnemyWeaponAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	return true;
}

void CEnemyWeaponAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);

}

CEnemyWeaponAnimation2D* CEnemyWeaponAnimation2D::Clone()
{
	return new CEnemyWeaponAnimation2D(*this);
}

#include "EnemyAnimation2D.h"
#include "Component/SpriteComponent.h"

CEnemyAnimation2D::CEnemyAnimation2D() :
	m_Die(false)
{
}

CEnemyAnimation2D::CEnemyAnimation2D(const CEnemyAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CEnemyAnimation2D::~CEnemyAnimation2D()
{
}

void CEnemyAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CEnemyAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("SmallEnemyIdle");
	AddAnimationSequence2D("SmallEnemyMove");
	m_SequenceIdle = FindSequence("SmallEnemyIdle");
	m_SequenceMove= FindSequence("SmallEnemyMove");
	return true;
}

void CEnemyAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
	if (m_Die)
	{
		if(m_SequenceDie)
			ChangeAnimation(m_SequenceDie);
	}
	else
	{
		if (m_Owner->GetVelocity().Length() > 0.f)
		{
			if (m_Owner->GetVelocity().y == 0.f)
			{
				if(m_SequenceMove)
					ChangeAnimation(m_SequenceMove);

			}
			//공중상태
			else
			{
				if (m_SequenceJump)
					ChangeAnimation(m_SequenceJump);
			}
		}

		else
		{
			if (m_SequenceIdle)
				ChangeAnimation(m_SequenceIdle);
		}
	}
}

CEnemyAnimation2D* CEnemyAnimation2D::Clone()
{
	return new CEnemyAnimation2D(*this);
}

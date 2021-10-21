#include "EnemyShotAnimation2D.h"
#include "Component/SpriteComponent.h"

CEnemyShotAnimation2D::CEnemyShotAnimation2D() :
	m_Die(false)
{
}

CEnemyShotAnimation2D::CEnemyShotAnimation2D(const CEnemyShotAnimation2D& anim) :
	CAnimation2D(anim)
{
}

CEnemyShotAnimation2D::~CEnemyShotAnimation2D()
{
}

void CEnemyShotAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CEnemyShotAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	return true;
}

void CEnemyShotAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
	if (m_Die)
	{
		if (m_SequenceDie)
			ChangeAnimation(m_SequenceDie);
	}
	else
	{
		if (m_Owner->GetVelocity().Length() > 0.f)
		{
			if (m_Owner->GetVelocity().y == 0.f)
			{
				if (m_SequenceMove)
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
			if (m_SequenceAttack)
			{
				if (m_CurrentSequence != m_SequenceAttack)
				{
					if (m_SequenceIdle)
						ChangeAnimation(m_SequenceIdle);
				}
			}
		}
	}
}

CEnemyShotAnimation2D* CEnemyShotAnimation2D::Clone()
{
	return new CEnemyShotAnimation2D(*this);
}

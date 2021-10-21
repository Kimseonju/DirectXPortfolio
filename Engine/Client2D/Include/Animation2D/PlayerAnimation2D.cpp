
#include "PlayerAnimation2D.h"
#include "Component/SpriteComponent.h"

CPlayerAnimation2D::CPlayerAnimation2D():
	m_Die(false)
{
}

CPlayerAnimation2D::CPlayerAnimation2D(const CPlayerAnimation2D& anim)	:
	CAnimation2D(anim)
{
}

CPlayerAnimation2D::~CPlayerAnimation2D()
{
}

void CPlayerAnimation2D::Start()
{
	CAnimation2D::Start();
}

bool CPlayerAnimation2D::Init()
{
	if (!CAnimation2D::Init())
		return false;

	AddAnimationSequence2D("PlayerIdle");
	AddAnimationSequence2D("PlayerRun");
	AddAnimationSequence2D("PlayerJump");
	AddAnimationSequence2D("PlayerAttack", false);

	return true;
}

void CPlayerAnimation2D::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
	if (m_Die)
	{
		ChangeAnimation("PlayerDie");
	}
	else
	{
  		if (m_Owner->GetVelocity().Length() > 0.f)
		{
			if (m_Owner->GetVelocity().y == 0.f)
				ChangeAnimation("PlayerRun");
			//공중상태
			else
			{
				ChangeAnimation("PlayerJump");
			}
		}

		else
		{
			if (GetCurrentSequenceName() != "PlayerAttack")
				ChangeAnimation("PlayerIdle");
		}
	}
}

CPlayerAnimation2D* CPlayerAnimation2D::Clone()
{
	return new CPlayerAnimation2D(*this);
}


#include "MoveComponent.h"
#include <GameObject.h>

CMoveComponent::CMoveComponent() :
	m_Gravity(false),
	m_GravityPower(600),
	m_JumpPower(200),
	m_Speed(100.f)
{
}

CMoveComponent::CMoveComponent(const CMoveComponent& com)
{
}

CMoveComponent::~CMoveComponent()
{
}

void CMoveComponent::Start()
{
}

bool CMoveComponent::Init()
{

	return true;
}

void CMoveComponent::Update(float DeltaTime)
{
	//가속도 
	Vector3 moveDir = Vector3::Zero;
	if (m_Gravity)
	{
		//공중상태

		//대쉬안할때
		if (m_DashTimer <= 0.f)
		{
			if (m_Dash)
			{
				m_Dash = false;
				m_Force.x = 0.f;
				m_Dir = Vector3::Zero;
			}
			if (m_Force.y > 200.f)
				m_Force.y = 200.f;
			m_Force.y -= m_GravityPower * DeltaTime;
			if (m_Force.y < -300.f)
				m_Force.y = -300.f;
			moveDir += m_Force * DeltaTime;
			moveDir += m_Dir * m_Speed * DeltaTime;
		}
		//대쉬중일때
		else
		{
			Dashing(DeltaTime);
			m_DashTimer -= DeltaTime;
			if (m_DashEffectTime <= 0.f)
			{
				m_DashEffectTime += 0.015f;
				m_DashEffect = true;
			}
			m_DashEffectTime -= DeltaTime;
			moveDir += m_Force * DeltaTime;
		}
	}
	else
	{
		//좌우로 움직이는중
		//애니메이션은 플레이어에서 조절
		if (m_Dir != Vector3::Zero)
		{
			moveDir += m_Dir * m_Speed * DeltaTime;
			moveDir += m_Force * DeltaTime;
			m_Dir = Vector3::Zero;
		}
	}
	m_PrevMoveDir = moveDir;
	m_MoveDir = moveDir;
	if(m_Owner)
		m_Owner->AddRelativePos(m_MoveDir);
}

void CMoveComponent::PostUpdate(float DeltaTime)
{
}

void CMoveComponent::Collision(float DeltaTime)
{
}

void CMoveComponent::PrevRender(float DeltaTime)
{
}

void CMoveComponent::Render(float DeltaTime)
{
}

CMoveComponent* CMoveComponent::Clone()
{
	return new CMoveComponent(*this);
}

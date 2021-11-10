
#include "RigidBodyComponent.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"

CRigidBodyComponent::CRigidBodyComponent() :
	m_Gravity(false),
	m_GravityPower(600),
	m_JumpPower(200),
	m_Speed(100.f)
{
}

CRigidBodyComponent::CRigidBodyComponent(const CRigidBodyComponent& com) :
    CSceneComponent(com)
{
}

CRigidBodyComponent::~CRigidBodyComponent()
{
}

void CRigidBodyComponent::Start()
{
    CSceneComponent::Start();
}

bool CRigidBodyComponent::Init()
{
    if (!CSceneComponent::Init())
        return false;

    return true;
}

void CRigidBodyComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);

	//가속도 
	//아이작 가속도 다 가속도...
	Vector3 moveDir= Vector3::Zero;
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
}

void CRigidBodyComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CRigidBodyComponent::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CRigidBodyComponent::PrevRender(float DeltaTime)
{
    CSceneComponent::PrevRender(DeltaTime);
	m_pParent->AddRelativePos(m_MoveDir);
}

void CRigidBodyComponent::Render(float DeltaTime)
{
    CSceneComponent::Render(DeltaTime);
}

CRigidBodyComponent* CRigidBodyComponent::Clone()
{
    return new CRigidBodyComponent(*this);
}

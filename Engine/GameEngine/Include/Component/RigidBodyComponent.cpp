
#include "RigidBodyComponent.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"

CRigidBodyComponent::CRigidBodyComponent() :
	m_Gravity(false),
	m_GravityPower(2000),
	m_JumpPower(800),
	m_Speed(400.f)
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

	//���ӵ� 
	//������ ���ӵ� �� ���ӵ�...
	Vector3 moveDir= Vector3::Zero;
	if (m_Gravity)
	{
		//���߻���
		
		//�뽬���Ҷ�
		if (m_DashTimer <= 0.f)
		{
			if (m_Dash)
			{
				m_Dash = false;
				m_Force.x = 0.f;
				m_Dir = Vector3::Zero;
			}
			if (m_Force.y > 600.f)
				m_Force.y = 600.f;
			m_Force.y -= m_GravityPower * DeltaTime;
			if (m_Force.y < -2000.f)
				m_Force.y = -2000.f;
			moveDir += m_Force * DeltaTime;
			moveDir += m_Dir * m_Speed * DeltaTime;
		}
		//�뽬���϶�
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
		//�¿�� �����̴���
		//�ִϸ��̼��� �÷��̾�� ����
		if (m_Dir != Vector3::Zero)
		{
			moveDir += m_Dir * m_Speed * DeltaTime;
			m_Dir = Vector3::Zero;
		}
	}
	m_PrevMoveDir = moveDir;
	m_pParent->AddRelativePos(moveDir);
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
}

void CRigidBodyComponent::Render(float DeltaTime)
{
    CSceneComponent::Render(DeltaTime);
}

CRigidBodyComponent* CRigidBodyComponent::Clone()
{
    return new CRigidBodyComponent(*this);
}

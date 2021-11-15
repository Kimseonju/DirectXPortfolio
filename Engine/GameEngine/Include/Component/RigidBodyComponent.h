#pragma once

//Primitive 출력을 하기위한용도
#include "SceneComponent.h"
#include "../Resource/Material.h"

class CRigidBodyComponent :
    public CSceneComponent
{
    friend class CGameObject;

protected:
    CRigidBodyComponent();
    CRigidBodyComponent(const CRigidBodyComponent& com);
    virtual ~CRigidBodyComponent();

protected:
    bool        m_Gravity;
    bool        m_DashEffect;
    bool        m_Dash;

    float m_Speed;
    float m_ShotSpeed;
    float m_ShotRange;
    float m_Att;
    float m_GravityPower;
    float m_JumpPower;
    float m_DashTimer;
    float m_DashEffectTime;
    Vector3 m_DamageSpeed;
    Vector3 m_Dir;       // 힘가해지는 방향
    Vector3 m_Force;       // 가속도   
    Vector3 m_SaveAccel;       // 물체에게 충돌받은 힘 저장
    float   m_ObjectMaxSpeed; //오브젝트가 가할때 힘 최대치
    float   m_MaxSpeed;    // 최대속력 
    Vector3 m_PrevMoveDir;
    float   m_DashRadian;
    Vector3 m_MoveDir;
    bool m_Jump;
public:
    Vector3 GetMove()
    {
        return m_MoveDir;
    }
    bool IsJump()
    {
        return m_Jump;
    }
    void Dash(float Angle)
    {
        m_DashRadian = DegreeToRadian(Angle);
        m_Gravity = true;
        m_DashTimer = 0.1f;
        m_DashEffectTime = 0.015f;
        m_Force.x = 0.f;
        m_Force.y = 0.f;
        m_Dash = true;
        m_Jump = true;
    }
    void StopDash()
    {
        m_DashTimer = 0.f;
    }
    void Dashing(float DeltaTime)
    {
        m_Force.x += cosf(m_DashRadian) * 50.f * DeltaTime * m_Speed;
        m_Force.y += sinf(m_DashRadian) * 100.f * DeltaTime * m_Speed;
    }

    void SetForce2D(float Angle, float Power)
    {
        float Radian = DegreeToRadian(Angle);
        m_Force.x = cosf(m_DashRadian) * Power;
        m_Force.y = sinf(m_DashRadian) * Power;
    }
    bool IsDash() const
    {
        return m_Dash;
    }
    bool IsDashEffect() const
    {
        return m_DashEffect;
    }
    void SetDashEffect(bool Effect)
    {
        m_DashEffect = Effect;
    }
    void SetGravity(bool bGravity)
    {
        m_Gravity = bGravity;
    }
    void StopForceX()
    {
        m_Force.x = 0.f;
    }
    void StopForceY()
    {
        m_Force.y = 0.f;
    }
    void SetJump(bool Jump)
    {
        m_Jump = Jump;
    }

    void Jump()
    {
        m_Jump = true;
        m_Gravity = true;
        m_Force.y = m_JumpPower;
    }
    void SetDir(Vector3& Dir)
    {
        m_Dir = Dir;
    }
    void AddDir(Vector3& Dir)
    {
        m_Dir += Dir;
    }
    void SetForce(Vector3& Force)
    {
        m_Force = Force;
    }
    void SetMoveSpeed(float Speed)
    {
        m_Speed = Speed;
    }

    Vector3 GetForce()const
    {
        return m_Force;
    }

    void SetGravityPower(float Power)
    {
        m_GravityPower = Power;
    }
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void PrevRender(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CRigidBodyComponent* Clone();
};


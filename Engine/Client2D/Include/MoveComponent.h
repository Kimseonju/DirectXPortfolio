#pragma once

//Primitive ����� �ϱ����ѿ뵵
#include <GameEngine.h>

class CMoveComponent
{
    friend class CGameObject;

public:
    CMoveComponent();
    CMoveComponent(const CMoveComponent& com);
    virtual ~CMoveComponent();

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
    Vector3 m_Dir;       // ���������� ����
    Vector3 m_Force;       // ���ӵ�   
    Vector3 m_SaveAccel;       // ��ü���� �浹���� �� ����
    float   m_ObjectMaxSpeed; //������Ʈ�� ���Ҷ� �� �ִ�ġ
    float   m_MaxSpeed;    // �ִ�ӷ� 
    Vector3 m_PrevMoveDir;
    float   m_DashRadian;
    Vector3 m_MoveDir;
    class CGameObject* m_Owner;
public:
    void SetOwner(class CGameObject* Owner)
    {
        m_Owner = Owner;
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
    void SetJump(bool Jump)
    {
        if (Jump)
        {
            m_Gravity = true;
            m_Force.y = m_JumpPower;
        }
        else
        {
            //�ٴ����� ��������������

            if (m_Force.y < 0.f)
            {
                m_Gravity = false;
            }
            m_Force.y = 0.f;
            m_Force.x = 0.f;
            m_MoveDir = Vector3(0.f, 0.f, 0.f);

        }
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
    virtual CMoveComponent* Clone();
};


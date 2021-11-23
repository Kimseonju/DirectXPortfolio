#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"

class CMetalBoomerangBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CMetalBoomerangBullet();
    CMetalBoomerangBullet(const CMetalBoomerangBullet& obj);
    virtual ~CMetalBoomerangBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderCircle> m_Collider2DCircle;
    float       m_Distance;
    bool        m_Collision;
    bool        m_Comeback;
    float       m_Force;
    float       m_ComebackTimeMax;
    float       m_ComebackTime;
    class CWeapon* m_Weapon;
public:
    void SetDistance(float Distance)
    {
        m_Distance = Distance;
    }

    void SetComeback(bool Comeback)
    {
        m_Comeback = Comeback;
    }
    void SetForce(float Force)
    {
        m_Force = Force;
    }
    void SetComebackTimeMax(float Time)
    {
        m_ComebackTimeMax = Time;
    }
    void SetCollisionProfile(const std::string& Name)
    {
        m_Collider2DCircle->SetCollisionProfile(Name);
    }

    void SetWeapon(CWeapon* Weapon)
    {
        m_Weapon = Weapon;
    }
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CMetalBoomerangBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


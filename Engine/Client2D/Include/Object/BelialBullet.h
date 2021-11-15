#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderCircle.h"

class CBelialBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CBelialBullet();
    CBelialBullet(const CBelialBullet& obj);
    virtual ~CBelialBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderCircle> m_Collider2DCircle;
    float       m_Distance;
public:
    void SetDistance(float Distance)
    {
        m_Distance = Distance;
    }

    void SetCollisionProfile(const std::string& Name)
    {
        m_Collider2DCircle->SetCollisionProfile(Name);
    }

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBelialBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


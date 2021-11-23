#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CRevolverBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CRevolverBullet();
    CRevolverBullet(const CRevolverBullet& obj);
    virtual ~CRevolverBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CSpriteComponent> m_Sprite2;
    CSharedPtr<CColliderBox2D> m_ColliderBox2D;
    float       m_Distance;
public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CRevolverBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


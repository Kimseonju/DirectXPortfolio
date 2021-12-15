#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CCosmosSwordBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CCosmosSwordBullet();
    CCosmosSwordBullet(const CCosmosSwordBullet& obj);
    virtual ~CCosmosSwordBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
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
    virtual CCosmosSwordBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include <Component/ColliderBox2D.h>

class CBelialLaserHead :
    public CGameObject
{
    friend class CScene;

protected:
    CBelialLaserHead();
    CBelialLaserHead(const CBelialLaserHead& obj);
    virtual ~CBelialLaserHead();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CColliderBox2D> m_Collider2D;
    class CAnimation2D* m_Animation2D;
public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBelialLaserHead* Clone();

public:
    void LaserCollisionSetting();
    void SetHorizontalReverse2DEnable(bool Enable);
public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


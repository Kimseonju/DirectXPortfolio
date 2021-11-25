#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CBansheeBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CBansheeBullet();
    CBansheeBullet(const CBansheeBullet& obj);
    virtual ~CBansheeBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CSpriteComponent> m_Sprite2;
    CSharedPtr<CColliderBox2D> m_ColliderBox2D;
    class CAnimation2D* m_Animation2D;
    float       m_Distance;
    int         m_Damage;
public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBansheeBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


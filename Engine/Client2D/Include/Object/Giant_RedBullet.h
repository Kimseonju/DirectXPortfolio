#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CGiant_RedBullet :
    public CGameObject
{
    friend class CScene;

protected:
    CGiant_RedBullet();
    CGiant_RedBullet(const CGiant_RedBullet& obj);
    virtual ~CGiant_RedBullet();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CSpriteComponent> m_Sprite2;
    CSharedPtr<CColliderBox2D> m_ColliderBox2D;
    class CAnimation2D* m_Animation2D;

public:
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CGiant_RedBullet* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


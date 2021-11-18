#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CEnemyArrow :
    public CGameObject
{
    friend class CScene;

protected:
    CEnemyArrow();
    CEnemyArrow(const CEnemyArrow& obj);
    virtual ~CEnemyArrow();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    CSharedPtr<CSpriteComponent> m_Sprite2;
    CSharedPtr<CColliderBox2D> m_ColliderBox2D;
public:
   
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CEnemyArrow* Clone();

public:
    void CollisionBegin(const HitResult& result, CCollider* Collider);
    void CollisionEnd(const HitResult& result, CCollider* Collider);
};


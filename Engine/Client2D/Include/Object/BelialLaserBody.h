#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include <Component/ColliderBox2D.h>

class CBelialLaserBody :
    public CGameObject
{
    friend class CScene;

protected:
    CBelialLaserBody();
    CBelialLaserBody(const CBelialLaserBody& obj);
    virtual ~CBelialLaserBody();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;
    class CAnimation2D* m_Animation2D;
public:

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CBelialLaserBody* Clone();

public:
    void SetHorizontalReverse2DEnable(bool Enable);
};


#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"

class CGiant_RedBulletMain :
    public CGameObject
{
    friend class CScene;

protected:
    CGiant_RedBulletMain();
    CGiant_RedBulletMain(const CGiant_RedBulletMain& obj);
    virtual ~CGiant_RedBulletMain();

protected:
    CSharedPtr<CSpriteComponent> m_Sprite;

    std::vector<CSharedPtr<CGameObject>> m_Bullet;

    float       m_Distance;

    int m_SpawnCount;
    int m_SpawnCountMax;
    float m_SpawnTimer;
    float m_SpawnTimerMax;
    bool m_Move;
    bool m_AttackReady;
public:
    bool IsAttackReady()
    {
        return m_AttackReady;
    }
    void MoveStart()
    {
        m_Move = true;
    }
public:
    virtual void Active(bool bEnable);
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CGiant_RedBulletMain* Clone();

};


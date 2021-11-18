
#include "Giant_RedBulletMain.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
#include "Giant_RedBulletFX.h"
#include "Giant_RedBullet.h"
CGiant_RedBulletMain::CGiant_RedBulletMain() :
    m_Distance(300.f),
    m_SpawnCountMax(20),
    m_SpawnCount(0),
    m_SpawnTimerMax(0.005f),
    m_SpawnTimer(0.f),
    m_Move(false),
    m_AttackReady(false)

{
}

CGiant_RedBulletMain::CGiant_RedBulletMain(const CGiant_RedBulletMain& obj) :
    CGameObject(obj)
{
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CGiant_RedBulletMain::~CGiant_RedBulletMain()
{
}

void CGiant_RedBulletMain::Active(bool bEnable)
{
    CGameObject::Active(bEnable);
    if (!bEnable)
    {
        auto iter = m_Bullet.begin();
        auto iterEnd = m_Bullet.end();
        for (; iter != iterEnd; ++iter)
        {
            if ((*iter)->IsEnable())
            {
                CGameObject* FX = m_pScene->SpawnObject<CGiant_RedBulletFX>("Giant_RedBulletFX");
                FX->SetWorldPos((*iter)->GetWorldPos());
            }
            (*iter)->Active(false);
        }
        m_Bullet.clear();
    }
}

void CGiant_RedBulletMain::Start()
{
    CGameObject::Start();
}

bool CGiant_RedBulletMain::Init()
{
    CGameObject::Init();

    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

    SetRootComponent(m_Sprite);

    m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
   

    return true;
}

void CGiant_RedBulletMain::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    m_SpawnTimer += DeltaTime;
    if (m_SpawnCount <= m_SpawnCountMax)
    {
        if (m_SpawnTimer > m_SpawnTimerMax)
        {
            m_SpawnTimer -= m_SpawnTimerMax;

            float Angle = m_SpawnCount * 18.f;

            CGiant_RedBullet* Bullet = m_pScene->SpawnObject<CGiant_RedBullet>("Giant_RedBullet");
            Bullet->SetWorldPos(GetWorldPos());
            Bullet->SetWorldRotationZ(Angle);
            Bullet->AddWorldPos(Bullet->GetAxis(AXIS_Y) * 20.f);

            m_Bullet.push_back(Bullet);
            m_SpawnCount++;
        }
    }
    else
    {
        //공격준비완료
        m_AttackReady = true;
    }

    if (m_Move)
    {
        float   Dist = 100.f * DeltaTime;
        AddRelativePos(GetAxis(AXIS_Y) * Dist);
        m_Distance -= Dist;

        auto iter = m_Bullet.begin();
        auto iterEnd = m_Bullet.end();
        for (; iter != iterEnd; ++iter)
        {
            (*iter)->AddRelativePos(GetAxis(AXIS_Y) * Dist);
        }
    }
    if (m_Distance <= 0.f)
    {
        auto iter = m_Bullet.begin();
        auto iterEnd = m_Bullet.end();
        for (; iter != iterEnd; ++iter)
        {
            if ((*iter)->IsEnable())
            {
                CGameObject* FX = m_pScene->SpawnObject<CGiant_RedBulletFX>("Giant_RedBulletFX");
                FX->SetWorldPos((*iter)->GetWorldPos());
            }
            (*iter)->Active(false);
        }
        m_Bullet.clear();
        Active(false);
    }
}

void CGiant_RedBulletMain::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CGiant_RedBulletMain::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CGiant_RedBulletMain::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CGiant_RedBulletMain* CGiant_RedBulletMain::Clone()
{
    return new CGiant_RedBulletMain(*this);
}


#include "BansheeBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
#include "BansheeBulletFX.h"
#include "Player.h"
CBansheeBullet::CBansheeBullet():
    m_Distance(200.f),
    m_Damage(5),
    m_Animation2D(nullptr)
{
}

CBansheeBullet::CBansheeBullet(const CBansheeBullet& obj) :
    CGameObject(obj)
{
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBansheeBullet::~CBansheeBullet()
{
}

void CBansheeBullet::Start()
{
    CGameObject::Start();
}

bool CBansheeBullet::Init()
{
    CGameObject::Init();

    m_ColliderBox2D = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Sprite2 = CreateSceneComponent<CSpriteComponent>("Sprite2");

    SetRootComponent(m_Sprite);
    m_Sprite->AddChild(m_ColliderBox2D);
    m_Sprite->AddChild(m_Sprite2);

    m_Sprite->SetRelativeScale(0.f, 0.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

    m_Sprite2->SetRelativeScale(13.f, 16.f, 1.f);
    m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);

    m_Sprite2->CreateAnimation2D<CAnimation2D>();
    m_Animation2D = m_Sprite2->GetAnimation2D();
    m_Animation2D->AddAnimationSequence2D("BansheeBullet");

    m_ColliderBox2D->SetExtent(4.f, 4.f);
    m_ColliderBox2D->SetCollisionProfile("EnemyAttack");
    

    m_ColliderBox2D->AddCollisionCallbackFunction<CBansheeBullet>(Collision_State::Begin, this,
        &CBansheeBullet::CollisionBegin);

    return true;
}

void CBansheeBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    float   Dist = 100.f * DeltaTime;
    AddRelativePos(GetAxis(AXIS_Y) * Dist);
    m_Distance -= Dist;
    if (m_Distance <= 0.f)
    {
        CGameObject* FX = m_pScene->SpawnObject<CBansheeBulletFX>("BansheeBulletFX");
        FX->SetWorldPos(GetWorldPos());
        Active(false);
    }
}

void CBansheeBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBansheeBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CBansheeBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CBansheeBullet* CBansheeBullet::Clone()
{
    return new CBansheeBullet(*this);
}

void CBansheeBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
    {
        //플레이어타격!

        CGameObject* FX = m_pScene->SpawnObject<CBansheeBulletFX>("BansheeBulletFX");
        FX->SetWorldPos(GetWorldPos());
        Active(false);


        CGlobalValue::MainPlayer->EnemyHit(m_Damage);
    }

}

void CBansheeBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

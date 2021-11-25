
#include "Giant_RedBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
#include "Giant_RedBulletFX.h"
#include "Player.h"
CGiant_RedBullet::CGiant_RedBullet()

{
}

CGiant_RedBullet::CGiant_RedBullet(const CGiant_RedBullet& obj) :
    CGameObject(obj)
{
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CGiant_RedBullet::~CGiant_RedBullet()
{
}

void CGiant_RedBullet::Start()
{
    CGameObject::Start();
}

bool CGiant_RedBullet::Init()
{
    CGameObject::Init();

    m_ColliderBox2D = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Sprite2 = CreateSceneComponent<CSpriteComponent>("Sprite2");

    SetRootComponent(m_Sprite);
    m_Sprite->AddChild(m_Sprite2);

    m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
    m_Sprite->AddChild(m_ColliderBox2D);


    m_Sprite2->SetRelativeScale(14.f, 14.f, 1.f);
    m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);
    m_Sprite2->CreateAnimation2D<CAnimation2D>();
    m_Animation2D = m_Sprite2->GetAnimation2D();
    m_Animation2D->AddAnimationSequence2D("Giant_RedBullet");

    m_ColliderBox2D->SetExtent(5.f, 5.f);
    m_ColliderBox2D->SetCollisionProfile("EnemyAttack");

    m_ColliderBox2D->AddCollisionCallbackFunction<CGiant_RedBullet>(Collision_State::Begin, this,
        &CGiant_RedBullet::CollisionBegin);

    return true;
}

void CGiant_RedBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    
}

void CGiant_RedBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CGiant_RedBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CGiant_RedBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CGiant_RedBullet* CGiant_RedBullet::Clone()
{
    return new CGiant_RedBullet(*this);
}

void CGiant_RedBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
    {
        CGameObject* FX = m_pScene->SpawnObject<CGiant_RedBulletFX>("Giant_RedBulletFX");
        FX->SetWorldPos(GetWorldPos());
        Enable(false);
        m_ColliderBox2D->Enable(false);
        m_Sprite2->Enable(false);
    }
    else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
    {
        //플레이어타격!
        CGameObject* FX = m_pScene->SpawnObject<CGiant_RedBulletFX>("Giant_RedBulletFX");
        FX->SetWorldPos(GetWorldPos());
        Enable(false);
        m_ColliderBox2D->Enable(false);
        m_Sprite2->Enable(false);

        CGlobalValue::MainPlayer->EnemyHit(4);

    }

}

void CGiant_RedBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

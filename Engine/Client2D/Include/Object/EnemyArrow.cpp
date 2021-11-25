
#include "EnemyArrow.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
#include "Player.h"
CEnemyArrow::CEnemyArrow()
{
}

CEnemyArrow::CEnemyArrow(const CEnemyArrow& obj) :
    CGameObject(obj)
{
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CEnemyArrow::~CEnemyArrow()
{
}

void CEnemyArrow::Start()
{
    CGameObject::Start();
}

bool CEnemyArrow::Init()
{
    CGameObject::Init();

    m_ColliderBox2D = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Sprite2 = CreateSceneComponent<CSpriteComponent>("Sprite2");

    SetRootComponent(m_Sprite);

    m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
    m_Sprite->AddChild(m_ColliderBox2D);


    m_Sprite->AddChild(m_Sprite2);
    m_Sprite2->SetRelativeScale(13.f, 5.f, 1.f);
    m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);
    CMaterial* Material = m_Sprite2->GetMaterial(0);
    Material->AddTexture("Arrow", TEXT("Weapon/Range/Arrow.png"));

    m_ColliderBox2D->SetExtent(2.f, 6.f);
    m_ColliderBox2D->SetCollisionProfile("EnemyAttack");

    //m_Body->SetCollisionProfile("Monster");


    m_ColliderBox2D->AddCollisionCallbackFunction<CEnemyArrow>(Collision_State::Begin, this,
        &CEnemyArrow::CollisionBegin);

    return true;
}

void CEnemyArrow::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    AddRelativePos(GetAxis(AXIS_Y) * DeltaTime * 100.f);
    m_Sprite2->SetRelativeRotationZ(GetWorldRotation().z+90.f);

}

void CEnemyArrow::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CEnemyArrow::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CEnemyArrow::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CEnemyArrow* CEnemyArrow::Clone()
{
    return new CEnemyArrow(*this);
}

void CEnemyArrow::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
    {
        Active(false);
    }
    else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
    {
        //플레이어타격!
        CGlobalValue::MainPlayer->EnemyHit(4);

    }

}

void CEnemyArrow::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

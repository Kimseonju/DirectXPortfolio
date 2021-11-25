
#include "RevolverBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
CRevolverBullet::CRevolverBullet():
    m_Distance(500.f)
{
}

CRevolverBullet::CRevolverBullet(const CRevolverBullet& obj) :
    CGameObject(obj)
{
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CRevolverBullet::~CRevolverBullet()
{
}

void CRevolverBullet::Start()
{
    CGameObject::Start();
}

bool CRevolverBullet::Init()
{
    CGameObject::Init();

    m_ColliderBox2D = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Sprite2 = CreateSceneComponent<CSpriteComponent>("Sprite2");

    SetRootComponent(m_Sprite);
    m_Sprite->AddChild(m_ColliderBox2D);
    m_Sprite->AddChild(m_Sprite2);

    m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

    m_Sprite2->SetPivot(0.5f, 0.5f, 0.f);
    m_Sprite2->SetRelativeScale(35.f, 7.f, 1.f);
    m_Sprite2->CreateAnimation2D<CAnimation2D>();
    CAnimation2D* Animation2D = m_Sprite2->GetAnimation2D();
    Animation2D->AddAnimationSequence2D("RevolverBullet", false);
    Animation2D->SetSequencePlayRate("RevolverBullet", 4.f);

    m_ColliderBox2D->SetExtent(3.f, 6.f);
    m_ColliderBox2D->SetCollisionProfile("PlayerAttack");

    m_ColliderBox2D->AddCollisionCallbackFunction<CRevolverBullet>(Collision_State::Begin, this,
        &CRevolverBullet::CollisionBegin);

    return true;
}

void CRevolverBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    float    Dist = 100.f * DeltaTime;

    AddRelativePos(GetAxis(AXIS_Y) * Dist);

    m_Distance -= Dist;

    if (m_Distance <= 0.f)
    {
        Active(false);
    }

    m_Sprite2->SetRelativeRotationZ(GetWorldRotation().z + 90.f);

}

void CRevolverBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CRevolverBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CRevolverBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CRevolverBullet* CRevolverBullet::Clone()
{
    return new CRevolverBullet(*this);
}

void CRevolverBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
    {
        Active(false);
    }

}

void CRevolverBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

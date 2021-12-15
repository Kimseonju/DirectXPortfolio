
#include "CosmosSwordBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
CCosmosSwordBullet::CCosmosSwordBullet() :
    m_Distance(500.f)
{
}

CCosmosSwordBullet::CCosmosSwordBullet(const CCosmosSwordBullet& obj) :
    CGameObject(obj)
{
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CCosmosSwordBullet::~CCosmosSwordBullet()
{
}

void CCosmosSwordBullet::Start()
{
    CGameObject::Start();
}

bool CCosmosSwordBullet::Init()
{
    CGameObject::Init();

    m_ColliderBox2D = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

    SetRootComponent(m_Sprite);
    m_Sprite->AddChild(m_ColliderBox2D);

    m_Sprite->SetRelativeScale(43.f, 58.f, 0.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
    CMaterial* Material = m_Sprite->GetMaterial(0);
    Material->AddTexture("CosmosSwordFX2", TEXT("Weapon/Melee/CosmosSwordFX3.png"));

    m_ColliderBox2D->SetExtent(20.f, 10.f);
    m_ColliderBox2D->SetCollisionProfile("PlayerAttack");

    m_ColliderBox2D->AddCollisionCallbackFunction<CCosmosSwordBullet>(Collision_State::Begin, this,
        &CCosmosSwordBullet::CollisionBegin);

    return true;
}

void CCosmosSwordBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    float    Dist = 300.f * DeltaTime;

    AddRelativePos(GetAxis(AXIS_Y) * Dist);

    m_Distance -= Dist;

    if (m_Distance <= 0.f)
    {
        Active(false);
    }

}

void CCosmosSwordBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CCosmosSwordBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CCosmosSwordBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CCosmosSwordBullet* CCosmosSwordBullet::Clone()
{
    return new CCosmosSwordBullet(*this);
}

void CCosmosSwordBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CCosmosSwordBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}


#include "BelialLaserHead.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "BelialBulletEffect.h"
CBelialLaserHead::CBelialLaserHead() 
{
}

CBelialLaserHead::CBelialLaserHead(const CBelialLaserHead& obj) :
    CGameObject(obj)
{
    m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBelialLaserHead::~CBelialLaserHead()
{
}

void CBelialLaserHead::Start()
{
    CGameObject::Start();
}

bool CBelialLaserHead::Init()
{
    CGameObject::Init();

    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default2);
    m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");

    SetRootComponent(m_Sprite);
    m_Sprite->AddChild(m_Collider2D);
    m_Sprite->CreateAnimation2D<CAnimation2D>();
    m_Animation2D = m_Sprite->GetAnimation2D();
    m_Animation2D->AddAnimationSequence2D("Belial_LaserHead", false);
    m_Sprite->SetRelativeScale(27.f, 44.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);


    m_Collider2D->SetExtent(13.f, 22.f);
    m_Collider2D->SetCollisionProfile("EnemyAttack");
    m_Collider2D->AddCollisionCallbackFunction<CBelialLaserHead>(Collision_State::Begin, this,
        &CBelialLaserHead::CollisionBegin);



    return true;
}

void CBelialLaserHead::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    if (m_Animation2D->GetFrameEnd())
    {
        Active(false);
    }
}

void CBelialLaserHead::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBelialLaserHead::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CBelialLaserHead::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CBelialLaserHead* CBelialLaserHead::Clone()
{
    return new CBelialLaserHead(*this);
}

void CBelialLaserHead::LaserCollisionSetting()
{
    if (m_Sprite->GetHorizontalReverse2DEnable())
    {
        m_Collider2D->AddWorldPos(-224.f, 0.f, 0.f);
    }
    else
    {
        m_Collider2D->AddWorldPos(224.f, 0.f, 0.f);
    }
    m_Collider2D->SetExtent(224.f, 22.f);
}

void CBelialLaserHead::SetHorizontalReverse2DEnable(bool Enable)
{
    if (m_Sprite)
    {
        m_Sprite->SetHorizontalReverse2DEnable(Enable);
    }
}

void CBelialLaserHead::CollisionBegin(const HitResult& result, CCollider* Collider)
{

}

void CBelialLaserHead::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

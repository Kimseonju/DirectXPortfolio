
#include "BelialLaserBody.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "BelialBulletEffect.h"
CBelialLaserBody::CBelialLaserBody() 
{
}

CBelialLaserBody::CBelialLaserBody(const CBelialLaserBody& obj) :
    CGameObject(obj)
{
    m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBelialLaserBody::~CBelialLaserBody()
{
}


void CBelialLaserBody::Start()
{
    CGameObject::Start();
}

bool CBelialLaserBody::Init()
{
    CGameObject::Init();

    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
    m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");

    SetRootComponent(m_Sprite);
    m_Sprite->CreateAnimation2D<CAnimation2D>();

    //32,51
    m_Sprite->CreateAnimation2D<CAnimation2D>();
    m_Animation2D = m_Sprite->GetAnimation2D();
    m_Animation2D->AddAnimationSequence2D("Belial_LaserBody", false);
    m_Sprite->SetRelativeScale(32.f, 51.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);


    m_Sprite->AddChild(m_Collider2D);

    m_Collider2D->SetExtent(16.f, 25.f);
    m_Collider2D->SetCollisionProfile("EnemyAttack");
    m_Collider2D->AddCollisionCallbackFunction<CBelialLaserBody>(Collision_State::Begin, this,
        &CBelialLaserBody::CollisionBegin);

    return true;
}

void CBelialLaserBody::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);
    if (m_Animation2D->GetFrameEnd())
    {
        Active(false);
    }
}

void CBelialLaserBody::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBelialLaserBody::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CBelialLaserBody::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CBelialLaserBody* CBelialLaserBody::Clone()
{
    return new CBelialLaserBody(*this);
}

void CBelialLaserBody::SetHorizontalReverse2DEnable(bool Enable)
{
    if (m_Sprite)
    {
        m_Sprite->SetHorizontalReverse2DEnable(Enable);
    }
}

void CBelialLaserBody::CollisionBegin(const HitResult& result, CCollider* Collider)
{

    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
    {
    }
  
}

void CBelialLaserBody::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

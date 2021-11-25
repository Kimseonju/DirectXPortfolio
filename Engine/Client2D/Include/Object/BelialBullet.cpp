
#include "BelialBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "BelialBulletEffect.h"
#include "Player.h"
CBelialBullet::CBelialBullet() :
    m_Distance(500.f)   
{
}

CBelialBullet::CBelialBullet(const CBelialBullet& obj) :
    CGameObject(obj)
{
    m_Collider2DCircle = (CColliderCircle*)FindSceneComponent("Collider2DCircle");
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBelialBullet::~CBelialBullet()
{
}

void CBelialBullet::Start()
{
    CGameObject::Start();
}

bool CBelialBullet::Init()
{
    CGameObject::Init();

    m_Collider2DCircle = CreateSceneComponent<CColliderCircle>("Collider2DCircle");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

    SetRootComponent(m_Sprite);
    m_Sprite->CreateAnimation2D<CAnimation2D>();
    CAnimation2D* Animation=m_Sprite->GetAnimation2D();
    Animation->AddAnimationSequence2D("Belial_Bullet");
    m_Sprite->SetRelativeScale(13.f, 13.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
    m_Sprite->AddChild(m_Collider2DCircle);

    m_Collider2DCircle->SetRadius(6.f);
    m_Collider2DCircle->SetCollisionProfile("EnemyAttack");

    m_Collider2DCircle->AddCollisionCallbackFunction<CBelialBullet>(Collision_State::Begin, this,
        &CBelialBullet::CollisionBegin);

    return true;
}

void CBelialBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    float   Dist = 50.f * DeltaTime;

    AddRelativePos(GetAxis(AXIS_Y) * Dist);

    m_Distance -= Dist;

    if (m_Distance <= 0.f)
        Active(false);
}

void CBelialBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CBelialBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CBelialBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CBelialBullet* CBelialBullet::Clone()
{
    return new CBelialBullet(*this);
}

void CBelialBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{

    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
    {
        //여기에효과
        CGameObject* Obj=m_pScene->SpawnObject<CBelialBulletEffect>("BulletFX");
        Obj->SetWorldPos(GetWorldPos());
        CGlobalValue::MainPlayer->EnemyHit(4);
        Active(false);
    }
    //if(result.DestObject==CGl)
    //Active(false);
    //
    //m_Collision = true;

    // 이펙트를 생성한다.
    //CFlameEffect* pParticle = m_pScene->SpawnObject<CFlameEffect>("FlameEffect",
    //    GetWorldPos());
    //
    //pParticle->SetRelativePos(result.DestObject->GetWorldPos());
    //
    //CParticleSystemComponent* ParticleCom = (CParticleSystemComponent*)pParticle->FindSceneComponent("Particle");

    //ParticleCom->SetMoveDir(-1.f, 0.f, 0.f);

    // 이펙트 사운드를 생성한다.
}

void CBelialBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
}

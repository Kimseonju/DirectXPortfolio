
#include "TempBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"

CTempBullet::CTempBullet() :
    m_Distance(500.f)
{
    m_Collision = false;
}

CTempBullet::CTempBullet(const CTempBullet& obj) :
    CGameObject(obj)
{
    m_Body = (CColliderCircle*)FindSceneComponent("Body");
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
    m_Collision = false;
}

CTempBullet::~CTempBullet()
{
}

void CTempBullet::Start()
{
    CGameObject::Start();
}

bool CTempBullet::Init()
{
    CGameObject::Init();

    m_Body = CreateSceneComponent<CColliderCircle>("Body");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

    SetRootComponent(m_Sprite);

    m_Sprite->SetRelativeScale(50.f, 50.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

    m_Body->SetRadius(sqrtf(50.f * 50.f));
    //m_Body->SetCollisionProfile("Monster");

    m_Sprite->AddChild(m_Body);

    m_Body->AddCollisionCallbackFunction<CTempBullet>(Collision_State::Begin, this,
        &CTempBullet::CollisionBegin);

    return true;
}

void CTempBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    float   Dist = 500.f * DeltaTime;

    AddRelativePos(GetAxis(AXIS_Y) * Dist);

    m_Distance -= Dist;

    if (m_Distance <= 0.f)
        Active(false);

    if (m_Collision)
    {
    }
}

void CTempBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CTempBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CTempBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CTempBullet* CTempBullet::Clone()
{
    return new CTempBullet(*this);
}

void CTempBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{
    Active(false);

    m_Collision = true;

    // 이펙트를 생성한다.
    CFlameEffect* pParticle = m_pScene->SpawnObject<CFlameEffect>("FlameEffect",
        GetWorldPos());

    pParticle->SetRelativePos(result.DestObject->GetWorldPos());

    CParticleSystemComponent* ParticleCom = (CParticleSystemComponent*)pParticle->FindSceneComponent("Particle");

    //ParticleCom->SetMoveDir(-1.f, 0.f, 0.f);

    // 이펙트 사운드를 생성한다.
}

void CTempBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
    m_Collision = false;
}

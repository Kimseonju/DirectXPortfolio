
#include "MetalBoomerangBullet.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "Weapon.h"
#include "ObjectDieEffectObject.h"
#include "../UI/UIManager.h"
#include "../UI/Inventory.h"
CMetalBoomerangBullet::CMetalBoomerangBullet() :
    m_Distance(500.f),
    m_Comeback(false),
    m_Force(500),
    m_ComebackTimeMax(3.f),
    m_ComebackTime(0.f),
    m_Weapon(nullptr)
{
    m_Collision = false;
}

CMetalBoomerangBullet::CMetalBoomerangBullet(const CMetalBoomerangBullet& obj) :
    CGameObject(obj)
{
    m_Collider2DCircle = (CColliderCircle*)FindSceneComponent("Collider2DCircle");
    m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
    m_Collision = false;
}

CMetalBoomerangBullet::~CMetalBoomerangBullet()
{
}

void CMetalBoomerangBullet::Start()
{
    CGameObject::Start();
}

bool CMetalBoomerangBullet::Init()
{
    CGameObject::Init();

    m_Collider2DCircle = CreateSceneComponent<CColliderCircle>("Collider2DCircle");
    m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

    SetRootComponent(m_Sprite);

    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
    m_Sprite->AddChild(m_Collider2DCircle);
    m_Sprite->CreateAnimation2D<CAnimation2D>();
    m_Sprite->SetRelativeScale(37.f, 37.f, 0.f);
    CAnimation2D* Animation2D = m_Sprite->GetAnimation2D();
    Animation2D->AddAnimationSequence2D("MetalBoomerangBullet");
    m_Collider2DCircle->SetRadius(sqrtf(18.f*18.f));
    m_Collider2DCircle->SetCollisionProfile("PlayerAttack");


    m_Collider2DCircle->AddCollisionCallbackFunction<CMetalBoomerangBullet>(Collision_State::Begin, this,
        &CMetalBoomerangBullet::CollisionBegin);

    return true;
}

void CMetalBoomerangBullet::Update(float DeltaTime)
{
    CGameObject::Update(DeltaTime);

    if (m_Comeback)
    {

        float Force = m_Force * DeltaTime;
        m_Force -= 500.f * DeltaTime;
        AddRelativePos(GetAxis(AXIS_Y) * Force);
        m_ComebackTime += DeltaTime;
        if (m_ComebackTime >= m_ComebackTimeMax)
        {
            if (m_Weapon)
            {
                CWeapon* Item = (CWeapon*)CUIManager::GetInst()->GetInventory()->GetWeapon();
                if (Item)
                {
                    if (m_Weapon == Item)
                    {
                        m_Weapon->Enable(true);
                    }
                }
                CObjectDieEffectObject* obj = m_pScene->SpawnObject<CObjectDieEffectObject>
                    ("ObjectDieEffectObject");
                obj->SetWorldPos(GetWorldPos());
                obj->SetWorldScale(40.f, 40.f, 0.f);
                Active(false);
            }
        }
    }
    else
    {
        float   Dist = 500.f * DeltaTime;

        AddRelativePos(GetAxis(AXIS_Y) * Dist);

        m_Distance -= Dist;

        if (m_Distance <= 0.f)
            Active(false);

    }

}

void CMetalBoomerangBullet::PostUpdate(float DeltaTime)
{
    CGameObject::PostUpdate(DeltaTime);
}

void CMetalBoomerangBullet::Collision(float DeltaTime)
{
    CGameObject::Collision(DeltaTime);
}

void CMetalBoomerangBullet::Render(float DeltaTime)
{
    CGameObject::Render(DeltaTime);
}

CMetalBoomerangBullet* CMetalBoomerangBullet::Clone()
{
    return new CMetalBoomerangBullet(*this);
}

void CMetalBoomerangBullet::CollisionBegin(const HitResult& result, CCollider* Collider)
{

    if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Player)
    {
        if (m_Weapon)
        {
            CWeapon* Item = (CWeapon*)CUIManager::GetInst()->GetInventory()->GetWeapon();
            if (Item)
            {
                if (m_Weapon == Item)
                {
                    m_Weapon->Enable(true);
                }
            }
            CObjectDieEffectObject* obj = m_pScene->SpawnObject<CObjectDieEffectObject>
                ("ObjectDieEffectObject");
            obj->SetWorldPos(GetWorldPos());
            obj->SetWorldScale(40.f, 40.f, 0.f);
            Active(false);
        }
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

void CMetalBoomerangBullet::CollisionEnd(const HitResult& result, CCollider* Collider)
{
    m_Collision = false;
}

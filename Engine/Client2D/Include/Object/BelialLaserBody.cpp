
#include "BelialLaserBody.h"
#include "FlameEffect.h"
#include "Scene/Scene.h"
#include "../GlobalValue.h"
#include "BelialBulletEffect.h"
#include "Player.h"
CBelialLaserBody::CBelialLaserBody() :
    m_Animation2D(nullptr)
{
}

CBelialLaserBody::CBelialLaserBody(const CBelialLaserBody& obj) :
    CGameObject(obj)
{
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
    m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default2);
    SetRootComponent(m_Sprite);
    m_Sprite->CreateAnimation2D<CAnimation2D>();
    m_Animation2D = m_Sprite->GetAnimation2D();

    m_Animation2D->AddAnimationSequence2D("Belial_LaserBody", false);
    m_Sprite->SetRelativeScale(32.f, 51.f, 1.f);
    m_Sprite->SetPivot(0.5f, 0.5f, 0.f);


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

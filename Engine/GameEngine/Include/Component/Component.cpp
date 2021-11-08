
#include "Component.h"
#include "../GameObject.h"
CComponent::CComponent()
{
}

CComponent::CComponent(const CComponent& com)
{
}

CComponent::~CComponent()
{
    m_pOwner = nullptr;
}

void CComponent::Active(bool bActive)
{
    CRef::Active(bActive);
}

bool CComponent::IsActive() const
{
    if (!m_Active)
    {
        return false;
    }
    if (!m_pOwner->IsActive())
    {
        return false;
    }
        
    return true;
}

void CComponent::Start()
{
}

bool CComponent::Init()
{
    return true;
}

void CComponent::Update(float DeltaTime)
{
}

void CComponent::PostUpdate(float DeltaTime)
{
}

void CComponent::Collision(float DeltaTime)
{
}

void CComponent::PrevRender(float DeltaTime)
{
}

void CComponent::Render(float DeltaTime)
{
}

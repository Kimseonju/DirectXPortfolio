#include "PlayerInteractionCollision.h"
#include <Resource/Material.h>
CPlayerInteractionCollision::CPlayerInteractionCollision() :
	m_LifeCount(0.f)
{
}

CPlayerInteractionCollision::CPlayerInteractionCollision(const CPlayerInteractionCollision& obj) :
	CGameObject(obj)
{

}

CPlayerInteractionCollision::~CPlayerInteractionCollision()
{
}

void CPlayerInteractionCollision::Start()
{
	CGameObject::Start();
}

bool CPlayerInteractionCollision::Init()
{
	CGameObject::Init();

	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Collider2D->SetCollisionProfile("InteractionInputKey");
	m_Collider2D->SetExtent(10.f, 10.f);

	SetRootComponent(m_Collider2D);
	
	return true;
}

void CPlayerInteractionCollision::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_LifeCount += DeltaTime;
	if (m_LifeCount > 0.3f)
		Active(false);
}

void CPlayerInteractionCollision::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPlayerInteractionCollision::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CPlayerInteractionCollision::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CPlayerInteractionCollision* CPlayerInteractionCollision::Clone()
{
	return new CPlayerInteractionCollision(*this);
}

void CPlayerInteractionCollision::Animation2DNotify(const std::string& Name)
{
}

void CPlayerInteractionCollision::AnimationFrameEnd(const std::string& Name)
{
	Active(false);
}

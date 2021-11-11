
#include "CreateObject.h"
CCreateObject::CCreateObject() :
	m_Animation2D(nullptr)
{
}

CCreateObject::CCreateObject(const CCreateObject& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Animation2D = obj.m_Animation2D->Clone();
}

CCreateObject::~CCreateObject()
{
}

void CCreateObject::Start()
{
	CGameObject::Start();
}

bool CCreateObject::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Sprite->SetWorldScale(31.f, 31.f, 0.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("CreateObjectEffect", false);

	return true;
}

void CCreateObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCreateObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCreateObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CCreateObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CCreateObject* CCreateObject::Clone()
{
	return new CCreateObject(*this);
}

void CCreateObject::Animation2DNotify(const std::string& Name)
{
}

bool CCreateObject::GetFrameEnd()
{
	return m_Animation2D->GetFrameEnd();
}

bool CCreateObject::SpawnStart()
{
	return false;
}

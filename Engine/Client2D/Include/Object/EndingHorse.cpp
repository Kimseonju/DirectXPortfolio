#include "EndingHorse.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CEndingHorse::CEndingHorse():
	m_Animation2D(nullptr)
{
}

CEndingHorse::CEndingHorse(const CEndingHorse& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CEndingHorse::~CEndingHorse()
{
}

void CEndingHorse::Start()
{
	CGameObject::Start();
}

bool CEndingHorse::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default2);


	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->AddWorldPos(-90.f, 20.f, 0.f);
	m_Sprite->SetWorldScale(120.f, 38.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("Horse");
	return true;
}

void CEndingHorse::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingHorse::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEndingHorse::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEndingHorse::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEndingHorse* CEndingHorse::Clone()
{
	return new CEndingHorse(*this);
}


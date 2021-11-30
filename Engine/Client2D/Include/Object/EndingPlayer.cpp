#include "EndingPlayer.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CEndingPlayer::CEndingPlayer() :
	m_Animation2D(nullptr)
{
}

CEndingPlayer::CEndingPlayer(const CEndingPlayer& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CEndingPlayer::~CEndingPlayer()
{
}

void CEndingPlayer::Start()
{
	CGameObject::Start();
}

bool CEndingPlayer::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default);

	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->AddWorldPos(-60.f, 30.f, 0.f);
	m_Sprite->SetWorldScale(15.f, 20.f, 0.f);
	m_Sprite->SetHorizontalReverse2DEnable(true);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("PlayerIdle");
	return true;
}

void CEndingPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEndingPlayer::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEndingPlayer::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEndingPlayer* CEndingPlayer::Clone()
{
	return new CEndingPlayer(*this);
}


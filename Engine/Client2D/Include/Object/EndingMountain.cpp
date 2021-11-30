#include "EndingMountain.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CEndingMountain::CEndingMountain()
{
}

CEndingMountain::CEndingMountain(const CEndingMountain& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CEndingMountain::~CEndingMountain()
{
}

void CEndingMountain::Start()
{
	CGameObject::Start();
}

bool CEndingMountain::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(320.f, 142.f, 0.f);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->AddTexture("TownBG_Day", TEXT("Map/TownBG_Day.png"));
	Material->SetBaseColor(1.5f, 1.5f, 1.5f, 1.f);
	return true;
}

void CEndingMountain::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	Vector3 Pos = GetWorldPos();
	Pos.x += 6.f * DeltaTime;
	if (Pos.x >= 320.f)
	{
		Pos.x -= 960.f;
	}
	SetWorldPos(Pos);
}

void CEndingMountain::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEndingMountain::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEndingMountain::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEndingMountain* CEndingMountain::Clone()
{
	return new CEndingMountain(*this);
}


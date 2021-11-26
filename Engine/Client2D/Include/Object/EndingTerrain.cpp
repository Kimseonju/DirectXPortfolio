#include "EndingTerrain.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CEndingTerrain::CEndingTerrain()
{
}

CEndingTerrain::CEndingTerrain(const CEndingTerrain& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CEndingTerrain::~CEndingTerrain()
{
}

void CEndingTerrain::Start()
{
	CGameObject::Start();
}

bool CEndingTerrain::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_TileMap = CreateSceneComponent<CTileMapComponent>("TileMap");

	SetRootComponent(m_TileMap);
	m_TileMap->Load(TEXT("EndingMap1.map"));
	m_TileMap->SetWorldPos(-170.f, -155.f, 0.f);
	return true;
}

void CEndingTerrain::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingTerrain::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEndingTerrain::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEndingTerrain::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEndingTerrain* CEndingTerrain::Clone()
{
	return new CEndingTerrain(*this);
}


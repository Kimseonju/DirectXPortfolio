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
	m_TileMap->Load(TEXT("EndingMap2.map"));
	//m_TileMap->SetEditorMode(false);
	m_TileMap->SetTileTypePrint(false);

	return true;
}

void CEndingTerrain::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	Vector3 Pos=m_TileMap->GetWorldPos();
	Pos.x += 10.f * DeltaTime;
	if (Pos.x > 310.f)
	{
		Pos.x -= 960.f;
	}
	m_TileMap->SetWorldPos(Pos);
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


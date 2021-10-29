
#include "TestTileMap.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CTestTileMap::CTestTileMap()
{
}

CTestTileMap::CTestTileMap(const CTestTileMap& obj) :
	CGameObject(obj)
{
	m_TileMap = (CTileMapComponent*)FindSceneComponent("TileMap");
}

CTestTileMap::~CTestTileMap()
{
}

void CTestTileMap::Start()
{
	CGameObject::Start();
}

bool CTestTileMap::Init()
{
	CGameObject::Init();

	m_TileMap = CreateSceneComponent<CTileMapComponent>("TileMap");

	SetRootComponent(m_TileMap);

	m_TileMap->CreateTile<CTile>(Tile_Shape::Rhombus, 100, 100, Vector2(160.f, 80.f));
	
	m_TileMap->SetMaterial(0, "MainMap");
	m_TileMap->SetFrameMax(5, 76);
	m_TileMap->SetTileDefaultFrame(3, 2);

	//m_TileMap->CreateTile<CTile>(Tile_Shape::Rect, 100, 100, Vector2(64.f, 64.f));
	//
	//m_TileMap->SetMaterial(0, "MainMapRect");
	//m_TileMap->SetFrameMax(1, 5);
	//m_TileMap->SetTileDefaultFrame(0, 0);
	return true;
}

void CTestTileMap::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CTestTileMap::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTestTileMap::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CTestTileMap::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CTestTileMap* CTestTileMap::Clone()
{
	return new CTestTileMap(*this);
}

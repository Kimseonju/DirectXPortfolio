
#include "Tile.h"
#include "TileMapComponent.h"
#include "../Scene/Scene.h"
#include "ColliderBox2D.h"


int CTile::s_TileCount = 0;

CTile::CTile() :
	m_Shape(Tile_Shape::Rect),
	m_TileType(Tile_Type::None),
	m_IndexX(-1),
	m_IndexY(-1),
	m_Index(-1),
	m_FrameX(0),
	m_FrameY(0),
	m_Collision(true),
	m_Editor(false),
	m_EnableChange(false)
{
}

CTile::CTile(const CTile& tile)
{
	*this = tile;
}

CTile::~CTile()
{

	if (m_CollisionObject.Get())
	{
		m_CollisionObject->Active(false);
		m_CollisionObject = nullptr;
	}
}

Vector2 CTile::GetPos()	const
{
	Vector3	OwnerPos = m_Owner->GetWorldPos();
	Vector2	Pos = m_Pos + Vector2(OwnerPos.x, OwnerPos.y);

	return Pos;
}

bool CTile::Init()
{
	m_Center = m_Pos + m_Size / 2.f;
	if (m_Shape == Tile_Shape::Rect)
	{
		if (m_Collision)
		{
			if (m_Editor)
			{
				s_TileCount++;
				std::string str = std::to_string(s_TileCount);
				m_CollisionObject = m_Owner->GetScene()->SpawnObject<CGameObject>("TileCollisionObject" + str);

				m_ColliderBox2DComponent = (CColliderBox2D*)m_CollisionObject->CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
				m_ColliderBox2DComponent->SetExtent(m_Size.x / 2.f, m_Size.y / 2.f);
				m_ColliderBox2DComponent->SetWorldPos(Vector3(m_Center.x, m_Center.y, 0.f));
				m_CollisionObject->SetRootComponent(m_ColliderBox2DComponent);
				//m_Center = m_Pos + m_Size / 2.f;
				switch (m_TileType)
				{
				case Tile_Type::None:
				{
					m_ColliderBox2DComponent->Enable(false);
					break;
				}
				case Tile_Type::Wall:
				{
					m_ColliderBox2DComponent->Enable(true);
					break;
				}
				case Tile_Type::Crossed_Wall:
				{
					m_ColliderBox2DComponent->Enable(true);
					break;
				}
				}
			}
			else
			{
				switch (m_TileType)
				{
				case Tile_Type::None:
				{
					break;
				}
				case Tile_Type::Wall:
				{
					s_TileCount++;
					std::string str = std::to_string(s_TileCount);
					m_CollisionObject = m_Owner->GetScene()->SpawnObject<CGameObject>("TileCollisionObject" + str);

					m_ColliderBox2DComponent = (CColliderBox2D*)m_CollisionObject->CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
					m_ColliderBox2DComponent->SetExtent(m_Size.x / 2.f, m_Size.y / 2.f);
					m_ColliderBox2DComponent->SetWorldPos(Vector3(m_Center.x, m_Center.y, 0.f));
					m_CollisionObject->SetRootComponent(m_ColliderBox2DComponent);
					m_ColliderBox2DComponent->Enable(true);
					break;
				}
				case Tile_Type::Crossed_Wall:
				{
					s_TileCount++;
					std::string str = std::to_string(s_TileCount);
					m_CollisionObject = m_Owner->GetScene()->SpawnObject<CGameObject>("TileCollisionObject" + str);

					m_ColliderBox2DComponent = (CColliderBox2D*)m_CollisionObject->CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
					m_ColliderBox2DComponent->SetExtent(m_Size.x / 2.f, 0.5f);
					m_ColliderBox2DComponent->SetWorldPos(Vector3(m_Center.x, m_Center.y, 0.f));
					m_ColliderBox2DComponent->AddWorldPos(0.f, m_Size.y / 2.f - 0.5f, 0.f);

					m_CollisionObject->SetRootComponent(m_ColliderBox2DComponent);
					m_ColliderBox2DComponent->Enable(true);
					break;
				}
				}
			}
		}
	}
	return true;
}

void CTile::Start()
{
	m_Center = m_Pos + m_Size / 2.f;

	m_NodeDistW = m_Size.x * m_Size.x;
	m_NodeDistH = m_Size.y * m_Size.y;
	m_NodeDistD = m_Size.x * m_Size.x + m_Size.y * m_Size.y;

	float	HalfW = m_Size.x * 0.5f;
	float	HalfH = m_Size.y * 0.5f;

	m_NodeDistDHalf = HalfW * HalfW + HalfH * HalfH;
}

void CTile::Update(float DeltaTime)
{
	if (m_EnableChange)
	{
		m_EnableChange = false;
		if (m_CollisionObject)
		{
			m_CollisionObject->Enable(m_Enable);
			m_ColliderBox2DComponent->Enable(m_Enable);
		}
	}
}

void CTile::PostUpdate(float DeltaTime)
{
	Vector3	OwnerPos = m_Owner->GetWorldPos();

	Vector2	Pos = m_Pos + Vector2(OwnerPos.x, OwnerPos.y);

	Matrix	matScale, matTranslate;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matTranslate.Translation(Pos.x, Pos.y, 0.f);

	m_matWorld = matScale * matTranslate;
}

void CTile::Render(float DeltaTime)
{
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_Shape, sizeof(Tile_Shape), 1, pFile);
	fwrite(&m_TileType, sizeof(Tile_Type), 1, pFile);
	fwrite(&m_Pos, sizeof(Vector2), 1, pFile);
	fwrite(&m_Size, sizeof(Vector2), 1, pFile);
	fwrite(&m_Center, sizeof(Vector2), 1, pFile);
	fwrite(&m_FrameStart, sizeof(Vector2), 1, pFile);
	fwrite(&m_FrameEnd, sizeof(Vector2), 1, pFile);
	fwrite(&m_IndexX, sizeof(int), 1, pFile);
	fwrite(&m_IndexY, sizeof(int), 1, pFile);
	fwrite(&m_Index, sizeof(int), 1, pFile);
	int num = m_Collision ? 1 : 0;
	fwrite(&num, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_Shape, sizeof(Tile_Shape), 1, pFile);
	fread(&m_TileType, sizeof(Tile_Type), 1, pFile);
	fread(&m_Pos, sizeof(Vector2), 1, pFile);
	fread(&m_Size, sizeof(Vector2), 1, pFile);
	fread(&m_Center, sizeof(Vector2), 1, pFile);
	fread(&m_FrameStart, sizeof(Vector2), 1, pFile);
	fread(&m_FrameEnd, sizeof(Vector2), 1, pFile);
	fread(&m_IndexX, sizeof(int), 1, pFile);
	fread(&m_IndexY, sizeof(int), 1, pFile);
	fread(&m_Index, sizeof(int), 1, pFile);
	m_FrameX = (int)m_FrameStart.x;
	m_FrameY = (int)m_FrameStart.y;

	int num = 0;
	fread(&num, sizeof(int), 1, pFile);
	if (num == 1)
	{
		m_Collision = true;
	}
	else
		m_Collision = false;
}

void CTile::SetCollisionProfile(const std::string& TilePass, const std::string& TileNoPass)
{
	if (!m_ColliderBox2DComponent)
		return;
	switch (m_TileType)
	{
	case Tile_Type::None:
	{
		m_ColliderBox2DComponent->Enable(false);
		break;
	}
	case Tile_Type::Wall:
	{
		m_ColliderBox2DComponent->SetCollisionProfile(TileNoPass);
		break;
	}
	case Tile_Type::Crossed_Wall:
	{
		m_ColliderBox2DComponent->SetCollisionProfile(TilePass);
		break;
	}
	}
}

void CTile::MapClear()
{
	if (m_CollisionObject)
	{
		m_CollisionObject->Active(false);
		m_ColliderBox2DComponent->Active(false);
	}
}

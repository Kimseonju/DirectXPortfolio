
#include "Tile.h"

CTile::CTile() :
	m_Shape(Tile_Shape::Rect),
	m_TileType(Tile_Type::None),
	m_IndexX(-1),
	m_IndexY(-1),
	m_Index(-1)
{
}

CTile::CTile(const CTile& tile)
{
	*this = tile;
}

CTile::~CTile()
{
}

bool CTile::Init()
{
	return true;
}

void CTile::Start()
{
}

void CTile::Update(float DeltaTime)
{
}

void CTile::PostUpdate(float DeltaTime)
{
	Matrix	matScale, matTranslate;

	matScale.Scaling(m_Size.x, m_Size.y, 1.f);
	matTranslate.Translation(m_Pos.x, m_Pos.y, 0.f);

	m_matWorld = matScale * matTranslate;
}

void CTile::Render(float DeltaTime)
{
}

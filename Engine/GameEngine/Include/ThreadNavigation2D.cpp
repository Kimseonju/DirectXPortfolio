#include "ThreadNavigation2D.h"
#include "Component/TileMapComponent.h"
#include "Component/Tile.h"

CThreadNavigation2D::CThreadNavigation2D()
{
	m_hExitEvent = CreateEvent(0, FALSE, FALSE, 0);
}

CThreadNavigation2D::~CThreadNavigation2D()
{
	SetLoop(false);

	if (m_hExitEvent)
	{
		WaitForSingleObject(m_hExitEvent, INFINITE);
		CloseHandle(m_hExitEvent);
	}

	while (!m_WorkQueue.Empty())
	{
		NavWorkInfo* Info = nullptr;

		m_WorkQueue.Pop(Info);

		SAFE_DELETE(Info);
	}
}

void CThreadNavigation2D::CreateNavigationInfo(CTileMapComponent* TileMap)
{
	int	TileCount = TileMap->GetTileCount();

	m_NavInfo.vecNavInfo.resize((size_t)TileCount);
	m_NavInfo.vecOpen.resize((size_t)TileCount);
	m_NavInfo.vecClose.resize((size_t)TileCount);

	m_NavInfo.CountX = TileMap->GetTileCountX();
	m_NavInfo.CountY = TileMap->GetTileCountY();

	for (int i = 0; i < TileCount; ++i)
	{
		CTile* Tile = TileMap->GetTile(i);

		m_NavInfo.vecNavInfo[i].Tile = Tile;
		m_NavInfo.vecNavInfo[i].IndexX = Tile->GetIndexX();
		m_NavInfo.vecNavInfo[i].IndexY = Tile->GetIndexY();
		m_NavInfo.vecNavInfo[i].Index = Tile->GetIndex();
	}
}

void CThreadNavigation2D::Run()
{
}

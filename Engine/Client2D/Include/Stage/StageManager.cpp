#include "StageManager.h"
#include "../GlobalValue.h"




void CStageManager::CreateDungeon()
{
	m_vecStageInfo.resize(m_MapSize);
	for (int i = 0; i < m_MapSize; i++)
	{
		m_vecStageInfo[i].resize(m_MapSize);
	}

	while (true)
	{
		// 맵 정보 초기화
		for (int x = 0; x < m_MapSize; x++)
		{
			for (int y = 0; y < m_MapSize; y++)
			{
				for (int dir = 0; dir < 4; dir++)
				{
					m_vecStageInfo[x][y].Wall[dir] = true;
				}
				m_vecStageInfo[x][y].visit = false;
				m_vecStageInfo[x][y].StageType = 0;
			}
		}
		int startX = GetRandom(0,m_MapSize);
		int startY = GetRandom(0,m_MapSize);
		CreateStage(startX, startY);

		if (CreateStage_Special()) 
		{
			break;
		}
	}
}

void CStageManager::CreateStage(int x, int y)
{
	if (m_vecStageInfo[x][y].visit) return;
	m_vecStageInfo[x][y].visit = true;

	int dir_x[4] = { 1,0,0,-1 };
	int dir_y[4] = { 0,1,-1,0 };
	bool checkDir[4] = { false, false, false, false };
	while (true)
	{
		if (checkDir[0] && checkDir[1] && checkDir[2] && checkDir[3]) break;

		int Dir = GetRandom(0, 4);
		if (checkDir[Dir]) continue;
		checkDir[Dir] = true;

		int nextX = x + dir_x[Dir];
		int nextY = y + dir_y[Dir];

		if (nextX < 0 || nextY >= m_MapSize || nextX < 0 || nextY >= m_MapSize)
			continue;

		if (m_vecStageInfo[nextX][nextY].visit)
			continue;
		
		//연결
		m_vecStageInfo[x][y].Wall[Dir] = false;
		m_vecStageInfo[nextX][nextY].Wall[(Dir + 2) % 4] = false;
		CreateStage(nextX, nextY);
	}
}

bool CStageManager::CreateStage_Special()
{
	/*
	
	기본제작 (맵제작후수정필요)
	*/
	std::vector<Vector2> vecStagePos;
	Vector2 StartPos;
	Vector2 EndPos;
	Vector2 ShopPos;
	Vector2 RestaurantPos;

	//시작방 체크할곳
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			//벽체크 (오른쪽출발맵 1개)
			if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	int RandomCount = GetRandom(0, (int)vecStagePos.size());
	StartPos = vecStagePos[RandomCount];
	m_vecStageInfo[(int)StartPos.x][(int)StartPos.y].StageType = 1;

	//끝방 체크
	vecStagePos.clear();
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			if (StartPos.x == x && StartPos.y == y)
				continue;
			//벽체크 
			if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	RandomCount = GetRandom(0, (int)vecStagePos.size());
	EndPos = vecStagePos[RandomCount];
	m_vecStageInfo[(int)EndPos.x][(int)EndPos.y].StageType = 2;

	//상점

	vecStagePos.clear();
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			//벽체크 
			if (StartPos.x == x && StartPos.y == y)
				continue;
			if (EndPos.x == x && EndPos.y == y)
				continue;
			if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	RandomCount = GetRandom(0, (int)vecStagePos.size());
	ShopPos = vecStagePos[RandomCount];
	m_vecStageInfo[(int)ShopPos.x][(int)ShopPos.y].StageType = 3;
	//레스토랑

	vecStagePos.clear();
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			//벽체크 
			if (StartPos.x == x && StartPos.y == y)
				continue;
			if (EndPos.x == x && EndPos.y == y)
				continue;
			if (ShopPos.x == x && ShopPos.y == y)
				continue;
			if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	RandomCount = GetRandom(0, (int)vecStagePos.size());
	RestaurantPos = vecStagePos[RandomCount];
	m_vecStageInfo[(int)RestaurantPos.x][(int)RestaurantPos.y].StageType = 4;


	//방설정완료



	return true;
}

DEFINITION_SINGLE(CStageManager)
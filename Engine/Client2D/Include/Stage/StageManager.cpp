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
		int startX = CGlobalValue::GetRandom(m_MapSize);
		int startY = CGlobalValue::GetRandom(m_MapSize);
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

		int Dir = CGlobalValue::GetRandom(4);
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
	return false;
}

DEFINITION_SINGLE(CStageManager)
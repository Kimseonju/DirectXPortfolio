#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"
#include "Stage.h"


struct tagStageInfo
{
	//방문했는지
	bool visit;

	//스테이지타입
	int StageType; // 방의 타입 , -1 : 사용하지 않는 방, 0 : 일반방, 1 : 시작방, 2: 끝방 , 3 : 식당방, 4 : 상점방 
	bool Wall[4]; // 방의 벽, (L T R B) 순서
};
class CStageManager
{



private:
	CStage* m_SelectStage;
	std::vector<std::vector<CStage*>> m_vecStage;
	std::vector<std::vector<tagStageInfo>> m_vecStageInfo;

	int m_CurIndexX, m_CurIndexY;

	int m_MapSize; // 전체 맵 사이즈(카운트)
private:

	void CreateBossStage();
	
	void CreateDungeon();
	void CreateStage(int x, int y);
	//시작, 끝, 상점, 레스토랑
	bool CreateStage_Special(); 
	
	void ReleaseStage();
	DECLARE_SINGLE(CStageManager)
};


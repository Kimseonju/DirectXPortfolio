#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"
#include "Stage.h"

class CStageManager
{



private:
	CStage* m_SelectStage;
	std::vector<std::vector<CStage*>> m_vecStage;
	std::vector<std::vector<StageInfo>> m_vecStageInfo;

	int m_CurIndexX, m_CurIndexY;

	int m_MapSize; // ��ü �� ������(ī��Ʈ)
private:

	void CreateBossStage();
	
	void CreateDungeon();
	void CreateStage(int x, int y);
	//����, ��, ����, �������
	bool CreateStage_Special(); 
	
	void ReleaseStage();
	DECLARE_SINGLE(CStageManager)
};


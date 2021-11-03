#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"
#include "Stage.h"


struct tagStageInfo
{
	//�湮�ߴ���
	bool visit;

	//��������Ÿ��
	int StageType; // ���� Ÿ�� , -1 : ������� �ʴ� ��, 0 : �Ϲݹ�, 1 : ���۹�, 2: ���� , 3 : �Ĵ��, 4 : ������ 
	bool Wall[4]; // ���� ��, (L T R B) ����
};
class CStageManager
{



private:
	CStage* m_SelectStage;
	std::vector<std::vector<CStage*>> m_vecStage;
	std::vector<std::vector<tagStageInfo>> m_vecStageInfo;

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


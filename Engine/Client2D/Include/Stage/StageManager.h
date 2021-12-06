#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"
#include "Stage.h"
#include "Resource/Sound.h"

class CStageManager
{



private:
	CStage* m_SelectStage;
	std::vector<std::vector<CStage*>> m_vecStage;
	std::vector<std::vector<StageInfo>> m_vecStageInfo;
	bool m_BossStage;
	Vector2 m_StartPos;
	Vector2 m_EndPos;
	Vector2 m_ShopPos;
	Vector2 m_RestaurantPos;

	Vector2 m_CurPos;


	CSound*	m_BGMSound[(int)StageType::Boss+1];


	//������,����
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecMainDoorStageSpawnInfo;
	int m_StartEndCount;
	//�Ϲݹ�
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecStageSpawnInfo;
	//������
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecBossStageSpawnInfo;

	//������
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecShopStageSpawnInfo;

	//�������
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecRestaurantStageSpawnInfo;

	int m_MapSize; // ��ü �� ������(ī��Ʈ)
	class CScene* m_pScene;
	int m_MapCount;
public:
	bool IsBossStage()
	{
		return m_BossStage;
	}
	std::string GetCurName();
	CStage* GetCurStage();
	Vector2 GetCurPos() const
	{
		return m_CurPos;
	}
	std::vector<std::vector<StageInfo>>& GetvecStageInfo()
	{
		return m_vecStageInfo;
	}
	int GetMapSize() const
	{
		return m_MapSize;
	}
	void SetScene(class CScene* Scene)
	{
		m_pScene = Scene;
	}
	void SetBossStage(bool Stage)
	{
		m_BossStage = Stage;
	}
public:
	void Init();
	void Start();
	void Update(float DeltaTime);

	void CreateBossStage();
	
	void CreateDungeon();
	void CreateStage(int x, int y);
	void NextStage(Stage_Dir Dir);
	void GateStage(Vector2 Pos);
	void PlayStage(Stage_Dir Dir);
	void PlayGateStage();
	//����, ��, ����, �������
	bool CreateStage_Special(); 
	
	void ReleaseStage();
	void LoadStage(FILE* pFile, const char* Name);
	void AllLoadStage(const TCHAR* FileName);
	void PushMainDoorStageSpawnInfo(int Door, StageObjectsInfo Info);
	void PushStageSpawnInfo(int Door, StageObjectsInfo Info);
	void PushBossStageSpawnInfo(int Door, StageObjectsInfo Info);
	void PushShopStageSpawnInfo(int Door, StageObjectsInfo Info);
	void PushRestaurantStageSpawnInfo(int Door, StageObjectsInfo Info);

	StageObjectsInfo GetMainDoorStageSpawnInfo(int Door);
	StageObjectsInfo GetStageSpawnInfo(int Door);
	StageObjectsInfo GetBossStageSpawnInfo(int Door);
	StageObjectsInfo GetShopStageSpawnInfo(int Door);
	StageObjectsInfo GetRestaurantStageSpawnInfo(int Door);

public:

	void BGMSoundUpdate(StageType Type);
	void BGMBossSoundPlay();
	void BGMSoundPause();
	DECLARE_SINGLE(CStageManager)

};


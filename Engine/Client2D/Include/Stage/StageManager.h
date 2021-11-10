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

	Vector2 m_StartPos;
	Vector2 m_EndPos;
	Vector2 m_ShopPos;
	Vector2 m_RestaurantPos;

	Vector2 m_CurPos;
	//시작점,끝점
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecMainDoorStageSpawnInfo;
	int m_StartEndCount;
	//일반방
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecStageSpawnInfo;
	//보스방
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecBossStageSpawnInfo;

	//상점방
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecShopStageSpawnInfo;

	//레스토랑
	std::unordered_map<int, std::vector<StageObjectsInfo>>m_vecRestaurantStageSpawnInfo;

	int m_MapSize; // 전체 맵 사이즈(카운트)
	class CScene* m_pScene;
	int m_MapCount;
public:
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
public:
	void Init();
	void Start();
	void Update(float DeltaTime);

	void CreateBossStage();
	
	void CreateDungeon();
	void CreateStage(int x, int y);
	void NextStage(Stage_Dir Dir);
	void PlayStage(Stage_Dir Dir);
	//시작, 끝, 상점, 레스토랑
	bool CreateStage_Special(); 
	
	void ReleaseStage();

	void LoadStage(FILE* pFile);
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
	DECLARE_SINGLE(CStageManager)

};


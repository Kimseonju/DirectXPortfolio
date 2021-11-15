#pragma once
#include "GameEngine.h"
#include "PlayerUI.h"
#include "Inventory.h"
#include "StageMap.h"
#include "BossSpawnUI.h"
class CUIManager
{

public:
	bool Init(CScene* Scene);
public:
	CPlayerUI* GetPlayerUI()
	{
		return m_PlayerUI;
	}

	CInventory* GetInventory()
	{
		return m_InventoryUI;
	}
	CStageMap* GetStageMap()
	{
		return m_StageMapUI;
	}

	CBossSpawnUI* GetBossSpawnUI()
	{
		return m_BossSpawnUI;
	}
private:
	CSharedPtr<CPlayerUI> m_PlayerUI;
	CSharedPtr<CInventory> m_InventoryUI;
	CSharedPtr<CStageMap> m_StageMapUI;
	CSharedPtr<CBossSpawnUI> m_BossSpawnUI;
	CScene* m_pScene;


public:
	DECLARE_SINGLE(CUIManager)
};


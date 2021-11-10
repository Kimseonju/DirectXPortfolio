#pragma once
#include "GameEngine.h"
#include "PlayerUI.h"
#include "Inventory.h"
#include "StageMap.h"

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

private:
	CSharedPtr<CPlayerUI> m_PlayerUI;
	CSharedPtr<CInventory> m_InventoryUI;
	CSharedPtr<CStageMap> m_StageMapUI;
	CScene* m_pScene;


public:
	DECLARE_SINGLE(CUIManager)
};


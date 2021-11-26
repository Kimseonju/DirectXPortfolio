#pragma once
#include "GameEngine.h"
#include "PlayerUI.h"
#include "Inventory.h"
#include "StageMap.h"
#include "BossSpawnUI.h"
#include "BossDieUI.h"
#include "BossUI.h"
#include "ShopUI.h"
#include "FadeInOutUI.h"
#include "StatusUI.h"
#include "MiniMap.h"
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
	CBossDieUI* GetBossDieUI()
	{
		return m_BossDieUI;
	}
	CBossUI* GetBossUI()
	{
		return m_BossUI;
	}

	CShopUI* GetShopUI()
	{
		return m_ShopUI;
	}

	CFadeInOutUI* GetFadeInOutUI()
	{
		return m_FadeInOutUI;
	}
	CStatusUI* GetStatusUI()
	{
		return m_StatusUI;
	}
	CMiniMap* GetMiniMapUI()
	{
		return m_MiniMapUI;
	}
private:
	CSharedPtr<CPlayerUI> m_PlayerUI;
	CSharedPtr<CInventory> m_InventoryUI;
	CSharedPtr<CStageMap> m_StageMapUI;
	CSharedPtr<CBossSpawnUI> m_BossSpawnUI;
	CSharedPtr<CBossDieUI> m_BossDieUI;
	CSharedPtr<CBossUI> m_BossUI;
	CSharedPtr<CShopUI> m_ShopUI;
	CSharedPtr<CFadeInOutUI> m_FadeInOutUI;
	CSharedPtr<CStatusUI> m_StatusUI;
	CSharedPtr<CMiniMap> m_MiniMapUI;
	CScene* m_pScene;


public:
	DECLARE_SINGLE(CUIManager)
};


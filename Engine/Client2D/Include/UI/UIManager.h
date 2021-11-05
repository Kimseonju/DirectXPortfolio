#pragma once
#include "GameEngine.h"
#include "PlayerUI.h"
#include "Inventory.h"

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


private:
	CSharedPtr<CPlayerUI> m_PlayerUI;
	CSharedPtr<CInventory> m_InventoryUI;
	CScene* m_pScene;


public:
	DECLARE_SINGLE(CUIManager)
};


#include "UIManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"

DEFINITION_SINGLE(CUIManager)

CUIManager::CUIManager()
{
}

CUIManager::~CUIManager()
{
}

bool CUIManager::Init(CScene* Scene)
{
	if (m_pScene)
		return false;
	m_pScene = Scene;
	m_InventoryUI = m_pScene->GetViewport()->AddWindow<CInventory>("Inventory");
	m_StageMapUI = m_pScene->GetViewport()->AddWindow<CStageMap>("StageMapUI");
	m_PlayerUI = m_pScene->GetViewport()->AddWindow<CPlayerUI>("PlayerUI");
	return true;
}

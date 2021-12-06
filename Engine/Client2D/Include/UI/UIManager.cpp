#include "UIManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Scene/Viewport.h"
#include "BasicMouse.h"

DEFINITION_SINGLE(CUIManager)

CUIManager::CUIManager():
	m_pScene(nullptr)
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
	m_BossSpawnUI = m_pScene->GetViewport()->AddWindow<CBossSpawnUI>("BossSpawnUI");
	m_BossDieUI = m_pScene->GetViewport()->AddWindow<CBossDieUI>("BossDieUI");
	m_BossUI = m_pScene->GetViewport()->AddWindow<CBossUI>("BossUI");
	m_ShopUI = m_pScene->GetViewport()->AddWindow<CShopUI>("ShopUI");
	m_FadeInOutUI = m_pScene->GetViewport()->AddWindow<CFadeInOutUI>("FadeInOutUI");
	m_StatusUI = m_pScene->GetViewport()->AddWindow<CStatusUI>("StatusUI");
	m_MiniMapUI = m_pScene->GetViewport()->AddWindow<CMiniMap>("MiniMapUI");
	m_FadeInOut_WhiteUI = m_pScene->GetViewport()->AddWindow<CFadeInOut_White>("FadeInOut_WhiteUI");
	m_BossSpawnUI->Enable(false);
	m_InventoryUI->Enable(false);
	m_StageMapUI->Enable(false);
	m_ShopUI->Enable(false);
	m_BossUI->Enable(false);
	m_StatusUI->Enable(false);
	//m_BossDieUI->Enable(false);

	m_RestaurantUI = m_pScene->GetViewport()->AddWindow<CRestaurantUI>("RestaurantUI");
	//m_TEstUI = m_pScene->GetViewport()->AddWindow<CResturantInfoWidget>("TEstUI");
	m_RestaurantUI->Enable(false);
	return true;
}

void CUIManager::MouseUIWorldCheck()
{
	if (m_InventoryUI->IsEnable()|| m_StageMapUI->IsEnable() || m_ShopUI->IsEnable() ||
		m_StatusUI->IsEnable() || m_RestaurantUI->IsEnable())
	{
		CGlobalValue::MainMouse->SetState(Mouse_State::UI);
	}
	else
	{
		CGlobalValue::MainMouse->SetState(Mouse_State::World);
	}
}

bool CUIManager::InventoryUIOnOff()
{
	if (m_InventoryUI->IsEnable())
	{
		m_InventoryUI->Enable(false);
		return false;
	}
	else
	{
		if (m_RestaurantUI->IsEnable() || m_StageMapUI->IsEnable())
		{
			return false;
		}
		m_InventoryUI->Enable(true);
		return true;
	}
}

bool CUIManager::StageMapUIOnOff()
{
	if (m_StageMapUI->IsEnable())
	{
		m_StageMapUI->Enable(false);
		return false;
	}
	else
	{

		if (m_RestaurantUI->IsEnable() || m_InventoryUI->IsEnable() || m_ShopUI->IsEnable())
		{
			return false;
		}
		m_StageMapUI->Enable(true);
		return true;
	}
}

bool CUIManager::ShopUIOnOff()
{
	if (m_ShopUI->IsEnable())
	{
		m_ShopUI->Enable(false);
		return false;
	}
	else
	{
		if (m_RestaurantUI->IsEnable() || m_StageMapUI->IsEnable())
		{
			return false;
		}
		m_ShopUI->Enable(true);
		m_InventoryUI->Enable(true);
		return true;

	}
}

bool CUIManager::StatusUIOnOff()
{
	if (m_StatusUI->IsEnable())
	{
		m_StatusUI->Enable(false);
		return false;
	}
	else
	{
		if (m_RestaurantUI->IsEnable() || m_StageMapUI->IsEnable() || m_ShopUI->IsEnable())
		{
			return false;
		}
		m_StatusUI->Enable(true);
		return true;
	}
}

bool CUIManager::RestaurantUIOnOff()
{
	if (m_RestaurantUI->IsEnable())
	{
		m_RestaurantUI->Enable(false);
		return false;
	}
	else
	{
		if (m_RestaurantUI->IsEnable() || m_InventoryUI->IsEnable() || m_ShopUI->IsEnable() ||
			m_StageMapUI->IsEnable() || m_StatusUI->IsEnable())
		{
			return false;
		}
		m_RestaurantUI->Enable(true);
		return true;
	}
}

void CUIManager::UIOff()
{
	if (m_RestaurantUI->IsEnable())
	{
		m_RestaurantUI->Enable(false);
		return;
	}
	if (m_StageMapUI->IsEnable())
	{
		m_StageMapUI->Enable(false);
		return;
	}
	if (m_ShopUI->IsEnable())
	{
		m_ShopUI->Enable(false);
		m_InventoryUI->Enable(false);
		return;
	}
	if (m_StatusUI->IsEnable())
	{
		m_StatusUI->Enable(false);
		return;
	}
}

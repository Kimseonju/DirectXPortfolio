#include "NavigationManager.h"
#include "Navigation2D.h"
#include "Navigation3D.h"
#include "Render/RenderManager.h"
#include "Component/TileMapComponent.h"
#include "ThreadManager.h"
#include "ThreadNavigation2D.h"

DEFINITION_SINGLE(CNavigationManager)

CNavigationManager::CNavigationManager() :
	m_Navigation(nullptr)
{
}

CNavigationManager::~CNavigationManager()
{
	SAFE_DELETE(m_Navigation);
}

bool CNavigationManager::Init()
{
	return true;
}

void CNavigationManager::CreateNavigation()
{
	SAFE_DELETE(m_Navigation);

	m_RenderSpace = CRenderManager::GetInst()->GetRenderSpace();

	switch (m_RenderSpace)
	{
	case Render_Space::Render2D:
		m_Navigation = new CNavigation2D;
		break;
	case Render_Space::Render3D:
		m_Navigation = new CNavigation3D;
		break;
	}
}

void CNavigationManager::SetTileInfo()
{
	CTileMapComponent* TileMap = ((CNavigation2D*)m_Navigation)->GetLastTileMap();

	if (!TileMap)
		return;

	// 스레드를 생성한다.
	for (int i = 0; i < 4; ++i)
	{
		std::string	Name = "NavThread";
		Name += (i + 1);

		CThreadNavigation2D* Thread = CThreadManager::GetInst()->CreateThread<CThreadNavigation2D>(Name);

		Thread->SetNavigation(m_Navigation);
		Thread->CreateNavigationInfo(TileMap);

		m_vecThread2D.push_back(Thread);

		Thread->Start();
	}
}

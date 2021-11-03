#pragma once

#include "GameEngine.h"

class CNavigationManager
{
private:
	Render_Space		m_RenderSpace;
	class CNavigation* m_Navigation;
	std::vector<class CThreadNavigation2D*>	m_vecThread2D;

public:
	class CNavigation* GetNavigation()	const
	{
		return m_Navigation;
	}

public:
	bool Init();
	void CreateNavigation();
	void SetTileInfo();

	DECLARE_SINGLE(CNavigationManager)
};


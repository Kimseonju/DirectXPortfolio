#pragma once

#include "GameEngine.h"

class CNavigationManager
{
private:
	Render_Space		m_RenderSpace;
	class CNavigation* m_Navigation;
	std::vector<class CThreadNavigation*>	m_vecThread;

public:
	class CNavigation* GetNavigation()	const
	{
		return m_Navigation;
	}

public:
	bool Init();
	void CreateNavigation();
	void SetTileInfo();
	bool FindPath(const Vector3& Start, const Vector3& Goal,
		class CSceneComponent* Component, void(CSceneComponent::* Func)(std::vector<Vector3>&));

	DECLARE_SINGLE(CNavigationManager)
};


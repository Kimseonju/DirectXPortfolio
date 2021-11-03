#pragma once
#include "Navigation.h"
class CNavigation2D :
	public CNavigation
{
	friend class CNavigationManager;

protected:
	CNavigation2D();
	virtual ~CNavigation2D();

private:
	std::vector<CSharedPtr<CTileMapComponent>>	m_NavData;

public:
	CTileMapComponent* GetTileMap(int Index = 0)	const
	{
		return m_NavData[Index];
	}

	CTileMapComponent* GetLastTileMap()	const
	{
		if (m_NavData.empty())
			return nullptr;

		return m_NavData[m_NavData.size() - 1];
	}

	void AddNavData(CTileMapComponent* Data)
	{
		m_NavData.push_back(Data);
	}

	void DeleteTileMapData(CTileMapComponent* Data)
	{
		auto	iter = m_NavData.begin();
		auto	iterEnd = m_NavData.end();

		for (; iter != iterEnd; ++iter)
		{
			if (*iter == Data)
			{
				m_NavData.erase(iter);
				break;
			}
		}
	}
};


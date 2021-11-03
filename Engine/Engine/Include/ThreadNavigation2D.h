#pragma once

#include "Thread.h"
#include "Sync.h"
#include "Component/Tile.h"
#include "Queue.h"

enum class Nav_Insert_Type
{
	None,
	Open,
	Close
};

struct NavInfo
{
	CTile* Tile;
	float	Cost;
	float	Dist;
	float	Total;
	Nav_Insert_Type	Type;
	int		IndexX;
	int		IndexY;
	int		Index;
	NavInfo* Parent;

	NavInfo()
	{
		Tile = nullptr;
		Parent = nullptr;
		Cost = 0.f;
		Dist = 0.f;
		Total = 0.f;
		IndexX = -1;
		IndexY = -1;
		Index = -1;
		Type = Nav_Insert_Type::None;
	}

	void Clear()
	{
		Parent = nullptr;
		Cost = 0.f;
		Dist = 0.f;
		Total = 0.f;
		Type = Nav_Insert_Type::None;
	}
};

struct NavInfoManager
{
	std::vector<NavInfo>	vecNavInfo;
	std::vector<NavInfo>	vecOpen;
	std::vector<NavInfo>	vecClose;
	int		OpenCount;
	int		UseCount;
	int		CountX;
	int		CountY;

	NavInfoManager()
	{
		OpenCount = 0;
		UseCount = 0;
		CountX = 0;
		CountY = 0;
	}
};

struct NavWorkInfo
{
	Vector3	Start;
	Vector3	Goal;
	class CSceneComponent* CallbackComponent;
	std::function<void(std::vector<Vector3>&)>	func;
};

class CThreadNavigation2D :
	public CThread
{
	friend class CThreadManager;

protected:
	CThreadNavigation2D();
	virtual ~CThreadNavigation2D();

private:
	class CNavigation* m_Navigation;
	NavInfoManager	m_NavInfo;
	CQueue<NavWorkInfo*, 500>	m_WorkQueue;
	std::vector<Vector3>		m_vecResult;
	HANDLE						m_hExitEvent;

public:
	int GetWorkCount()	const
	{
		return m_WorkQueue.Size();
	}


public:
	void SetNavigation(class CNavigation* Navigation)
	{
		m_Navigation = Navigation;
	}

	void CreateNavigationInfo(class CTileMapComponent* TileMap);

	void AddWorkInfo(const Vector3& Start, const Vector3& Goal,
		class CSceneComponent* Component, void(CSceneComponent::* Func)(std::vector<Vector3>&))
	{
		NavWorkInfo* Info = new NavWorkInfo;

		Info->Start = Start;
		Info->Goal = Goal;
		Info->CallbackComponent = Component;
		Info->func = std::bind(Func, Component, std::placeholders::_1);

		m_WorkQueue.Push(Info);
	}

public:
	virtual void Run();
};


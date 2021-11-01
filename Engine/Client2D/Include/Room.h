#pragma once

#include "GlobalValue.h"
#include <GameObject.h>
#include "GlobalValue.h"
#include "Stage/Stage.h"
class CRoom
{

public:
	CRoom();
	CRoom(const CRoom& obj);
	virtual ~CRoom();

public:
	std::vector<CSharedPtr<CGameObject>> m_EnemyObject;
	//원통,상자
	std::vector<CSharedPtr<CGameObject>> m_ContainerObject;

	std::vector<CSharedPtr<CGameObject>> m_DoorObject;
	std::vector<CSharedPtr<CGameObject>> m_Trigger;

	CRoom* m_LeftRoom;
	CRoom* m_RightRoom;
	CRoom* m_UpRoom;
	CRoom* m_DownRoom;
	bool m_NextDoor;
	int m_Posx;
	int m_Posy;
	CStage* m_Stage;
public:

	int GetRoom_Dir();
	void Room_Dir(int num);
public:
	void SetNextDoor(bool Next)
	{
		m_NextDoor = Next;
	}
	void SetPos(int x, int y)
	{
		m_Posx = x;
		m_Posy = y;
	}
	void SetStage(CStage* Stage);
public:

	virtual void Start(RoomCreate_Dir RoomCreateDir);
	virtual bool Init(RoomCreate_Dir PrevDir);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CRoom* Clone();
};

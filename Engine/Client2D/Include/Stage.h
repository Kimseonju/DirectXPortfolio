#pragma once

#include "GlobalValue.h"
#include <GameObject.h>
#include "GlobalValue.h"
class CStage 
{
public:
	CStage();
	CStage(const CStage& obj);
	virtual ~CStage();

public:
	class CRoom* m_Rooms[20][20];
	int m_RoomSize;
public:
	//방이 없다 true
	// 있거나 못만든다.=false
	bool CheckRoom(int x, int y);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CStage* Clone();
	void SetRooms(int x, int y, class CRoom* room);
	CRoom* GetRooms(int x, int y);
	int GetRoomSize()
	{
		return m_RoomSize;
	}
};

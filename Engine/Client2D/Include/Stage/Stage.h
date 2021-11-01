#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"

class CStage
{
public:
	CStage();
	virtual ~CStage();
private:

	/*
	�߰��ɻ���
	��
	�̴ϸ�
	��UI

	*/
	Stage_State m_State;
	std::vector<CSharedPtr<CGameObject>> m_Enemy;
	std::vector<CDoor*> m_Doors;
	CStage* ConnectStage[Stage_Dir::END];
	bool m_Visit;  //�湮����üũ
	bool m_NextStage;
	std::vector<Vector2> m_PlayerSpawn;


	class CRoom* m_Rooms[20][20];
	int m_RoomSize;
public:
	//���� ���� true
	// �ְų� �������.=false
	bool CheckRoom(int x, int y);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CStage* Clone();
	void SetRooms(int x, int y, class CRoom* room);
	class CRoom* GetRooms(int x, int y);
	int GetRoomSize()
	{
		return m_RoomSize;
	}
};

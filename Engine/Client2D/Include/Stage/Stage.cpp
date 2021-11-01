
#include "Stage.h"
#include "Scene/Scene.h"
#include "../Room.h"

CStage::CStage() :
	m_RoomSize(0),
	m_Rooms{}
{
}

CStage::~CStage()
{
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (m_Rooms[i][j])
			{
				delete m_Rooms[i][j];
				m_Rooms[i][j] = nullptr;
			}
		}
	}
}
bool CStage::CheckRoom(int x, int y)
{
	if (x < 0 || x >= 20 || y < 0 || y >= 20)
	{
		return false;
	}
	if (m_Rooms[x][y])
	{
		return false;
	}

	return true;
}

void CStage::Start()
{
}

bool CStage::Init()
{
	CRoom* room = new CRoom();
	room->SetPos(4, 4);
	room->SetStage(this);
	SetRooms(4, 4, room);
	for (int i = 0; i < 4; ++i)
	{
		room->Start((RoomCreate_Dir)i);
	}
	return true;
}

void CStage::Update(float DeltaTime)
{
	switch (m_State)
	{
	case Stage_State::Idle:
	{
		if (m_Enemy.size() > 0)
		{
			m_State = Stage_State::Spawn;
			//적스폰
		}
		else
		{
			m_State = Stage_State::Clear;
		}
		break;
	}
	case Stage_State::Spawn:
	{
		//문닫기
		for (int i = 0; i < 4; i++)
		{
			if (m_Doors[i] != nullptr)
			{

			}
		}

		//스폰시작
		size_t Size = m_Enemy.size();
		for (size_t i = 0; i < Size; i++)
		{

		}

		if (m_Enemy.size() <= 0)
		{
			m_State = Stage_State::Clear;
			//보물상자 스폰시키기
		}


		break;
	}
	case Stage_State::Clear:
	{
		//문열기
		for (int i = 0; i < 4; i++)
		{
			if (m_Doors[i] != nullptr)
			{

			}
		}
		break;
	}
	}

}

void CStage::PostUpdate(float DeltaTime)
{
}

void CStage::Collision(float DeltaTime)
{
}

void CStage::Render(float DeltaTime)
{
}

CStage* CStage::Clone()
{
	return new CStage(*this);
}

void CStage::SetRooms(int x, int y, CRoom* room)
{
	if (m_Rooms[x][y])
	{

	}
	else
	{
		m_Rooms[x][y] = room;
		m_RoomSize++;
	}
}
CRoom* CStage::GetRooms(int x, int y)
{
	return m_Rooms[x][y];
}
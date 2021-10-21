
#include "Room.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"

CRoom::CRoom() :
	m_NextDoor(false),
	m_LeftRoom(nullptr),
	m_RightRoom(nullptr),
	m_UpRoom(nullptr),
	m_DownRoom(nullptr),
	m_Posx(-1),
	m_Posy(-1)
{
}

CRoom::CRoom(const CRoom& obj)
{
}

CRoom::~CRoom()
{
}



int CRoom::GetRoom_Dir()
{
	int num = 0;
	if (m_LeftRoom)
		num =(num <<1)| 1;
	if (m_RightRoom) 
		num = (num << 1) | 1;
	if (m_UpRoom) 
		num = (num << 1)| 1;
	if (m_DownRoom)
		num = (num << 1)| 1;
	return num;
}

void CRoom::Room_Dir(int num)
{
	bool left, right, up, down;
	left = right = up = down = false;

	down = (num & 0x0000000f);
	up = ((num >> 1) & 0x0000000f);
	right = ((num >> 2) & 0x0000000f);
	left = ((num >> 3) & 0x0000000f);

}

void CRoom::SetStage(CStage* Stage)
{
	m_Stage = Stage;
}

void CRoom::Start(RoomCreate_Dir RoomCreateDir)
{
	if (m_Stage->GetRoomSize() > 20)
	{
		return;
	}
	switch (RoomCreateDir)
	{
	case RoomCreate_Dir::Left:
		if (m_Stage->CheckRoom(m_Posx - 1, m_Posy))
		{
			CRoom* room = new CRoom;
			room->SetStage(m_Stage);
			m_Stage->SetRooms(m_Posx - 1, m_Posy, room);
			room->m_RightRoom = this;
			room->SetPos(m_Posx - 1, m_Posy); 
			room->Init(RoomCreate_Dir::Right);
			m_LeftRoom = room;
		}
		break;
	case RoomCreate_Dir::Right:
		if (m_Stage->CheckRoom(m_Posx + 1, m_Posy))
		{
			CRoom* room = new CRoom;
			room->SetStage(m_Stage);
			room->m_LeftRoom = this;
			m_Stage->SetRooms(m_Posx+1, m_Posy , room);
			room->SetPos(m_Posx + 1, m_Posy);
			room->Init(RoomCreate_Dir::Left);
			m_RightRoom = room;
		}
		break;
	case RoomCreate_Dir::Up:
		if (m_Stage->CheckRoom(m_Posx , m_Posy+1))
		{
			CRoom* room = new CRoom;
			room->SetStage(m_Stage);
			room->m_DownRoom = this;
			m_Stage->SetRooms(m_Posx, m_Posy + 1, room);
			room->SetPos(m_Posx , m_Posy+1);
			room->Init(RoomCreate_Dir::Down);
			room = m_UpRoom;
		}
		break;
	case RoomCreate_Dir::Down:
		if (m_Stage->CheckRoom(m_Posx , m_Posy-1))
		{
			CRoom* room = new CRoom;
			room->SetStage(m_Stage);
			room->m_UpRoom = this;
			m_Stage->SetRooms(m_Posx, m_Posy - 1, room);
			room->SetPos(m_Posx , m_Posy-1);
			room->Init(RoomCreate_Dir::Up);
			m_DownRoom = room;
		}
		break;
	default:
		break;
	}
}

bool CRoom::Init(RoomCreate_Dir PrevDir)
{
	RoomCreate_Dir Dir;
	for (;;)
	{
		Dir = (RoomCreate_Dir)CGlobalValue::GetRandom((int)RoomCreate_Dir::End);
		if (Dir != PrevDir)
			break;
	}
	Start(Dir);
	return true;
}

void CRoom::Update(float DeltaTime)
{
}

void CRoom::PostUpdate(float DeltaTime)
{
}

void CRoom::Collision(float DeltaTime)
{
}

void CRoom::Render(float DeltaTime)
{
}

CRoom* CRoom::Clone()
{
	return new CRoom(*this);
}
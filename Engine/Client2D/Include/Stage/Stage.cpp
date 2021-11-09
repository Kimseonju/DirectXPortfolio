
#include "Stage.h"
#include "Scene/Scene.h"
#include "../Room.h"
#include "../MainDoor.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
CStage::CStage() :
	m_Enable(true),
	m_State(Stage_State::Idle)
{
}

CStage::~CStage()
{
}
void CStage::Enable(bool Enable)
{
	m_Enable = Enable;
	m_TileMap->Enable(m_Enable);
	m_TileMapObject->Enable(m_Enable);
}
void CStage::ObjectUpdate(StageObjectsInfo Info, StageType Type)
{
	if (m_State != Stage_State::Idle)
	{
		return;
	}
	m_TileMap =Info.TileMap;
	m_TileMapObject = Info.TileMapObject;
	size_t Size=Info.StageSpawn.size();
	for (size_t i = 0; i < Size; i++)
	{
		CGameObject* Obj = nullptr;
		switch (Info.StageSpawn[i].ClassType)
		{
		case Client_Class_Type::Default: //
		{
			break;
		}
		case Client_Class_Type::Object: //�������´�
		{
			switch (Info.StageSpawn[i].ObjectType)
			{
			case Client_Object_Type::MainDoor: //1���� ������ġ
				//�÷��̾ ������ �������ʾ����� ������ MainDoor���� ����� ������ġ�� ����
			{
				CMainDoor* MainDoor=m_pScene->SpawnObject<CMainDoor>("MainDoor");
				if (Type == StageType::Start)
				{
					MainDoor->StartDoor();
				}
				else if (Type == StageType::End)
				{
					MainDoor->EndDoor();
				}
				m_Object.push_back(MainDoor);
				Obj = MainDoor;
				break;
			}
			case Client_Object_Type::House:
			{
				break;
			}
			case Client_Object_Type::Door:
			{

				CDoor* Door = m_pScene->SpawnObject<CDoor>("MainDoor");
				m_Doors.push_back(Door);
				Door->SetDoorDir(Info.StageSpawn[i].DoorDir);
				Obj = Door;

				break;
			}
			}
			break;
		}
		case Client_Class_Type::Enemy:
		{
			CGameObject* Obj = nullptr;
			break;
		}

		case Client_Class_Type::Boss:
		{
			break;
		}
		}
		if (Obj)
		{
			Obj->SetWorldPos(Info.StageSpawn[i].Pos);
			Obj->SetWorldRotation(Info.StageSpawn[i].Rot);
			Obj->SetWorldScale(Info.StageSpawn[i].Scale);
			Obj->SetPivot(Info.StageSpawn[i].Pivot);
		}
		

	}

}
void CStage::Start()
{
}

bool CStage::Init()
{

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
			//������
		}
		else
		{
			m_State = Stage_State::Clear;
		}
		break;
	}
	case Stage_State::Spawn:
	{
		//���ݱ�
		for (int i = 0; i < 4; i++)
		{
			if (m_Doors[i] != nullptr)
			{

			}
		}

		//��������
		size_t Size = m_Enemy.size();
		for (size_t i = 0; i < Size; i++)
		{

		}

		if (m_Enemy.size() <= 0)
		{
			m_State = Stage_State::Clear;
			//�������� ������Ű��
		}


		break;
	}
	case Stage_State::Clear:
	{
		//������
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

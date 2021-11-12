
#include "Stage.h"
#include "Scene/Scene.h"
#include "../Object/MainDoor.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Component/TileMapComponent.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../Object/CreateObject.h"
#include "../Object/SmallSkel.h"
CStage::CStage() :
	m_Enable(true),
	m_State(Stage_State::Idle),
	m_DoorDir(-1),
	m_EnemyOrder(1)
{
}

CStage::~CStage()
{

	m_vecEnemy.clear();
	auto iter = m_SpawnEnemy.begin();
	auto iterEnd = m_SpawnEnemy.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter).second.clear();
	}
}
void CStage::Enable(bool Enable)
{
	m_Enable = Enable;
	m_TileMapComponent->Enable(m_Enable);
	m_TileObjectMapComponent->Enable(m_Enable);

	for (size_t i = 0; i < m_vecEnemy.size(); ++i)
	{
		m_vecEnemy[i]->Enable(m_Enable);
	}
	for (size_t i = 0; i < m_Object.size(); ++i)
	{
		m_Object[i]->Enable(m_Enable);
	}
	for (size_t i = 0; i < m_Doors.size(); ++i)
	{
		m_Doors[i]->Enable(m_Enable);
	}
}
void CStage::ObjectUpdate(StageObjectsInfo Info, StageType Type, int num)
{
	if (m_State != Stage_State::Idle)
	{
		return;
	}
	m_Name = Info.Name;
	m_DoorDir = num;
	m_TileMap =Info.TileMap;
	m_TileMapObject = Info.TileMapObject;
	m_TileMapComponent = Info.TileMapComponent;
	m_TileObjectMapComponent = Info.TileObjectMapComponent;
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
		case Client_Class_Type::Object: //만들어놓는다
		{
			switch (Info.StageSpawn[i].ObjectType)
			{
			case Client_Object_Type::MainDoor: //1순위 스폰위치
				//플레이어가 문으로 열고가지않았으면 무조건 MainDoor에서 잡아준 스폰위치로 간다
			{
				CMainDoor* MainDoor=m_pScene->SpawnObject<CMainDoor>("MainDoor");
				if (Type == StageType::Start)
				{
					MainDoor->StartDoor();
					CGlobalValue::MainPlayer->SetWorldPos(Info.StageSpawn[i].Pos);
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

				CDoor* Door = m_pScene->SpawnObject<CDoor>("MainDoor2");
				m_Doors.push_back(Door);
				Door->SetDoorDir(Info.StageSpawn[i].DoorDir);
				Door->SetDir(Info.StageSpawn[i].DoorDir);
				Obj = Door;

				break;
			}
			}
			break;
		}
		case Client_Class_Type::Enemy:
		{
			std::string str = std::to_string(i);
			if (Info.StageSpawn[i].CreateEnemyOrder == 0)
			{
				switch (Info.StageSpawn[i].EnemyType)
				{
				case Client_Enemy_Type::SmallSkel_Sword:
					Obj = m_pScene->SpawnObject<CSmallSkel>("CreateObject"+ str);
					Obj->SetStartTimer(1.f);
					m_vecEnemy.push_back(Obj);
					break;
				case Client_Enemy_Type::SmallSkel_Bow:
					break;
				case Client_Enemy_Type::End:
					break;
				default:
					break;
				}
			}
			else
			{
				Obj = m_pScene->SpawnObject<CCreateObject>("CreateObject"+ str);
				Obj->SetCreateEnemyEffect(Info.StageSpawn[i].CreateEnemyEffect);
				Obj->SetCreateEnemyOrder(Info.StageSpawn[i].CreateEnemyOrder);
				Obj->SetEnemyType(Info.StageSpawn[i].EnemyType);
				PushSpawnEnemy(Obj);
			}
			Obj->Enable(false);
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
		if (m_vecEnemy.size() > 0)
		{
			//스폰시작
			size_t Size = m_vecEnemy.size();
			for (size_t i = 0; i < Size; i++)
			{
				m_vecEnemy[i]->Enable(true);
			}
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
		size_t Size=m_Doors.size();
		for (size_t i = 0; i < Size; i++)
		{
			m_Doors[i]->DoorOpenClose(false);
		}

		auto iter = m_vecEnemy.begin();
		auto iterEnd = m_vecEnemy.end();

		for (; iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				iter=m_vecEnemy.erase(iter);
				iterEnd = m_vecEnemy.end();
				continue;
			}
			++iter;
		}
		

		if (m_vecEnemy.size() <= 0)
		{
			m_State = Stage_State::Clear;
			//보물상자 스폰시키기
		}


		break;
	}
	case Stage_State::Clear:
	{
		//문열기
		size_t Size = m_Doors.size();
		for (size_t i = 0; i < Size; i++)
		{
			m_Doors[i]->DoorOpenClose(false);
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

void CStage::PlayerStageMove(Stage_Dir Dir)
{
	//같은방향으로
	if (Dir == Stage_Dir::END)
		return;
	int iDir=((int)Dir + 2) % 4;
	for (int i = 0; i < m_Doors.size(); ++i)
	{
		Door_Dir DoorDir=m_Doors[i]->GetDoorDir();
		if (iDir == (int)DoorDir)
		{
			m_Doors[i]->PlayerMove();
		}
	}

}

void CStage::PushSpawnEnemy(CGameObject* Obj)
{
	auto iter= m_SpawnEnemy.find(Obj->GetCreateEnemyOrder());

	if (iter == m_SpawnEnemy.end())
	{
		std::vector<CSharedPtr<CGameObject>> vecCreateEnemy;
		m_SpawnEnemy.insert(std::make_pair(Obj->GetCreateEnemyOrder(), vecCreateEnemy));
		iter = m_SpawnEnemy.find(Obj->GetCreateEnemyOrder());
	}
	iter->second.push_back(Obj);
}

#include "StageManager.h"
#include "../GlobalValue.h"
#include <PathManager.h>
#include <Component/TileMapComponent.h>
#include "../Object/Player.h"
#include <Resource/ResourceManager.h>
#include <Scene/SceneResource.h>
CStageManager::CStageManager() :
	m_pScene(nullptr),
	m_MapSize(4),
	m_MapCount(0),
	m_BossStage(false),
	m_SelectStage(nullptr),
	m_BGMSound(),
	m_StartEndCount(0)
{
}
CStageManager::~CStageManager()
{
	for (size_t i = 0; i < m_vecStage.size(); i++)
	{
		for (size_t j = 0; j < m_vecStage[i].size(); ++j)
		{
			SAFE_DELETE(m_vecStage[i][j]);
		}
	}
}

std::string CStageManager::GetCurName()
{
	return m_SelectStage->GetName();
}

CStage* CStageManager::GetCurStage()
{
	return m_SelectStage;
}

void CStageManager::Init()
{
	CreateDungeon();

	m_CurPos = m_StartPos;
	
	CSound* Sound = m_pScene->GetResource()->FindSound("Town");
	m_BGMSound[(int)StageType::None] = Sound;
	Sound = m_pScene->GetResource()->FindSound("Fleld");
	m_BGMSound[(int)StageType::Base] = Sound;
	m_BGMSound[(int)StageType::Start] = Sound;
	m_BGMSound[(int)StageType::Start] = Sound;
	m_BGMSound[(int)StageType::End] = Sound;

	Sound = m_pScene->GetResource()->FindSound("Shop");
	m_BGMSound[(int)StageType::Shop] = Sound;

	Sound = m_pScene->GetResource()->FindSound("Boss");
	m_BGMSound[(int)StageType::Boss] = Sound;


	Sound = m_pScene->GetResource()->FindSound("Foodshop");
	m_BGMSound[(int)StageType::Restaurant] = Sound;
}

void CStageManager::Start()
{
	PlayStage(Stage_Dir::END);
}

void CStageManager::Update(float DeltaTime)
{
	if (m_SelectStage)
	{
		m_SelectStage->Update(DeltaTime);
		//배경음 관리
	}

}

void CStageManager::CreateBossStage()
{
	m_SelectStage->Enable(false);
	m_SelectStage = nullptr;
	m_BossStage = true;
	m_StartPos = Vector2(0.f, 0.f);
	m_EndPos = Vector2(0.f, 2.f);
	m_CurPos = m_StartPos;
	for (size_t i = 0; i < m_vecStage.size(); i++)
	{
		for (size_t j = 0; j < m_vecStage[i].size(); ++j)
		{
			SAFE_DELETE(m_vecStage[i][j]);
		}
		m_vecStage[i].clear();
	}
	m_vecStage.clear();

	for (size_t i = 0; i < m_vecStageInfo.size(); i++)
	{
		m_vecStageInfo[i].clear();
	}
	m_vecStageInfo.clear();



	m_vecStage.resize(3);

	m_vecStage[0].resize(3);
	m_vecStage[1].resize(3);
	m_vecStage[2].resize(3);

	m_vecStageInfo.resize(3);

	m_vecStageInfo[0].resize(3);
	m_vecStageInfo[1].resize(3);
	m_vecStageInfo[2].resize(3);

	for (int x = 0; x < 3; x++)
	{
		for (int dir = 0; dir < 4; dir++)
		{
			m_vecStageInfo[x][0].Wall[dir] = true;
		}
		m_vecStageInfo[x][0].visit = false;
		m_vecStageInfo[x][0].StageType = StageType::Base;
	}
	m_vecStageInfo[0][0].Wall[(int)Door_Dir::Door_Right] = false;
	m_vecStageInfo[1][0].Wall[(int)Door_Dir::Door_Left] = false;
	m_vecStageInfo[1][0].Wall[(int)Door_Dir::Door_Right] = false;
	m_vecStageInfo[2][0].Wall[(int)Door_Dir::Door_Left] = false;

	m_vecStageInfo[0][0].StageType= StageType::Start;

	m_vecStageInfo[1][0].StageType = StageType::Boss;

	m_vecStageInfo[2][0].StageType = StageType::End;

	PlayStage(Stage_Dir::END);
}

void CStageManager::CreateDungeon()
{
	m_vecStageInfo.resize(m_MapSize);
	for (int i = 0; i < m_MapSize; i++)
		m_vecStageInfo[i].resize(m_MapSize);
	m_vecStage.resize(m_MapSize);
	for (int i = 0; i < m_MapSize; i++)
		m_vecStage[i].resize(m_MapSize);
	while (true)
	{
		for (int x = 0; x < m_MapSize; x++)
		{
			for (int y = 0; y < m_MapSize; y++)
			{
				for (int dir = 0; dir < 4; dir++)
				{
					m_vecStageInfo[x][y].Wall[dir] = true;
				}
				m_vecStageInfo[x][y].visit = false;
				m_vecStageInfo[x][y].StageType = StageType::Base;
			}
		}
		int startX = GetRandom(0,m_MapSize - 1);
		int startY = GetRandom(0,m_MapSize - 1);
		CreateStage(startX, startY);

		if (CreateStage_Special()) 
		{
			break;
		}
	}
}

void CStageManager::CreateStage(int x, int y)
{
	if (m_vecStageInfo[x][y].visit) 
		return;

	m_vecStageInfo[x][y].visit = true;

	int dir_x[4] = { -1,0,1,0 };
	int dir_y[4] = { 0,1,0,-1 };
	//왼쪽부터 시계방향
	bool checkDir[4] = { false, false, false, false };
	while (true)
	{
		if (checkDir[0] && checkDir[1] && checkDir[2] && checkDir[3]) break;

		int Dir = GetRandom(0, 4-1);
		if (checkDir[Dir]) continue;
		checkDir[Dir] = true;

		int nextX = x + dir_x[Dir];
		int nextY = y + dir_y[Dir];

		if (nextX < 0 || nextX >= m_MapSize || nextY < 0 || nextY >= m_MapSize)
			continue;

		if (m_vecStageInfo[nextX][nextY].visit)
			continue;
		
		//연결
		m_vecStageInfo[x][y].Wall[Dir] = false;
		m_vecStageInfo[nextX][nextY].Wall[(Dir + 2) % 4] = false;
		CreateStage(nextX, nextY);
	}
}

void CStageManager::NextStage(Stage_Dir Dir)
{
	switch (Dir)
	{
	case LEFT:
		m_CurPos.x -= 1.f;
		break;
	case UP:
		m_CurPos.y += 1.f;
		break;
	case RIGHT:
		m_CurPos.x += 1.f;
		break;
	case DOWN:
		m_CurPos.y -= 1.f;
		break;
	}

	PlayStage(Dir);
}

void CStageManager::GateStage(Vector2 Pos)
{
	m_CurPos = Pos;
	PlayGateStage();
}

void CStageManager::PlayStage(Stage_Dir Dir)
{
	if (m_SelectStage)
	{
		m_SelectStage->Enable(false);
	}
	int x = (int)m_CurPos.x;
	int y = (int)m_CurPos.y;
	if (m_vecStage[x][y])
	{
		//만약있는방이면 이미 방문했던방이다.
		m_SelectStage = m_vecStage[x][y];
		m_SelectStage->PlayerStageMove(Dir);
		m_SelectStage->Enable(true);
		BGMSoundUpdate(m_vecStage[x][y]->GetStageType());
		return;
	}
	//첫방문
	CStage* Stage = new CStage;
	//벽이없다면 문이있다는 뜻
	int num = 0;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Left])
		num = num | 1;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Up])
		num = num | 2;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Right])
		num = num | 4;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Down])
		num = num | 8;
	StageObjectsInfo Info;
	switch (m_vecStageInfo[x][y].StageType)
	{
	case StageType::None:
		break;
	case StageType::Base:
		Info = GetStageSpawnInfo(num);
		break;
#pragma region GetStage...
	case StageType::Start:
		Info = GetMainDoorStageSpawnInfo(num);
		break;
	case StageType::End:
		Info = GetMainDoorStageSpawnInfo(num);
		break;
	case StageType::Shop:
		Info = GetShopStageSpawnInfo(num);
		break;
	case StageType::Restaurant:
		Info = GetRestaurantStageSpawnInfo(num);
		break;
	case StageType::Boss:
		Info = GetBossStageSpawnInfo(num);
		break;
#pragma endregion
	}

	Stage->SetScene(m_pScene);
	Stage->ObjectUpdate(Info, m_vecStageInfo[x][y].StageType, num);
	Stage->PlayerStageMove(Dir);
	m_vecStage[x][y] = Stage;
	Stage->Enable(true);
	m_SelectStage = Stage;
	BGMSoundUpdate(m_vecStage[x][y]->GetStageType());
}

void CStageManager::PlayGateStage()
{
	if (m_SelectStage)
	{
		m_SelectStage->Enable(false);
	}
	int x = (int)m_CurPos.x;
	int y = (int)m_CurPos.y;
	if (m_vecStage[x][y])
	{
		//만약있는방이면 이미 방문했던방이다.
		m_SelectStage = m_vecStage[x][y];
		m_SelectStage->PlayerStageGate();
		m_SelectStage->Enable(true);
		BGMSoundUpdate(m_vecStage[x][y]->GetStageType());
		return;
	}


	//첫방문
	CStage* Stage = new CStage;
	//벽이없다면 문이있다는 뜻
	int num = 0;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Left])
		num = num | 1;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Up])
		num = num | 2;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Right])
		num = num | 4;
	if (!m_vecStageInfo[x][y].Wall[(int)Door_Dir::Door_Down])
		num = num | 8;
	StageObjectsInfo Info;

	//나중에 만들면 수정
	switch (m_vecStageInfo[x][y].StageType)
	{
	case StageType::None:
		break;
	case StageType::Base:
		Info = GetStageSpawnInfo(num);
		break;
	case StageType::Start:
		Info = GetMainDoorStageSpawnInfo(num);
		break;
	case StageType::End:
		Info = GetMainDoorStageSpawnInfo(num);
		break;
	case StageType::Shop:
		Info = GetShopStageSpawnInfo(num);
		break;
	case StageType::Restaurant:
		Info = GetRestaurantStageSpawnInfo(num);
		break;

	case StageType::Boss:
		Info = GetBossStageSpawnInfo(num);
		break;
	}

	Stage->SetScene(m_pScene);
	Stage->ObjectUpdate(Info, m_vecStageInfo[x][y].StageType, num);
	//Stage->PlayerStageMove(Dir);
	m_vecStage[x][y] = Stage;
	Stage->Enable(true);
	m_SelectStage = Stage;
	BGMSoundUpdate(m_vecStage[x][y]->GetStageType());
	
	
}

bool CStageManager::CreateStage_Special()
{
	std::vector<Vector2> vecStagePos;
#pragma region StartStage
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && 
				m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && 
				m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	int RandomNum = GetRandom(0, (int)vecStagePos.size() - 1);
	m_StartPos = vecStagePos[RandomNum];
	m_vecStageInfo[(int)m_StartPos.x][(int)m_StartPos.y].StageType = StageType::Start;
	vecStagePos.clear();
#pragma endregion	
#pragma region EndStage
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			if (m_StartPos.x == x && m_StartPos.y == y)
				continue;
			if (!m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	RandomNum = GetRandom(0, (int)vecStagePos.size() - 1);
	m_EndPos = vecStagePos[RandomNum];
	m_vecStageInfo[(int)m_EndPos.x][(int)m_EndPos.y].StageType = StageType::End;
	vecStagePos.clear();
#pragma endregion

#pragma region ShopStage
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			if (m_StartPos.x == x && m_StartPos.y == y)
				continue;
			if (m_EndPos.x == x && m_EndPos.y == y)
				continue;
			if (!m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	RandomNum = GetRandom(0, (int)vecStagePos.size() - 1);
	m_ShopPos = vecStagePos[RandomNum];
	m_vecStageInfo[(int)m_ShopPos.x][(int)m_ShopPos.y].StageType = StageType::Shop;
	vecStagePos.clear();
#pragma endregion
#pragma region RestaurantStage
	for (int x = 0; x < m_MapSize; ++x)
	{
		for (int y = 0; y < m_MapSize; ++y)
		{
			if (m_StartPos.x == x && m_StartPos.y == y)
				continue;
			if (m_EndPos.x == x && m_EndPos.y == y)
				continue;
			if (m_ShopPos.x == x && m_ShopPos.y == y)
				continue;
			if (!m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				!m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	if (vecStagePos.size() == 0)
		return false;
	RandomNum = GetRandom(0, (int)vecStagePos.size() - 1);
	m_ShopPos = vecStagePos[RandomNum];
	m_vecStageInfo[(int)m_ShopPos.x][(int)m_ShopPos.y].StageType = StageType::Restaurant;
	vecStagePos.clear();
#pragma endregion
#pragma region StageCheck

	for (int x = 0; x < m_MapSize; x++)
	{
		for (int y = 0; y < m_MapSize; y++)
		{
			if (m_StartPos.x == x && m_StartPos.y == y)
				continue;
			if (m_EndPos.x == x && m_EndPos.y == y)
				continue;
			if (m_ShopPos.x == x && m_ShopPos.y == y)
				continue;
			if (m_RestaurantPos.x == x && m_RestaurantPos.y == y)
				continue;

			if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && !m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}

			else if (m_vecStageInfo[x][y].Wall[(int)WallDir::Left] && m_vecStageInfo[x][y].Wall[(int)WallDir::Up] &&
				m_vecStageInfo[x][y].Wall[(int)WallDir::Right] && !m_vecStageInfo[x][y].Wall[(int)WallDir::Down])
			{
				vecStagePos.push_back(Vector2{ (float)x,(float)y });
			}
		}
	}
	int dir_x[4] = { -1,0,1,0 };
	int dir_y[4] = { 0,1,0,-1 };

	for (int i = 0; i < vecStagePos.size(); i++)
	{
		m_vecStageInfo[(int)vecStagePos[i].x][(int)vecStagePos[i].y].StageType = StageType::None;
		for (int dir = 0; dir < 4; dir++)
		{
			if (!m_vecStageInfo[(int)vecStagePos[i].x][(int)vecStagePos[i].y].Wall[dir])
			{
				int nextX = (int)vecStagePos[i].x + dir_x[dir];
				int nextY = (int)vecStagePos[i].y + dir_y[dir];
				m_vecStageInfo[nextX][nextY].Wall[(dir + 2) % 4] = true;
			}
		}
	}
#pragma endregion

	return true;
}

void CStageManager::ReleaseStage()
{


}


void CStageManager::LoadStage(FILE* pFile, const char* Name)
{
	size_t Size = 0;
	fread(&Size, sizeof(size_t), 1, pFile);

	Client_Class_Type  ClassType;
	Client_Object_Type ObjectType;
	Client_Enemy_Type EnemyType;
	bool			  CreateEnemyEffect = false;
	int				  CreateEnemyOrder=0;
	Door_Dir          DoorDir;
	StageObjectsInfo _StageObjectsInfo;
	std::vector< StageObjectSpawnInfo> vecSpawn;
	_StageObjectsInfo.Name = Name;
	//이 스테이지의 문의 방향을 확인한다. 문이없으면 0 있으면 1
	bool bDoorDir[4] = { 0 };
	//Client_Object_Type에서 MainDoor가 있는지 없는지 확인한다 따로분류요함
	bool bMainDoor = false;
	bool bBoss = false;
	bool bShop = false;
	bool bRestaurant = false;

	for (size_t i = 0; i < Size; ++i)
	{
		StageObjectSpawnInfo Spawn;
		fread(&ClassType, sizeof(Client_Class_Type), 1, pFile);
		fread(&ObjectType, sizeof(Client_Object_Type), 1, pFile);
		fread(&EnemyType, sizeof(Client_Enemy_Type), 1, pFile);
		fread(&DoorDir, sizeof(Door_Dir), 1, pFile);

		if (ClassType == Client_Class_Type::Enemy)
		{
			int EnemyEffect = 0;
			fread(&EnemyEffect, sizeof(int), 1, pFile);
			fread(&CreateEnemyOrder, sizeof(int), 1, pFile);
			if (EnemyEffect == 1)
				CreateEnemyEffect = true;
		}
		Vector3	Pos, Rot, Scale, Pivot;

		fread(&Pos, sizeof(Vector3), 1, pFile);
		fread(&Rot, sizeof(Vector3), 1, pFile);
		fread(&Scale, sizeof(Vector3), 1, pFile);
		fread(&Pivot, sizeof(Vector3), 1, pFile);
		Spawn.ClassType = ClassType;
		Spawn.ObjectType = ObjectType;
		Spawn.EnemyType = EnemyType;
		Spawn.DoorDir = DoorDir;
		Spawn.Pos = Pos;
		Spawn.Rot = Rot;
		Spawn.Scale = Scale;
		Spawn.Pivot = Pivot;
		Spawn.CreateEnemyEffect = CreateEnemyEffect;
		Spawn.CreateEnemyOrder = CreateEnemyOrder;
		switch (ClassType)
		{
		case Client_Class_Type::Default: //
		{
			break;
		}
		case Client_Class_Type::Object: //만들어놓는다
		{
			switch (ObjectType)
			{
			case Client_Object_Type::MainDoor: //1순위 스폰위치
				//플레이어가 문으로 열고가지않았으면 무조건 MainDoor에서 잡아준 스폰위치로 간다
			{
				bMainDoor = true;
				break;
			}
			case Client_Object_Type::House:
			{
				break;
			}
			case Client_Object_Type::Door:
			{
				//이자리는 문이있는자리
				bDoorDir[(int)DoorDir] = 1;
				//문위치가정해지면 자동으로 스폰위치도 정해진다
				break;
			}

			case Client_Object_Type::Shop:
			{
				bShop = true;
				break;
			}
			case Client_Object_Type::Restaurant:
			{
				bRestaurant = true;
				break;
			}
			}
			break;
		}
		case Client_Class_Type::Boss:
		{
			bBoss = true;
			break;
		}
		}
		vecSpawn.push_back(Spawn);
	}
	_StageObjectsInfo.StageSpawn = vecSpawn;
	_StageObjectsInfo.UseCount = 0;


	int num = 0;
	if (bDoorDir[(int)Door_Dir::Door_Left])
		num = num | 1;
	if (bDoorDir[(int)Door_Dir::Door_Up])
		num = num | 2;
	if (bDoorDir[(int)Door_Dir::Door_Right])
		num = num | 4;
	if (bDoorDir[(int)Door_Dir::Door_Down])
		num = num | 8;


	//맵 로딩

	m_MapCount++;
	std::string str = std::to_string(m_MapCount);
	CGameObject* TileMap = m_pScene->SpawnObject<CGameObject>("TileMap"+str);
	CTileMapComponent* TileMapComponent = TileMap->CreateSceneComponent<CTileMapComponent>("TileMap");
	TileMap->SetRootComponent(TileMapComponent);
	CGameObject* TileMapObject = m_pScene->SpawnObject<CGameObject>("TileMapObject" + str);
	CTileMapComponent* TileObjectMapComponent = TileMap->CreateSceneComponent<CTileMapComponent>("TileMap");
	TileMapObject->SetRootComponent(TileObjectMapComponent);
	TileMapComponent->ClientLoad(pFile);
	TileObjectMapComponent->ClientLoad(pFile);
	//TileMap->Enable(false);
	//TileMapObject->Enable(false);
	TileMapComponent->Enable(false);
	TileMapComponent->SetEditorMode(false);
	TileObjectMapComponent->Enable(false);
	TileObjectMapComponent->SetEditorMode(false);
	_StageObjectsInfo.TileMap=TileMap;
	_StageObjectsInfo.TileMapObject = TileMapObject;
	_StageObjectsInfo.TileMapComponent = TileMapComponent;
	_StageObjectsInfo.TileObjectMapComponent = TileObjectMapComponent;
	TileMapComponent->SetCollisionTileProfile("Tile_pass", "Tile_Nopass");
	TileObjectMapComponent->SetCollisionTileProfile("Tile_pass", "Tile_Nopass");
	if (bMainDoor)
	{

		PushMainDoorStageSpawnInfo(num, _StageObjectsInfo);
	}
	else if(bBoss)
	{

		PushBossStageSpawnInfo(num, _StageObjectsInfo);
	}
	else if (bShop)
	{
		PushShopStageSpawnInfo(num, _StageObjectsInfo);
	}
	else if (bRestaurant)
	{
		PushRestaurantStageSpawnInfo(num, _StageObjectsInfo);
	}
	else
	{
		PushStageSpawnInfo(num, _StageObjectsInfo);
	}
}

void CStageManager::AllLoadStage(const TCHAR* FileName)
{
	const PathInfo* Info = CPathManager::GetInst()->FindPath(MAP_PATH);

	TCHAR	FullPath[MAX_PATH] = {};
	TCHAR	Name[MAX_PATH] = {};

	if (Info)
		lstrcpy(FullPath, Info->pPath);

	lstrcat(FullPath, FileName);
	lstrcat(Name, FileName);

	char	FullPathMultibyte[MAX_PATH] = {};
	char	NameMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

	ConvertLength = WideCharToMultiByte(CP_ACP, 0, Name, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, Name, -1, NameMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "rb");

	if (!pFile)
		return;

	LoadStage(pFile, NameMultibyte);

	fclose(pFile);
}

void CStageManager::PushMainDoorStageSpawnInfo(int Door, StageObjectsInfo Info)
{
	auto	iter = m_vecMainDoorStageSpawnInfo.find(Door);

	if (iter == m_vecMainDoorStageSpawnInfo.end())
	{
		std::vector<StageObjectsInfo> vecStageSpawnInfo;
		m_vecMainDoorStageSpawnInfo.insert(std::make_pair(Door, vecStageSpawnInfo));
		iter = m_vecMainDoorStageSpawnInfo.find(Door);
	}
	iter->second.push_back(Info);
}

void CStageManager::PushStageSpawnInfo(int Door, StageObjectsInfo Info)
{
	auto	iter = m_vecStageSpawnInfo.find(Door);

	if (iter == m_vecStageSpawnInfo.end())
	{
		std::vector<StageObjectsInfo> vecStageSpawnInfo;
		m_vecStageSpawnInfo.insert(std::make_pair(Door, vecStageSpawnInfo));
		iter = m_vecStageSpawnInfo.find(Door);
	}
	iter->second.push_back(Info);
}

void CStageManager::PushBossStageSpawnInfo(int Door, StageObjectsInfo Info)
{
	auto	iter = m_vecBossStageSpawnInfo.find(Door);

	if (iter == m_vecBossStageSpawnInfo.end())
	{
		std::vector<StageObjectsInfo> vecStageSpawnInfo;
		m_vecBossStageSpawnInfo.insert(std::make_pair(Door, vecStageSpawnInfo));
		iter = m_vecBossStageSpawnInfo.find(Door);
	}
	iter->second.push_back(Info);
}

void CStageManager::PushShopStageSpawnInfo(int Door, StageObjectsInfo Info)
{
	auto	iter = m_vecShopStageSpawnInfo.find(Door);

	if (iter == m_vecShopStageSpawnInfo.end())
	{
		std::vector<StageObjectsInfo> vecStageSpawnInfo;
		m_vecShopStageSpawnInfo.insert(std::make_pair(Door, vecStageSpawnInfo));
		iter = m_vecShopStageSpawnInfo.find(Door);
	}
	iter->second.push_back(Info);
}

void CStageManager::PushRestaurantStageSpawnInfo(int Door, StageObjectsInfo Info)
{
	auto	iter = m_vecRestaurantStageSpawnInfo.find(Door);

	if (iter == m_vecRestaurantStageSpawnInfo.end())
	{
		std::vector<StageObjectsInfo> vecStageSpawnInfo;
		m_vecRestaurantStageSpawnInfo.insert(std::make_pair(Door, vecStageSpawnInfo));
		iter = m_vecRestaurantStageSpawnInfo.find(Door);
	}
	iter->second.push_back(Info);
}

StageObjectsInfo CStageManager::GetMainDoorStageSpawnInfo(int Door)
{
	auto	iter = m_vecMainDoorStageSpawnInfo.find(Door);
	StageObjectsInfo Temp;
	if (iter == m_vecMainDoorStageSpawnInfo.end())
	{
		return Temp;
	}
	std::vector<StageObjectsInfo>& Info = iter->second;

	int SelectCount = 0;
	int UseCount = Info[0].UseCount;

	//쓰고난 다음번째 선택
	for (size_t i = 1; i < Info.size(); i++)
	{
		if (UseCount > Info[i].UseCount)
		{
			SelectCount = (int)i;
			UseCount = Info[i].UseCount;
		}
	}

	Info[SelectCount].UseCount++;;

	return Info[SelectCount];
}

StageObjectsInfo CStageManager::GetStageSpawnInfo(int Door)
{
	auto	iter = m_vecStageSpawnInfo.find(Door);

	StageObjectsInfo Temp;
	if (iter == m_vecStageSpawnInfo.end())
	{
		return Temp;
	}
	std::vector<StageObjectsInfo> Info = iter->second;

	int SelectCount = 0;
	int UseCount = Info[0].UseCount;
	
	//쓰고난 다음번째 선택
	for (size_t i = 1; i < Info.size(); i++)
	{
		if (UseCount > Info[i].UseCount)
		{
			SelectCount = (int)i;
			UseCount = Info[i].UseCount;
		}
	}
	
	Info[SelectCount].UseCount++;;

	return Info[SelectCount];
}

StageObjectsInfo CStageManager::GetBossStageSpawnInfo(int Door)
{
	auto	iter = m_vecBossStageSpawnInfo.find(Door);

	StageObjectsInfo Temp;
	if (iter == m_vecBossStageSpawnInfo.end())
	{
		return Temp;
	}
	std::vector<StageObjectsInfo> Info = iter->second;

	int SelectCount = 0;
	int UseCount = Info[0].UseCount;

	//쓰고난 다음번째 선택
	for (size_t i = 1; i < Info.size(); i++)
	{
		if (UseCount > Info[i].UseCount)
		{
			SelectCount = (int)i;
			UseCount = Info[i].UseCount;
		}
	}

	Info[SelectCount].UseCount++;;

	return Info[SelectCount];
}

StageObjectsInfo CStageManager::GetShopStageSpawnInfo(int Door)
{
	auto	iter = m_vecShopStageSpawnInfo.find(Door);

	StageObjectsInfo Temp;
	if (iter == m_vecShopStageSpawnInfo.end())
	{
		return Temp;
	}
	std::vector<StageObjectsInfo> Info = iter->second;

	int SelectCount = 0;
	int UseCount = Info[0].UseCount;

	//쓰고난 다음번째 선택
	for (size_t i = 1; i < Info.size(); i++)
	{
		if (UseCount > Info[i].UseCount)
		{
			SelectCount = (int)i;
			UseCount = Info[i].UseCount;
		}
	}

	Info[SelectCount].UseCount++;;

	return Info[SelectCount];
}

StageObjectsInfo CStageManager::GetRestaurantStageSpawnInfo(int Door)
{
	auto	iter = m_vecRestaurantStageSpawnInfo.find(Door);

	StageObjectsInfo Temp;
	if (iter == m_vecRestaurantStageSpawnInfo.end())
	{
		return Temp;
	}
	std::vector<StageObjectsInfo> Info = iter->second;

	int SelectCount = 0;
	int UseCount = Info[0].UseCount;

	//쓰고난 다음번째 선택
	for (size_t i = 1; i < Info.size(); i++)
	{
		if (UseCount > Info[i].UseCount)
		{
			SelectCount = (int)i;
			UseCount = Info[i].UseCount;
		}
	}

	Info[SelectCount].UseCount++;;

	return Info[SelectCount];
}

void CStageManager::BGMSoundUpdate(StageType Type)
{
	BGMSoundPause();
	if (m_BossStage)
	{
		return;
	}
	switch (Type)
	{
	case StageType::Base:
	case StageType::Start:
	case StageType::End:
		m_BGMSound[(int)Type]->Play();
		break;
	case StageType::Shop:
		m_BGMSound[(int)Type]->Play();
		break;
	case StageType::Boss:
		break;

	case StageType::Restaurant:
		m_BGMSound[(int)Type]->Play();
		break;
	}
}
void CStageManager::BGMBossSoundPlay()
{
	BGMSoundPause();
	m_BGMSound[(int)StageType::Boss]->Play();

}
void CStageManager::BGMSoundPause()
{
	int Size = (int)StageType::Boss + 1;
	for (int i = 0; i < Size; ++i)
	{
		if(m_BGMSound[i])
			m_BGMSound[i]->Pause();
	}
}


DEFINITION_SINGLE(CStageManager)
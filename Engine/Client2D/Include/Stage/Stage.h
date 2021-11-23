#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"
#include <Component/TileMapComponent.h>
#include "../Object/SpawnEffect.h"
//Enemy,Object,Tile Door 등 들고있는 클래스
class CStage
{
public:
	CStage();
	virtual ~CStage();
private:

	/*
	추가될사항
	맵
	미니맵
	맵UI
	*/
	std::string m_Name;
	Stage_State m_State;
	int m_EnemyOrder;
	std::unordered_map<int, std::vector<CSharedPtr<CSpawnEffect>>> m_SpawnEnemy;
	std::vector<CSharedPtr<CGameObject>> m_vecEnemy;
	std::vector<CSharedPtr<CGameObject>> m_Object;
	std::vector<CSharedPtr<CSpawnEffect>> m_ItemSpawn;
	std::vector<CSharedPtr<CDoor>> m_Doors;
	class CGameObject* m_TileMap;
	class CGameObject* m_TileMapObject;
	CSharedPtr<CTileMapComponent> m_TileMapComponent;
	CSharedPtr<CTileMapComponent> m_TileObjectMapComponent;
	
	bool m_Enable;
	class CScene* m_pScene;
	int m_DoorDir;
public:
	std::string GetName() const
	{
		return m_Name;
	}
	void SetScene(class CScene* Scene)
	{
		m_pScene = Scene;
	}
	void Enable(bool Enable);
	void Active(bool bActive);
	Stage_State GetStageState()
	{
		return m_State;
	}
	void SetTileMap(class CGameObject* TileMap)
	{
		m_TileMap = TileMap;
	}void SetTileMapObject(class CGameObject* TileMapObject)
	{
		m_TileMapObject = TileMapObject;
	}
	void ObjectUpdate(StageObjectsInfo Info, StageType Type, int num);
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CStage* Clone();
public:

	void PushObject(class CGameObject* obj);
	void DeleteObject(class CGameObject* obj);
	void PushEnemy(class CGameObject* obj);
	void PlayerStageMove(Stage_Dir Dir);
	void PushSpawnEnemy(CSpawnEffect* Obj);
};

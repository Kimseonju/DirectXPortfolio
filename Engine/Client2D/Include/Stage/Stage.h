#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"
#include <Component/TileMapComponent.h>
#include "../Object/SpawnEffect.h"
#include "../Object/Gate.h"
//Enemy,Object,Tile Door ?? ?????ִ? Ŭ????
class CStage
{
public:
	CStage();
	virtual ~CStage();
private:

	/*
	?߰??ɻ???
	??
	?̴ϸ?
	??UI
	*/
	std::string m_Name;
	Stage_State m_State;
	int m_EnemyOrder;
	StageType m_Type;
	std::unordered_map<int, std::vector<CSharedPtr<CSpawnEffect>>> m_SpawnEnemy;
	std::vector<CSharedPtr<CGameObject>> m_vecEnemy;
	std::vector<CSharedPtr<CGameObject>> m_Object;
	std::vector<CSharedPtr<CSpawnEffect>> m_ItemSpawn;
	std::vector<CSharedPtr<CDoor>> m_Doors;
	CSharedPtr<CGate> m_Gate;
	class CGameObject* m_TileMap;
	class CGameObject* m_TileMapObject;
	CSharedPtr<CTileMapComponent> m_TileMapComponent;
	CSharedPtr<CTileMapComponent> m_TileObjectMapComponent;
	
	bool m_Enable;
	class CScene* m_pScene;
	int m_DoorDir;
public:
	bool IsGate()
	{
		return m_Gate;
	}

	StageType GetStageType()
	{
		return m_Type;
	}
	CTileMapComponent* GetTileComonent()
	{
		return m_TileMapComponent;
	}

	std::vector<CTile*>& GetvecTile()
	{
		return m_TileMapComponent->GetvecTile();
	}

	std::vector<CTile*>& GetvecObjectTile()
	{
		return m_TileObjectMapComponent->GetvecTile();
	}
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
	}
	void SetTileMapObject(class CGameObject* TileMapObject)
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
	void PlayerStageGate();
	void MoveStageGate(Vector2 Pos);
	void PushSpawnEnemy(CSpawnEffect* Obj);
};

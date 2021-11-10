#pragma once
#include <GameObject.h>
#include "../GlobalValue.h"
#include "Door.h"

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
	Stage_State m_State;
	std::vector<CSharedPtr<CGameObject>> m_Enemy;
	std::vector<CSharedPtr<CGameObject>> m_Object;
	std::vector<CDoor*> m_Doors;
	class CGameObject* m_TileMap;
	class CGameObject* m_TileMapObject;
	class CTileMapComponent* m_TileMapComponent;
	class CTileMapComponent* m_TileObjectMapComponent;
	
	bool m_Enable;
	class CScene* m_pScene;
	int m_DoorDir;
public:
	void SetScene(class CScene* Scene)
	{
		m_pScene = Scene;
	}
	void Enable(bool Enable);
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
	void PlayerStageMove(Stage_Dir Dir);
};

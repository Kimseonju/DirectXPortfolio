#pragma once
#include "IMGUIWindow.h"
#include "Editor.h"
#include "GameEngine.h"
class CTileMapToolWindow :
	public CIMGUIWindow
{
public:
	CTileMapToolWindow();
	virtual ~CTileMapToolWindow();

private:
	class CIMGUITileMapComponent* m_TileMap;
	class CIMGUITileComponent* m_Tile;

	class CIMGUITabBar* m_TabBar;
	class CIMGUIText* m_CameraPosX;
	class CIMGUIText* m_CameraPosY;
	class CIMGUIText* m_MousePosX;
	class CIMGUIText* m_MousePosY;
	class CIMGUIText* m_TileIndexX;
	class CIMGUIText* m_TileIndexY;
	class CScene*	  m_pScene;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
public:
	void CreateTileMapComponent();
	void CreateTileComponent();
public:

	void SetPosition(const Vector3& Pos);
	void SetScene(class CScene* Scene)
	{
		m_pScene = Scene;
	}
public:
	int GetImageFrameX();
	int GetImageFrameY();
	class CTileMapComponent* GetTileMap();
	class CIMGUITileMapComponent* GetTileMapComponent();
	bool IsTileMap();
	Tile_Shape GetTileShape();
	Tile_Type GetTileType();
	Tile_Modify_Type GetTileModifyType()	const;

public:

	Vector2 GetImageFrame()	const;
public:

};

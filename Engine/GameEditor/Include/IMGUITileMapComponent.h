#pragma once
#include "IMGUIWidgetComponent.h"
#include "Editor.h"
#include "Component/TileMapComponent.h"
#include "Resource/Texture.h"
#include <IMGUITabItem.h>
class CIMGUITileMapComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUITileMapComponent();
	virtual ~CIMGUITileMapComponent();

private:



private:
	CSharedPtr<CTexture>	m_TileTexture;

private:
	class CIMGUITextInput* m_InputPosX;
	class CIMGUITextInput* m_InputPosY;
	class CIMGUITextInput* m_InputPosZ;
	class CIMGUITextInput* m_InputScaleX;
	class CIMGUITextInput* m_InputScaleY;
	class CIMGUITextInput* m_InputScaleZ;
	class CIMGUITextInput* m_InputRotX;
	class CIMGUITextInput* m_InputRotY;
	class CIMGUITextInput* m_InputRotZ;

private:
	class CIMGUIComboBox* m_TileShapeCombo;
	class CIMGUITextInput* m_InputTileCountX;
	class CIMGUITextInput* m_InputTileCountY;
	class CIMGUITextInput* m_InputTileSizeX;
	class CIMGUITextInput* m_InputTileSizeY;
	class CIMGUITextInput* m_InputImageFrameX;
	class CIMGUITextInput* m_InputImageFrameY;
	class CIMGUITextInput* m_InputImageFrameMaxX;
	class CIMGUITextInput* m_InputImageFrameMaxY;
	Tile_Shape		m_TileShape;
	class CIMGUIComboBox* m_TileModifyTypeCombo;
	class CIMGUIComboBox* m_TileEditCombo;
	class CIMGUIImage* m_TileImage;
	Tile_Type			m_TileType;
	Tile_Modify_Type	m_TileModifyType;
	bool		m_CreateTile;
	CSharedPtr<CTileMapComponent> m_TileMapComponent;
	CSharedPtr<CTileMapComponent> m_TileMapObjectComponent;
	CSharedPtr<CGameObject>	m_TileMap;
	CSharedPtr<CGameObject>	m_TileObjectMap;
	int		m_ImageFrameX;
	int		m_ImageFrameY;
	int		m_ImageFrameMaxX;
	int		m_ImageFrameMaxY;
private:
	CIMGUITabItem* m_TileMapTabItem;
	class CIMGUITileComponent* m_TileComponent;

public:

	void SetTileComponent(class CIMGUITileComponent* Component)
	{
		m_TileComponent = Component;
	}

	CIMGUITabItem* GetTabItem()
	{
		return m_TileMapTabItem;
	}
	int GetImageFrameX()	const
	{
		return m_ImageFrameX;
	}

	int GetImageFrameY()	const
	{
		return m_ImageFrameY;
	}

	CTileMapComponent* GetTileMapComponent()	const
	{
		return m_TileMapComponent;
	}

	CTileMapComponent* GetTileMapObjectComponent()	const
	{
		return m_TileMapObjectComponent;
	}
	bool IsTileMap()	const
	{
		return m_CreateTile;
	}

	Tile_Shape GetTileShape()	const
	{
		return m_TileShape;
	}

	Tile_Type GetTileType()	const
	{
		return m_TileType;
	}

	Tile_Modify_Type GetTileModifyType()	const
	{
		return m_TileModifyType;
	}

public:
	void SetPosition(const Vector3& Pos);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputPosX();
	void InputPosY();
	void InputPosZ();
	void InputRotX();
	void InputRotY();
	void InputRotZ();
	void InputScaleX();
	void InputScaleY();
	void InputScaleZ();
	void InputImageFrameX();
	void InputImageFrameY();
	void InputImageFrameMaxX();
	void InputImageFrameMaxY();

public:
	void InputTileCountX();
	void InputTileCountY();
	void InputTileSizeX();
	void InputTileSizeY();


private:
	void TileShapeComboCallback(int SelectIndex, const char* Item);
	void TileModifyTypeComboCallback(int SelectIndex, const char* Item);
	void TileEditComboCallback(int SelectIndex, const char* Item);
	void CreateInputPos();
	void CreateInputScale();
	void CreateInputRotation();
	void CreateTileMapInfo();
public:
	void CreateMapTool();
public:
	void CreateTileButton();
	void SaveTileMap();
	void SaveTile(FILE* pFile);
	void LoadTileMap();
	void LoadTile(FILE* pFile);
	void LoadTileImage();

};

#pragma once

#include "IMGUIWindow.h"
#include "Editor.h"
#include "Component/TileMapComponent.h"

class CTileMapWindow :
	public CIMGUIWindow
{
public:
	CTileMapWindow();
	virtual ~CTileMapWindow();

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
	Tile_Shape		m_TileShape;
	class CIMGUIComboBox* m_TileModifyTypeCombo;
	class CIMGUIComboBox* m_TileEditCombo;
	Tile_Type			m_TileType;
	Tile_Modify_Type	m_TileModifyType;
	bool		m_CreateTile;
	CSharedPtr<CTileMapComponent> m_TileMap;

public:
	CTileMapComponent* GetTileMap()	const
	{
		return m_TileMap;
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
	void CreateTileButton();
	void SaveTileMap();
	void LoadTileMap();
};


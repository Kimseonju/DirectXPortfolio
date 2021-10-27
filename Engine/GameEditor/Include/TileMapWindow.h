#pragma once

#include "IMGUIWindow.h"

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
	void CreateInputPos();
	void CreateInputScale();
	void CreateInputRotation();
	void CreateTileMapInfo();

public:
	void CreateTileButton();
};


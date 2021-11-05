#include "pch.h"
#include "TileMapToolWindow.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"

#include "IMGUITileComponent.h"
#include "IMGUITileMapComponent.h"
#include <IMGUITabBar.h>
#include <IMGUITabBarEnd.h>
#include <IMGUISeparator.h>
#include <Input.h>
#include <Engine.h>
#include <Scene/Scene.h>
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
CTileMapToolWindow::CTileMapToolWindow()
{
}

CTileMapToolWindow::~CTileMapToolWindow()
{
	SAFE_DELETE(m_TileMap);
	SAFE_DELETE(m_Tile);
}

bool CTileMapToolWindow::Init()
{
	m_TabBar = AddWidget<CIMGUITabBar>("TileMapTool");
	CreateTileMapComponent();
	CreateTileComponent();
	m_TabBar->WidgetPush(m_TileMap->GetTabItem());
	m_TabBar->WidgetPush(m_Tile->GetTabItem());
	m_TileMap->SetTileComponent(m_Tile);
	m_TabBar->SetTabBar(AddWidget<CIMGUITabBarEnd>("TileMapToolEnd"));


	AddWidget<CIMGUISeparator>("Separator");

	//Camera
	CIMGUIText* Text = AddWidget<CIMGUIText>("CameraPos1");
	Text->SetText("CameraPos : ");
	CIMGUISameLine* Sameline=AddWidget<CIMGUISameLine>("SameLine");
	m_CameraPosX = AddWidget<CIMGUIText>("##CameraPosXText");

	Sameline = AddWidget<CIMGUISameLine>("SameLine");
	Sameline->SetSpacing(10.f);
	m_CameraPosY = AddWidget<CIMGUIText>("##CameraPosYText");
	
	//Mouse
	Text=AddWidget<CIMGUIText>("MousePosX1");
	Text->SetText("MousePos : ");
	Sameline = AddWidget<CIMGUISameLine>("SameLine");

	m_MousePosX = AddWidget<CIMGUIText>("##MousePosXText");

	Sameline = AddWidget<CIMGUISameLine>("SameLine");
	Sameline->SetSpacing(10.f);
	m_MousePosY = AddWidget<CIMGUIText>("##MousePosYText");

	//Tile
	Text = AddWidget<CIMGUIText>("TileIndex");
	Text->SetText("TileIndex : ");
	Sameline = AddWidget<CIMGUISameLine>("SameLine");

	m_TileIndexX = AddWidget<CIMGUIText>("##TileIndexXText");

	Sameline = AddWidget<CIMGUISameLine>("SameLine");
	Sameline->SetSpacing(10.f);
	m_TileIndexY = AddWidget<CIMGUIText>("##TileIndexYText");
	return true;
}

void CTileMapToolWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	if (m_pScene)
	{
		CCamera* Camera=m_pScene->GetCameraManager()->GetCurrentCamera();
		Vector3 CameraPos=Camera->GetWorldPos();

		m_CameraPosX->SetText(std::to_string(CameraPos.x).c_str());
		m_CameraPosY->SetText(std::to_string(CameraPos.y).c_str());
	}

	Vector2 Pos=CInput::GetInst()->GetMouse2DWorldPos();
	m_MousePosX->SetText(std::to_string(Pos.x).c_str());
	m_MousePosY->SetText(std::to_string(Pos.y).c_str());

	int x=m_TileMap->GetTileMap()->GetTileIndexX(Vector3(Pos.x,Pos.y,0.f));
	int y=m_TileMap->GetTileMap()->GetTileIndexY(Vector3(Pos.x, Pos.y, 0.f));
	m_TileIndexX->SetText(std::to_string(x).c_str());
	m_TileIndexX->SetText(std::to_string(y).c_str());
}

void CTileMapToolWindow::CreateTileMapComponent()
{
	if (m_TileMap)
		return;
	m_TileMap = new CIMGUITileMapComponent;
	m_TileMap->SetOwner(this);
	m_TileMap->Init();
}

void CTileMapToolWindow::CreateTileComponent()
{
	if (m_Tile)
		return;
	m_Tile = new CIMGUITileComponent;
	m_Tile->SetOwner(this);
	m_Tile->Init();
}

void CTileMapToolWindow::SetPosition(const Vector3& Pos)
{
	m_TileMap->SetPosition(Pos);
}

int CTileMapToolWindow::GetImageFrameX()
{
	return m_TileMap->GetImageFrameX();
}

int CTileMapToolWindow::GetImageFrameY()
{
	return m_TileMap->GetImageFrameY();
}

CTileMapComponent* CTileMapToolWindow::GetTileMap()
{
	return m_TileMap->GetTileMap();
}

CIMGUITileMapComponent* CTileMapToolWindow::GetTileMapComponent()
{
	return m_TileMap;
}

bool CTileMapToolWindow::IsTileMap()
{
	return m_TileMap->IsTileMap();
}

Tile_Shape CTileMapToolWindow::GetTileShape()
{
	return m_TileMap->GetTileShape();
}

Tile_Type CTileMapToolWindow::GetTileType()
{
	return m_TileMap->GetTileType();
}

Tile_Modify_Type CTileMapToolWindow::GetTileModifyType() const
{
	return m_TileMap->GetTileModifyType();
}

Vector2 CTileMapToolWindow::GetImageFrame() const
{
	return m_Tile->GetImageFrame();
}

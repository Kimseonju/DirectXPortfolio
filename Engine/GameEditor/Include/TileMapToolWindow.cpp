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
	return true;
}

void CTileMapToolWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
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

#include "pch.h"
#include "IMGUITileComponent.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "IMGUITabBar.h"
#include "IMGUITabItem.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "GameObject.h"
#include "Component/TileMapComponent.h"
#include <IMGUIImageButton.h>
#include <IMGUITabItemEnd.h>

#include "PathManager.h"
#include "IMGUIImage.h"
CIMGUITileComponent::CIMGUITileComponent()
{
}

CIMGUITileComponent::~CIMGUITileComponent()
{
}


bool CIMGUITileComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	//
	Text = m_Owner->AddWidget<CIMGUIText>("#####dump", 150.f, 20.f);
	m_vecWidget.push_back(Text);



	m_TileMapTabItem = m_Owner->AddWidget<CIMGUITabItem>("TileTool");

	m_ImageButton = m_Owner->AddWidget<CIMGUIImageButton>("Button100", 100.f, 100.f);

	m_ImageButton->SetTexture("tileAtlas", TEXT("Map/tileAtlas.png"));
	m_ImageButton->SetClickCallback<CIMGUITileComponent>(this, &CIMGUITileComponent::ImageButton);
	m_vecWidget.push_back(m_ImageButton);
	
	CIMGUIButton* SaveButton = m_Owner->AddWidget<CIMGUIButton>("Save", 150.f, 20.f);
	SaveButton->SetClickCallback<CIMGUITileComponent>(this, &CIMGUITileComponent::TestButtonClick);
	m_vecWidget.push_back(SaveButton);

	CIMGUISameLine* SameLine1 = m_Owner->AddWidget<CIMGUISameLine>("SameLine1");
	m_vecWidget.push_back(SameLine1);
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* LoadButton = m_Owner->AddWidget<CIMGUIButton>("Load", 150.f, 20.f);
	m_vecWidget.push_back(LoadButton);
	LoadButton->SetClickCallback(this, &CIMGUITileComponent::TestButtonClick);


	CIMGUIButton* DoorLeftButton = m_Owner->AddWidget<CIMGUIButton>("Door_Left", 150.f, 20.f);
	m_vecWidget.push_back(DoorLeftButton);
	SameLine1 = m_Owner->AddWidget<CIMGUISameLine>("SameLineDoor_Left");
	m_vecWidget.push_back(SameLine1);
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);

	CIMGUIButton* DeleteDoorLeft = m_Owner->AddWidget<CIMGUIButton>("DeleteDoor_Left", 150.f, 20.f);
	m_vecWidget.push_back(DeleteDoorLeft);
	DeleteDoorLeft->SetClickCallback(this, &CIMGUITileComponent::TestButtonClick);

	CIMGUIButton* DoorRightButton = m_Owner->AddWidget<CIMGUIButton>("Door_Right", 150.f, 20.f);
	m_vecWidget.push_back(DoorRightButton);
	SameLine1 = m_Owner->AddWidget<CIMGUISameLine>("SameLineDoor_Right");
	m_vecWidget.push_back(SameLine1);
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorRight = m_Owner->AddWidget<CIMGUIButton>("DeleteDoor_Right", 150.f, 20.f);
	m_vecWidget.push_back(DeleteDoorRight);
	DeleteDoorLeft->SetClickCallback(this, &CIMGUITileComponent::TestButtonClick);

	CIMGUIButton* DoorUpButton = m_Owner->AddWidget<CIMGUIButton>("Door_Up", 150.f, 20.f);
	m_vecWidget.push_back(DoorUpButton);
	SameLine1 = m_Owner->AddWidget<CIMGUISameLine>("SameLineDoor_Up");
	m_vecWidget.push_back(SameLine1);
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorUp = m_Owner->AddWidget<CIMGUIButton>("DeleteDoor_Up", 150.f, 20.f);
	m_vecWidget.push_back(DeleteDoorUp);
	DeleteDoorLeft->SetClickCallback(this, &CIMGUITileComponent::TestButtonClick);

	CIMGUIButton* DoorLeftDown = m_Owner->AddWidget<CIMGUIButton>("Door_Down", 150.f, 20.f);
	m_vecWidget.push_back(DoorLeftDown);
	SameLine1 = m_Owner->AddWidget<CIMGUISameLine>("SameLineDoor_Down");
	m_vecWidget.push_back(SameLine1);
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorDown = m_Owner->AddWidget<CIMGUIButton>("DeleteDoor_Down", 150.f, 20.f);
	m_vecWidget.push_back(DeleteDoorDown);
	DeleteDoorLeft->SetClickCallback(this, &CIMGUITileComponent::TestButtonClick);

	m_TileMapTabItem->WidgetPush(m_vecWidget);
	m_TileMapTabItem->SetTabBarEnd(m_Owner->AddWidget<CIMGUITabItemEnd>("TileToolEnd"));

	return true;
}

void CIMGUITileComponent::Update(float DeltaTime)
{
}

void CIMGUITileComponent::SetTexture(const std::string& Name, const TCHAR* FileName, const std::string& PathName)
{
	m_ImageButton->SetTexture(Name, FileName, PathName);
}

void CIMGUITileComponent::SetTextureFullPath(const std::string& Name, const TCHAR* FullPath)
{
	m_ImageButton->SetTextureFullPath(Name, FullPath);
}

void CIMGUITileComponent::SetTexture(CTexture* Texture)
{
	m_ImageButton->SetTexture(Texture);
}

void CIMGUITileComponent::SetFrameMax(int x, int y)
{
	m_ImageButton->SetFrameMax(x, y);
}

void CIMGUITileComponent::ImageButton()
{
	m_ImageFrame = m_ImageButton->GetImageFrame();
}

void CIMGUITileComponent::TestButtonClick()
{
}

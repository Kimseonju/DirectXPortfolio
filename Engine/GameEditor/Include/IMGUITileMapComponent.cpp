#include "pch.h"
#include "IMGUITileMapComponent.h"
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
#include "IMGUITileComponent.h"
#include <IMGUITabItemEnd.h>

#include "PathManager.h"
#include "IMGUIImage.h"


CIMGUITileMapComponent::CIMGUITileMapComponent() :
	m_CreateTile(false),
	m_ImageFrameX(0),
	m_ImageFrameY(0),
	m_ImageFrameMaxX(1),
	m_ImageFrameMaxY(1)
{
}

CIMGUITileMapComponent::~CIMGUITileMapComponent()
{
}

void CIMGUITileMapComponent::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
}

bool CIMGUITileMapComponent::Init()
{
	m_TileMapTabItem = m_Owner->AddWidget<CIMGUITabItem>("TileMapTool");
	CreateInputPos();
	CreateInputRotation();
	CreateInputScale();
	CreateTileMapInfo();

	m_TileMapTabItem->WidgetPush(m_vecWidget);
	m_TileMapTabItem->SetTabBarEnd(m_Owner->AddWidget<CIMGUITabItemEnd>("TileMapToolEnd"));

	m_TileShape = Tile_Shape::Rect;

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	Scene->GetResource()->CreateMaterial("MainMap");
	Scene->GetResource()->AddMaterialTexture("MainMap", "MainMap",
		TEXT("Diablos_Lair_Floor_TRS/Diablos_Lair_Floor.png"));
	Scene->GetResource()->SetMaterialTransparency("MainMap", true);
	Scene->GetResource()->SetMaterialShader("MainMap", "TileMapShader");

	Scene->GetResource()->CreateMaterial("MainMapRect");
	Scene->GetResource()->AddMaterialTexture("MainMapRect", "MainMapRect",
		TEXT("Floors.png"));
	Scene->GetResource()->SetMaterialTransparency("MainMapRect", true);
	Scene->GetResource()->SetMaterialShader("MainMapRect", "TileMapShader");


	return true;
}

void CIMGUITileMapComponent::Update(float DeltaTime)
{
}

void CIMGUITileMapComponent::InputPosX()
{
}

void CIMGUITileMapComponent::InputPosY()
{
}

void CIMGUITileMapComponent::InputPosZ()
{
}

void CIMGUITileMapComponent::InputRotX()
{
}

void CIMGUITileMapComponent::InputRotY()
{
}

void CIMGUITileMapComponent::InputRotZ()
{
}

void CIMGUITileMapComponent::InputScaleX()
{
}

void CIMGUITileMapComponent::InputScaleY()
{
}

void CIMGUITileMapComponent::InputScaleZ()
{
}

void CIMGUITileMapComponent::InputImageFrameX()
{
	m_ImageFrameX = m_InputImageFrameX->GetValueInt();

	if (m_ImageFrameX >= m_ImageFrameMaxX)
		m_ImageFrameX = m_ImageFrameMaxX - 1;

	else if (m_ImageFrameX < 0)
		m_ImageFrameX = 0;

	if (m_TileMap)
		m_TileMap->UpdateInfo();

	m_TileImage->SetStartUV(m_ImageFrameX / (float)m_ImageFrameMaxX,
		m_ImageFrameY / (float)m_ImageFrameMaxY);
	m_TileImage->SetEndUV((m_ImageFrameX + 1) / (float)m_ImageFrameMaxX,
		(m_ImageFrameY + 1) / (float)m_ImageFrameMaxY);
}

void CIMGUITileMapComponent::InputImageFrameY()
{
	m_ImageFrameY = m_InputImageFrameY->GetValueInt();

	if (m_ImageFrameY >= m_ImageFrameMaxY)
		m_ImageFrameY = m_ImageFrameMaxY - 1;

	else if (m_ImageFrameY < 0)
		m_ImageFrameY = 0;

	if (m_TileMap)
		m_TileMap->UpdateInfo();

	m_TileImage->SetStartUV(m_ImageFrameX / (float)m_ImageFrameMaxX,
		m_ImageFrameY / (float)m_ImageFrameMaxY);
	m_TileImage->SetEndUV((m_ImageFrameX + 1) / (float)m_ImageFrameMaxX,
		(m_ImageFrameY + 1) / (float)m_ImageFrameMaxY);
}

void CIMGUITileMapComponent::InputImageFrameMaxX()
{
	m_ImageFrameMaxX = m_InputImageFrameMaxX->GetValueInt();

	if (m_TileMap)
	{
		m_TileMap->SetFrameMax(m_ImageFrameMaxX, m_ImageFrameMaxY);
		m_TileMap->UpdateInfo();
	}
	if (m_TileComponent)
	{
		m_TileComponent->SetFrameMax(m_ImageFrameMaxX, m_ImageFrameMaxY);
	}

	m_TileImage->SetStartUV(m_ImageFrameX / (float)m_ImageFrameMaxX,
		m_ImageFrameY / (float)m_ImageFrameMaxY);
	m_TileImage->SetEndUV((m_ImageFrameX + 1) / (float)m_ImageFrameMaxX,
		(m_ImageFrameY + 1) / (float)m_ImageFrameMaxY);
}

void CIMGUITileMapComponent::InputImageFrameMaxY()
{
	m_ImageFrameMaxY = m_InputImageFrameMaxY->GetValueInt();

	if (m_TileMap)
	{
		m_TileMap->SetFrameMax(m_ImageFrameMaxX, m_ImageFrameMaxY);
		m_TileMap->UpdateInfo();
	}

	if (m_TileComponent)
	{
		m_TileComponent->SetFrameMax(m_ImageFrameMaxX, m_ImageFrameMaxY);
	}
	m_TileImage->SetStartUV(m_ImageFrameX / (float)m_ImageFrameMaxX,
		m_ImageFrameY / (float)m_ImageFrameMaxY);
	m_TileImage->SetEndUV((m_ImageFrameX + 1) / (float)m_ImageFrameMaxX,
		(m_ImageFrameY + 1) / (float)m_ImageFrameMaxY);
}

void CIMGUITileMapComponent::InputTileCountX()
{
}

void CIMGUITileMapComponent::InputTileCountY()
{
}

void CIMGUITileMapComponent::InputTileSizeX()
{
}

void CIMGUITileMapComponent::InputTileSizeY()
{
}

void CIMGUITileMapComponent::TileShapeComboCallback(int SelectIndex,
	const char* Item)
{
	m_TileShape = (Tile_Shape)SelectIndex;
}

void CIMGUITileMapComponent::TileModifyTypeComboCallback(int SelectIndex,
	const char* Item)
{
	m_TileModifyType = (Tile_Modify_Type)SelectIndex;

	m_TileEditCombo->DeleteAllItem();

	switch ((Tile_Modify_Type)SelectIndex)
	{
	case Tile_Modify_Type::Type:
		m_TileEditCombo->AddItem("None");
		m_TileEditCombo->AddItem("Wall");
		m_TileEditCombo->AddItem("Crossed_Wall");
		break;
	case Tile_Modify_Type::Image:
		break;
	}
}


void CIMGUITileMapComponent::TileEditComboCallback(int SelectIndex, const char* Item)
{
	switch (m_TileModifyType)
	{
	case Tile_Modify_Type::Type:
		m_TileType = (Tile_Type)SelectIndex;
		break;
	case Tile_Modify_Type::Image:
		break;
	}
}

void CIMGUITileMapComponent::CreateInputPos()
{
	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("Position");
	Text->SetFont("DefaultFont");
	Text->SetText("Position");

	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_InputPosX = m_Owner->AddWidget<CIMGUITextInput>("##PosX", 50.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputPosX);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPosX);
	m_vecWidget.push_back(SameLine);

	m_InputPosY = m_Owner->AddWidget<CIMGUITextInput>("##PosY", 50.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputPosY);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPosY);
	m_vecWidget.push_back(SameLine);

	m_InputPosZ = m_Owner->AddWidget<CIMGUITextInput>("##PosZ", 50.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputPosZ);
	m_vecWidget.push_back(m_InputPosZ);

	m_InputPosX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
}

void CIMGUITileMapComponent::CreateInputScale()
{
	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("Scale");
	Text->SetFont("DefaultFont");
	Text->SetText("Scale");

	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_InputScaleX = m_Owner->AddWidget<CIMGUITextInput>("##ScaleX", 50.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetFloat(1.f);
	m_InputScaleX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputScaleX);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputScaleX);
	m_vecWidget.push_back(SameLine);

	m_InputScaleY = m_Owner->AddWidget<CIMGUITextInput>("##ScaleY", 50.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetFloat(1.f);
	m_InputScaleY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputScaleY);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputScaleY);
	m_vecWidget.push_back(SameLine);

	m_InputScaleZ = m_Owner->AddWidget<CIMGUITextInput>("##ScaleZ", 50.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetFloat(1.f);
	m_InputScaleZ->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputScaleZ);
	m_vecWidget.push_back(m_InputScaleZ);

	m_InputScaleX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
}

void CIMGUITileMapComponent::CreateInputRotation()
{
	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("Rotation");
	Text->SetFont("DefaultFont");
	Text->SetText("Rotation");

	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);


	m_InputRotX = m_Owner->AddWidget<CIMGUITextInput>("##RotX", 50.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputRotX);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputRotX);
	m_vecWidget.push_back(SameLine);

	m_InputRotY = m_Owner->AddWidget<CIMGUITextInput>("##RotY", 50.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputRotY);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputRotY);
	m_vecWidget.push_back(SameLine);

	m_InputRotZ = m_Owner->AddWidget<CIMGUITextInput>("##RotZ", 50.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputRotZ);
	m_vecWidget.push_back(m_InputRotZ);

	m_InputRotX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
}

void CIMGUITileMapComponent::CreateTileMapInfo()
{


	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("TileMap");
	Text->SetFont("DefaultFont");
	Text->SetText("TileShape");

	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_TileShapeCombo = m_Owner->AddWidget<CIMGUIComboBox>("##TileShape", 300.f, 100.f);

	m_TileShapeCombo->SetSelectCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::TileShapeComboCallback);

	m_TileShapeCombo->AddItem("Rect");
	m_TileShapeCombo->AddItem("Rhombus");
	m_vecWidget.push_back(m_TileShapeCombo);

	Text = m_Owner->AddWidget<CIMGUIText>("TileMap");
	Text->SetFont("DefaultFont");
	Text->SetText("TileCount");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_InputTileCountX = m_Owner->AddWidget<CIMGUITextInput>("##TileCountX", 100.f, 20.f);
	m_InputTileCountX->SetNumberInt(true);
	m_InputTileCountX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputTileCountX);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputTileCountY = m_Owner->AddWidget<CIMGUITextInput>("##TileCountY", 100.f, 20.f);
	m_InputTileCountY->SetNumberInt(true);
	m_InputTileCountY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputTileCountY);

	m_vecWidget.push_back(m_InputTileCountX);
	m_vecWidget.push_back(m_InputTileCountY);
	m_vecWidget.push_back(SameLine);


	// Tile Size
	Text = m_Owner->AddWidget<CIMGUIText>("TileMapSize");
	Text->SetFont("DefaultFont");
	Text->SetText("TileSize");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);


	m_InputTileSizeX = m_Owner->AddWidget<CIMGUITextInput>("##TileSizeX", 100.f, 20.f);
	m_InputTileSizeX->SetNumberFloat(true);
	m_InputTileSizeX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputTileSizeX);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputTileSizeX);
	m_vecWidget.push_back(SameLine);


	m_InputTileSizeY = m_Owner->AddWidget<CIMGUITextInput>("##TileSizeY", 100.f, 20.f);
	m_InputTileSizeY->SetNumberFloat(true);
	m_InputTileSizeY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputTileSizeY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputTileSizeY);
	m_vecWidget.push_back(SameLine);

	CIMGUIButton* Button = m_Owner->AddWidget<CIMGUIButton>("타일생성", 80.f, 20.f);
	m_vecWidget.push_back(Button);

	Button->SetClickCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::CreateTileButton);

	Text = m_Owner->AddWidget<CIMGUIText>("TileMapModifyType");
	Text->SetFont("DefaultFont");
	Text->SetText("ModifyType");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_TileModifyTypeCombo = m_Owner->AddWidget<CIMGUIComboBox>("##TileModifyType", 100.f, 100.f);

	m_TileModifyTypeCombo->SetSelectCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::TileModifyTypeComboCallback);

	m_TileModifyTypeCombo->AddItem("Type");
	m_TileModifyTypeCombo->AddItem("Image");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_TileModifyTypeCombo);
	m_vecWidget.push_back(SameLine);

	Text = m_Owner->AddWidget<CIMGUIText>("TileMapEdit");
	Text->SetFont("DefaultFont");
	Text->SetText("TileTypeEdit");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_TileEditCombo = m_Owner->AddWidget<CIMGUIComboBox>("##TileTypeEdit", 100.f, 100.f);

	m_TileEditCombo->SetSelectCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::TileEditComboCallback);
	m_vecWidget.push_back(m_TileEditCombo);

	Text = m_Owner->AddWidget<CIMGUIText>("TileMap");
	Text->SetFont("DefaultFont");
	Text->SetText("ImageFrame");
	m_vecWidget.push_back(Text);

	Text = m_Owner->AddWidget<CIMGUIText>("FrameX", 70.f, 20.f);
	Text->SetText("FrameX");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_InputImageFrameX = m_Owner->AddWidget<CIMGUITextInput>("##ImageFrameX", 100.f, 20.f);
	m_InputImageFrameX->SetNumberInt(true);
	m_InputImageFrameX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputImageFrameX);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputImageFrameX);
	m_vecWidget.push_back(SameLine);

	Text = m_Owner->AddWidget<CIMGUIText>("FrameY", 70.f, 20.f);
	Text->SetText("FrameY");
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_InputImageFrameY = m_Owner->AddWidget<CIMGUITextInput>("##ImageFrameY", 100.f, 20.f);
	m_InputImageFrameY->SetNumberInt(true);
	m_InputImageFrameY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputImageFrameY);
	m_vecWidget.push_back(m_InputImageFrameY);

	Text = m_Owner->AddWidget<CIMGUIText>("FrameMaxX", 70.f, 20.f);
	Text->SetText("FrameMaxX");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");

	m_InputImageFrameMaxX = m_Owner->AddWidget<CIMGUITextInput>("##ImageFrameMaxX", 100.f, 20.f);
	m_InputImageFrameMaxX->SetNumberInt(true);
	m_InputImageFrameMaxX->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputImageFrameMaxX);
	m_InputImageFrameMaxX->SetInt(1);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputImageFrameMaxX);
	m_vecWidget.push_back(SameLine);

	Text = m_Owner->AddWidget<CIMGUIText>("FrameMaxY", 70.f, 20.f);
	Text->SetText("FrameMaxY");
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_InputImageFrameMaxY = m_Owner->AddWidget<CIMGUITextInput>("##ImageFrameMaxY", 100.f, 20.f);
	m_InputImageFrameMaxY->SetNumberInt(true);
	m_InputImageFrameMaxY->SetInputCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::InputImageFrameMaxY);
	m_InputImageFrameMaxY->SetInt(1);
	m_vecWidget.push_back(m_InputImageFrameMaxY);

	Text = m_Owner->AddWidget<CIMGUIText>("TileImage", 70.f, 20.f);
	Text->SetText("TileImage");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_TileImage = m_Owner->AddWidget<CIMGUIImage>("##TileImage", 100.f, 100.f);
	m_TileImage->SetStartUV(0.f, 0.f);
	m_TileImage->SetEndUV(1.f, 1.f);
	m_TileImage->SetTexture("DefaultImageSlot", TEXT("DefaultSlot.png"));

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_TileImage);
	m_vecWidget.push_back(SameLine);

	Button = m_Owner->AddWidget<CIMGUIButton>("타일이미지 불러오기", 150.f, 100.f);

	Button->SetClickCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::LoadTileImage);
	m_vecWidget.push_back(Button);

	Button = m_Owner->AddWidget<CIMGUIButton>("저장", 80.f, 40.f);

	Button->SetClickCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::SaveTileMap);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Button);
	m_vecWidget.push_back(SameLine);

	Button = m_Owner->AddWidget<CIMGUIButton>("불러오기", 80.f, 40.f);

	Button->SetClickCallback<CIMGUITileMapComponent>(this, &CIMGUITileMapComponent::LoadTileMap);
	m_vecWidget.push_back(Button);





}

void CIMGUITileMapComponent::CreateMapTool()
{

}

void CIMGUITileMapComponent::CreateTileButton()
{
	m_CreateTile = true;
	// 타일맵을 생성한다.
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	Vector3	Pos, Rot, Scale;

	Vector2	TileSize;

	int	TileCountX = 0, TileCountY = 0;

	Pos.x = m_InputPosX->GetValueFloat();
	Pos.y = m_InputPosY->GetValueFloat();
	Pos.z = m_InputPosZ->GetValueFloat();

	Rot.x = m_InputRotX->GetValueFloat();
	Rot.y = m_InputRotY->GetValueFloat();
	Rot.z = m_InputRotZ->GetValueFloat();

	Scale.x = m_InputScaleX->GetValueFloat();
	Scale.y = m_InputScaleY->GetValueFloat();
	Scale.z = m_InputScaleZ->GetValueFloat();

	TileSize.x = m_InputTileSizeX->GetValueFloat();
	TileSize.y = m_InputTileSizeY->GetValueFloat();

	TileCountX = m_InputTileCountX->GetValueInt();
	TileCountY = m_InputTileCountY->GetValueInt();

	CGameObject* MainMap = Scene->SpawnObject<CGameObject>("MainMap");

	CTileMapComponent* TileMap = MainMap->CreateSceneComponent<CTileMapComponent>("TileMap");

	MainMap->SetRootComponent(TileMap);

	TileMap->SetWorldPos(Pos);
	TileMap->SetWorldRotation(Rot);
	TileMap->SetWorldScale(Scale);


	// TileShape를 얻어온다.
	TileMap->CreateTile<CTile>(m_TileShape, TileCountX, TileCountY, TileSize);
	TileMap->SetMaterial(0, "MainMap");

	TileMap->SetFrameMax(m_ImageFrameMaxX, m_ImageFrameMaxY);
	TileMap->SetTileDefaultFrame(m_ImageFrameX, m_ImageFrameY);

	if (m_TileTexture)
	{
		TileMap->GetMaterial(0)->SetTexture("MainMap", m_TileTexture);
		TileMap->UpdateInfo();
	}
	//TileMap->SetMaterial(0, "MainMap");
	//TileMap->SetFrameMax(5, 76);
	//TileMap->SetTileDefaultFrame(3, 2);

	//TileMap->SetMaterial(0, "MainMapRect");
	//TileMap->SetFrameMax(1, 5);
	//TileMap->SetTileDefaultFrame(0, 0);
	m_TileMap = TileMap;
}


void CIMGUITileMapComponent::SaveTileMap()
{
	if (!m_TileMap)
	{
		AfxMessageBox(TEXT("타일맵을 생성하세요"));
		return;
	}

	static TCHAR	Filter[] = TEXT("MapFile(*.map)|*.map;|모든파일(*.*)|*.*||");

	CFileDialog	dlg(FALSE, TEXT(".map"), TEXT(""), OFN_OVERWRITEPROMPT,
		Filter);

	const PathInfo* Info = CPathManager::GetInst()->FindPath(MAP_PATH);

	dlg.m_pOFN->lpstrInitialDir = Info->pPath;

	if (dlg.DoModal() == IDOK)
	{
		m_TileMap->SaveFullPath(dlg.GetPathName());
	}
}

void CIMGUITileMapComponent::LoadTileMap()
{
	static TCHAR	Filter[] = TEXT("MapFile(*.map)|*.map;|모든파일(*.*)|*.*||");

	CFileDialog	dlg(TRUE, TEXT(".map"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	const PathInfo* Info = CPathManager::GetInst()->FindPath(MAP_PATH);

	dlg.m_pOFN->lpstrInitialDir = Info->pPath;

	if (dlg.DoModal() == IDOK)
	{
		if (!m_TileMap)
		{
			CScene* Scene = CSceneManager::GetInst()->GetScene();

			CGameObject* MainMap = Scene->SpawnObject<CGameObject>("MainMap");

			CTileMapComponent* TileMap = MainMap->CreateSceneComponent<CTileMapComponent>("TileMap");

			MainMap->SetRootComponent(TileMap);

			m_TileMap = TileMap;
		}

		m_TileMap->LoadFullPath(dlg.GetPathName());

		m_InputTileCountX->SetInt(m_TileMap->GetTileCountX());
		m_InputTileCountY->SetInt(m_TileMap->GetTileCountY());
		m_InputTileSizeX->SetFloat(m_TileMap->GetTileSize().x);
		m_InputTileSizeY->SetFloat(m_TileMap->GetTileSize().y);

		m_CreateTile = true;
	}
}

void CIMGUITileMapComponent::LoadTileImage()
{
	static TCHAR	Filter[] = TEXT("ImageFile(*.BMP, *.PNG, *.JPG, *.JPEG, *.TGA, *.DDS) | *.BMP;*.PNG;*.JPG;*.JPEG;*.TGA;*.DDS;*.bmp;*.png;*.jpg;*.jpeg;*.tga;*.dds |모든파일(*.*)|*.*||");

	CFileDialog	dlg(TRUE, TEXT(".png"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	const PathInfo* Info = CPathManager::GetInst()->FindPath(TEXTURE_PATH);

	dlg.m_pOFN->lpstrInitialDir = Info->pPath;

	if (dlg.DoModal() == IDOK)
	{
		CScene* Scene = CSceneManager::GetInst()->GetScene();

		std::string	Name = CT2CA(dlg.GetFileTitle());

		Scene->GetResource()->LoadTextureFullPath(Name,
			dlg.GetPathName().GetString());

		m_TileTexture = Scene->GetResource()->FindTexture(Name);

		m_TileImage->SetStartUV(0.f, 0.f);
		m_TileImage->SetEndUV(1.f, 1.f);
		m_TileImage->SetTexture(m_TileTexture);
		if(m_TileComponent)
			m_TileComponent->SetTexture(m_TileTexture);

		if (m_TileMap)
		{
			m_TileMap->GetMaterial(0)->SetTexture("MainMap", m_TileTexture);

			if (m_TileTexture)
			{
				m_TileMap->GetMaterial(0)->SetTexture("MainMap", m_TileTexture);
				m_TileMap->UpdateInfo();
			}
		}
	}
}

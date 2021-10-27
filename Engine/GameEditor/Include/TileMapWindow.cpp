#include "pch.h"
#include "TileMapWindow.h"
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
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "GameObject.h"
#include "Component/TileMapComponent.h"

CTileMapWindow::CTileMapWindow()
{
}

CTileMapWindow::~CTileMapWindow()
{
}

void CTileMapWindow::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
}

bool CTileMapWindow::Init()
{
	CreateInputPos();
	CreateInputRotation();
	CreateInputScale();

	CreateTileMapInfo();

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

void CTileMapWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CTileMapWindow::InputPosX()
{
	float x = m_InputPosX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosX(x);
}

void CTileMapWindow::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosY(y);
}

void CTileMapWindow::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosZ(z);
}

void CTileMapWindow::InputRotX()
{
}

void CTileMapWindow::InputRotY()
{
}

void CTileMapWindow::InputRotZ()
{
}

void CTileMapWindow::InputScaleX()
{
}

void CTileMapWindow::InputScaleY()
{
}

void CTileMapWindow::InputScaleZ()
{
}

void CTileMapWindow::InputTileCountX()
{
}

void CTileMapWindow::InputTileCountY()
{
}

void CTileMapWindow::InputTileSizeX()
{
}

void CTileMapWindow::InputTileSizeY()
{
}

void CTileMapWindow::TileShapeComboCallback(int SelectIndex,
	const char* Item)
{
	m_TileShape = (Tile_Shape)SelectIndex;
}

void CTileMapWindow::CreateInputPos()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("Position");
	Text->SetFont("DefaultFont");
	Text->SetText("Position");

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetText("X");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPosX = AddWidget<CIMGUITextInput>("##PosX", 50.f, 20.f);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputPosX);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetText("Y");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPosY = AddWidget<CIMGUITextInput>("##PosY", 50.f, 20.f);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputPosY);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 20.f);
	Label->SetText("Z");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputPosZ = AddWidget<CIMGUITextInput>("##PosZ", 50.f, 20.f);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputPosZ);

	m_InputPosX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
}

void CTileMapWindow::CreateInputScale()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("Scale");
	Text->SetFont("DefaultFont");
	Text->SetText("Scale");

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetText("X");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputScaleX = AddWidget<CIMGUITextInput>("##ScaleX", 50.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetFloat(1.f);
	m_InputScaleX->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputScaleX);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetText("Y");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputScaleY = AddWidget<CIMGUITextInput>("##ScaleY", 50.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetFloat(1.f);
	m_InputScaleY->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputScaleY);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 20.f);
	Label->SetText("Z");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputScaleZ = AddWidget<CIMGUITextInput>("##ScaleZ", 50.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetFloat(1.f);
	m_InputScaleZ->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputScaleZ);

	m_InputScaleX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
}

void CTileMapWindow::CreateInputRotation()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("Rotation", 70.f);
	Text->SetFont("DefaultFont");
	Text->SetText("Rotation");

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetText("X");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputRotX = AddWidget<CIMGUITextInput>("##RotX", 50.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputRotX);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetText("Y");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputRotY = AddWidget<CIMGUITextInput>("##RotY", 50.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputRotY);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Z", 30.f, 20.f);
	Label->SetText("Z");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputRotZ = AddWidget<CIMGUITextInput>("##RotZ", 50.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputRotZ);

	m_InputRotX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
}

void CTileMapWindow::CreateTileMapInfo()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("TileMap");
	Text->SetFont("DefaultFont");
	Text->SetText("TileShape");

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_TileShapeCombo = AddWidget<CIMGUIComboBox>("##TileShape", 300.f, 100.f);

	m_TileShapeCombo->SetSelectCallback<CTileMapWindow>(this, &CTileMapWindow::TileShapeComboCallback);

	m_TileShapeCombo->AddItem("Rect");
	m_TileShapeCombo->AddItem("Rhombus");

	Text = AddWidget<CIMGUIText>("TileMap");
	Text->SetFont("DefaultFont");
	Text->SetText("TileCount");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	CIMGUILabel* Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetText("X");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputTileCountX = AddWidget<CIMGUITextInput>("##TileCountX", 100.f, 20.f);
	m_InputTileCountX->SetNumberInt(true);
	m_InputTileCountX->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputTileCountX);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetText("Y");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputTileCountY = AddWidget<CIMGUITextInput>("##TileCountY", 100.f, 20.f);
	m_InputTileCountY->SetNumberInt(true);
	m_InputTileCountY->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputTileCountY);


	// Tile Size
	Text = AddWidget<CIMGUIText>("TileMapSize");
	Text->SetFont("DefaultFont");
	Text->SetText("TileSize");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("X", 30.f, 20.f);
	Label->SetText("X");

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputTileSizeX = AddWidget<CIMGUITextInput>("##TileSizeX", 100.f, 20.f);
	m_InputTileSizeX->SetNumberFloat(true);
	m_InputTileSizeX->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputTileSizeX);

	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	Label = AddWidget<CIMGUILabel>("Y", 30.f, 20.f);
	Label->SetText("Y");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputTileSizeY = AddWidget<CIMGUITextInput>("##TileSizeY", 100.f, 20.f);
	m_InputTileSizeY->SetNumberFloat(true);
	m_InputTileSizeY->SetInputCallback<CTileMapWindow>(this, &CTileMapWindow::InputTileSizeY);

	CIMGUIButton* Button = AddWidget<CIMGUIButton>("Ÿ�ϻ���", 100.f, 100.f);

	Button->SetClickCallback<CTileMapWindow>(this, &CTileMapWindow::CreateTileButton);
}

void CTileMapWindow::CreateTileButton()
{
	// Ÿ�ϸ��� �����Ѵ�.
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

	CGameObject* MainMap = Scene->SpawnObject<CGameObject>("MainMap",
		Pos, Rot, Scale);

	CTileMapComponent* TileMap = MainMap->CreateSceneComponent<CTileMapComponent>("TileMap");

	MainMap->SetRootComponent(TileMap);

	// TileShape�� ���´�.
	TileMap->CreateTile<CTile>(m_TileShape, TileCountX, TileCountY, TileSize);

	TileMap->SetMaterial(0, "MainMap");
	TileMap->SetFrameMax(5, 76);
	TileMap->SetTileDefaultFrame(3, 2);

	/*TileMap->SetMaterial(0, "MainMapRect");
	TileMap->SetFrameMax(1, 5);
	TileMap->SetTileDefaultFrame(0, 0);*/
}


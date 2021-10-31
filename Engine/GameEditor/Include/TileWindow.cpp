#include "pch.h"
#include "TileWindow.h"
#include "IMGUIButton.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include <IMGUIImageButton.h>
#include <Resource/ResourceManager.h>
/*
for (int i = 0; i < 8; i++)
		{
			ImGui::PushID(i);
			int frame_padding = -1 + i;                             // -1 == uses default padding (style.FramePadding)
			ImVec2 size = ImVec2(32.0f, 32.0f);                     // Size of the image we want to make visible
			ImVec2 uv0 = ImVec2(0.0f, 0.0f);                        // UV coordinates for lower-left
			ImVec2 uv1 = ImVec2(32.0f / my_tex_w, 32.0f / my_tex_h);// UV coordinates for (32,32) in our texture
			ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);         // Black background
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);       // No tint
			if (ImGui::ImageButton(my_tex_id, size, uv0, uv1, frame_padding, bg_col, tint_col))
				pressed_count += 1;
			ImGui::PopID();
			ImGui::SameLine();
		}

		이미지 클릭하는 부분 적용하기


*/
CTileWindow::CTileWindow() :
	m_ImageFrame(Vector2(-1,-1))
{
}

CTileWindow::~CTileWindow()
{
}

bool CTileWindow::Init()
{

	m_ImageButton = AddWidget<CIMGUIImageButton>("Button100", 100.f, 100.f);

	m_ImageButton->SetTexture("tileAtlas", TEXT("Map/tileAtlas.png"));
	m_ImageButton->SetClickCallback<CTileWindow>(this, &CTileWindow::ImageButton);

	CIMGUIButton* SaveButton = AddWidget<CIMGUIButton>("Save", 150.f, 20.f);
	SaveButton->SetClickCallback<CTileWindow>(this, &CTileWindow::TestButtonClick);

	CIMGUISameLine* SameLine1 = AddWidget<CIMGUISameLine>("SameLine1");
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* LoadButton = AddWidget<CIMGUIButton>("Load", 150.f, 20.f);
	LoadButton->SetClickCallback(this, &CTileWindow::TestButtonClick);
	

	CIMGUIButton* DoorLeftButton = AddWidget<CIMGUIButton>("Door_Left", 150.f, 20.f);
	SameLine1 = AddWidget<CIMGUISameLine>("SameLineDoor_Left");
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorLeft = AddWidget<CIMGUIButton>("DeleteDoor_Left", 150.f, 20.f);
	DeleteDoorLeft->SetClickCallback(this, &CTileWindow::TestButtonClick);

	CIMGUIButton* DoorRightButton = AddWidget<CIMGUIButton>("Door_Right", 150.f, 20.f);
	SameLine1 = AddWidget<CIMGUISameLine>("SameLineDoor_Right");
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorRight = AddWidget<CIMGUIButton>("DeleteDoor_Right", 150.f, 20.f);
	DeleteDoorLeft->SetClickCallback(this, &CTileWindow::TestButtonClick);

	CIMGUIButton* DoorUpButton = AddWidget<CIMGUIButton>("Door_Up", 150.f, 20.f);
	SameLine1 = AddWidget<CIMGUISameLine>("SameLineDoor_Up");
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorUp = AddWidget<CIMGUIButton>("DeleteDoor_Up", 150.f, 20.f);
	DeleteDoorLeft->SetClickCallback(this, &CTileWindow::TestButtonClick);

	CIMGUIButton* DoorLeftDown = AddWidget<CIMGUIButton>("Door_Down", 150.f, 20.f);
	SameLine1 = AddWidget<CIMGUISameLine>("SameLineDoor_Down");
	SameLine1->SetStartX(150.f);
	SameLine1->SetSpacing(50.f);
	CIMGUIButton* DeleteDoorDown = AddWidget<CIMGUIButton>("DeleteDoor_Down", 150.f, 20.f);
	DeleteDoorLeft->SetClickCallback(this, &CTileWindow::TestButtonClick);

	return true;
}

void CTileWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CTileWindow::ImageButton()
{
	m_ImageFrame =m_ImageButton->GetImageFrame();
}

void CTileWindow::TestButtonClick()
{
	MessageBox(0, TEXT("Test"), TEXT("Test"), MB_OK);
}

void CTileWindow::ListCallback(int SelectIndex, const char* Item)
{
	char    Text[256] = {};
	sprintf_s(Text, "Index : %d Item : %s", SelectIndex, Item);

	MessageBoxA(0, Text, "ListBox", MB_OK);
}

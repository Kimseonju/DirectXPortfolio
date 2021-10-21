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
CTileWindow::CTileWindow()
{
}

CTileWindow::~CTileWindow()
{
}

bool CTileWindow::Init()
{

	CIMGUIImageButton* ImageButton = AddWidget<CIMGUIImageButton>("Button100", 100.f, 100.f);

	if (!CResourceManager::GetInst()->LoadTexture("tileAtlas", TEXT("Map/tileAtlas.png")))
		return false;

	if (!CResourceManager::GetInst()->LoadTexture("townAtlas", TEXT("Map/townAtlas.png")))
		return false;
	CTexture* Image = CResourceManager::GetInst()->FindTexture("townAtlas");

	ImageButton->SetImage(Image);

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



	CIMGUILabel* Label1 = AddWidget<CIMGUILabel>("Test", 100.f, 100.f);
	Label1->SetFont("DefaultFont");

	Label1->SetText("Labe 테스트입니다.");

	CIMGUIText* Text1 = AddWidget<CIMGUIText>("Text", 100.f, 100.f);
	Text1->SetFont("DefaultFont");

	Text1->SetText("Text 테스트입니다.");

	CIMGUIListBox* ListBox1 = AddWidget<CIMGUIListBox>("ListBox", 300.f, 100.f);

	ListBox1->AddItem("AAA");
	ListBox1->AddItem("CCC");
	ListBox1->AddItem("EEE");
	ListBox1->AddItem("FFF");
	ListBox1->AddItem("BBB");
	ListBox1->AddItem("ZZZ");

	ListBox1->SetSelectCallback<CTileWindow>(this, &CTileWindow::ListCallback);
	ListBox1->Sort(true);


	CIMGUIComboBox* ComboBox1 = AddWidget<CIMGUIComboBox>("TestComboBox");

	ComboBox1->AddItem("AAA");
	ComboBox1->AddItem("CCC");
	ComboBox1->AddItem("EEE");
	ComboBox1->AddItem("FFF");
	ComboBox1->AddItem("BBB");
	ComboBox1->AddItem("ZZZ");

	ComboBox1->SetSelectCallback<CTileWindow>(this, &CTileWindow::ListCallback);

	CIMGUITextInput* TextInput1 = AddWidget<CIMGUITextInput>("TextInput", 100.f, 100.f);
	TextInput1->SetFont("DefaultFont");

	TextInput1->SetMultiLine(true);
	TextInput1->SetNumberInt(true);
	Text1->SetText("Text 테스트입니다.");

	return true;
}

void CTileWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
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

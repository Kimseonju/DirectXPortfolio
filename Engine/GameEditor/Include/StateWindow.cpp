#include "pch.h"
#include "StateWindow.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIRadioButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"

#include "IMGUITransformComponent.h"
#include "IMGUISpriteComponent.h"
#include "IMGUICollider2DComponent.h"
#include "IMGUICameraComponent.h"
#include "Editor.h"
#include "GlobalValue.h"
#include <Engine.h>
#include <Timer.h>
CStateWindow::CStateWindow()
{
}

CStateWindow::~CStateWindow()
{

}

bool CStateWindow::Init()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("MouseState");
	Text->SetText("MouseState");
	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_MosueStateRadioButton = AddWidget<CIMGUIRadioButton>("MouseStateRadioBox", 300.f, 20.f);

	m_MosueStateRadioButton->SetSelectCallback<CStateWindow>(this, &CStateWindow::MouseRadioCallback);
	m_MosueStateRadioButton->AddItem("Normal");
	m_MosueStateRadioButton->AddItem("Tile");
	m_MosueStateRadioButton->AddItem("TileObject");
	m_MosueStateRadioButton->AddItem("World");
	CGlobalValue::MouseState = Mouse_State::Normal;


	Text = AddWidget<CIMGUIText>("FPS");
	Text->SetText("FPS : ");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_FPS = AddWidget<CIMGUIText>("##FPS");

	return true;
}

void CStateWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	int FPS = (int)CEngine::GetInst()->GetFPS();
	m_FPS->SetText(std::to_string(FPS).c_str());
}

void CStateWindow::MouseRadioCallback(int SelectIndex, const char* Item)
{
	CGlobalValue::MouseState = (Mouse_State)SelectIndex;
}

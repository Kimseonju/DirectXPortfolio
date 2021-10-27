#include "pch.h"
#include "Animation2DWindow.h"
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

CAnimation2DWindow::CAnimation2DWindow()
{
}

CAnimation2DWindow::~CAnimation2DWindow()
{
}
void CAnimation2DWindow::SetAnimationName(const std::string& Name)
{
}
void CAnimation2DWindow::SetFrameIdx(float Idx)
{
}
void CAnimation2DWindow::SetFrameTime(float Time)
{
}
bool CAnimation2DWindow::Init()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("À§Ä¡");
	Text->SetFont("DefaultFont");


#pragma region FrameIdx

	CIMGUIText* Label = AddWidget<CIMGUIText>("Label_Title", 100.f, 20.f);
	Label->SetText("Animation2D");
	Label = AddWidget<CIMGUIText>("Label_Position", 100.f, 20.f);
	Label->SetText("FrameIdx");
	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputFrameIdx = AddWidget<CIMGUITextInput>("##InputFrameIdx", 100.f, 20.f);
	m_InputFrameIdx->SetNumberFloat(true);
	m_InputFrameIdx->SetInputCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::InputFrameIdx);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputFrameIdx->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion

#pragma region FrameTime

	Label = AddWidget<CIMGUIText>("Label_Position", 100.f, 20.f);
	Label->SetText("FrameTime");
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputFrameTime = AddWidget<CIMGUITextInput>("##InputFrameTime", 100.f, 20.f);
	m_InputFrameTime->SetNumberFloat(true);
	m_InputFrameTime->SetInputCallback<CAnimation2DWindow>(this, &CAnimation2DWindow::InpuFrameTime);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_InputFrameTime->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion

	return true;
}

void CAnimation2DWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CAnimation2DWindow::InputFrameIdx()
{
}

void CAnimation2DWindow::InpuFrameTime()
{
}

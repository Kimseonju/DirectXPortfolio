#include "pch.h"
#include "IMGUICollider2DComponent.h"
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

CIMGUICollider2DComponent::CIMGUICollider2DComponent()
{
}

CIMGUICollider2DComponent::~CIMGUICollider2DComponent()
{
}

void CIMGUICollider2DComponent::SetPosition(const Vector2& Pos)
{
	m_OffsetInputPosX->SetFloat(Pos.x);
	m_OffsetInputPosY->SetFloat(Pos.y);
}

void CIMGUICollider2DComponent::SetScale(const Vector2& Pos)
{
	m_OffsetInputScaleX->SetFloat(Pos.x);
	m_OffsetInputScaleY->SetFloat(Pos.y);
}
void CIMGUICollider2DComponent::TypeComboCallback(int SelectIndex, const char* Item)
{
	//m_TileShape = (Tile_Shape)SelectIndex;
}
bool CIMGUICollider2DComponent::Init()
{
	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("À§Ä¡");
	Text->SetFont("DefaultFont");
	m_vecWidget.push_back(Text);
#pragma region Type
	m_Collider2DType = m_Owner->AddWidget<CIMGUIComboBox>("##TileShape", 300.f, 100.f);
	m_Collider2DType->SetSelectCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::TypeComboCallback);
	m_Collider2DType->AddItem("Box");
	m_Collider2DType->AddItem("Circle");
	m_Collider2DType->AddItem("Pixel");
	m_vecWidget.push_back(m_Collider2DType);
#pragma endregion

#pragma region Position

	CIMGUIText* Label = m_Owner->AddWidget<CIMGUIText>("Label_Title", 100.f, 20.f);
	Label->SetText("Collider2D");
	Label = m_Owner->AddWidget<CIMGUIText>("Label_Position", 100.f, 20.f);
	Label->SetText("OffsetPos");
	m_vecWidget.push_back(Label);
	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_OffsetInputPosX = m_Owner->AddWidget<CIMGUITextInput>("##OffsetInput_PosX", 100.f, 20.f);
	m_vecWidget.push_back(m_OffsetInputPosX);
	m_OffsetInputPosX->SetNumberFloat(true);
	m_OffsetInputPosX->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputPosX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_OffsetInputPosY = m_Owner->AddWidget<CIMGUITextInput>("##OffsetInput_PosY", 100.f, 20.f);
	m_vecWidget.push_back(m_OffsetInputPosY);
	m_OffsetInputPosY->SetNumberFloat(true);
	m_OffsetInputPosY->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputPosY);

	m_OffsetInputPosX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_OffsetInputPosY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion

#pragma region Scale

	Label = m_Owner->AddWidget<CIMGUIText>("Label_Scale", 100.f, 20.f);
	m_vecWidget.push_back(Label);
	Label->SetText("Offset Scale");
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);
	SameLine->SetSize(20.f, 20.f);

	m_OffsetInputScaleX = m_Owner->AddWidget<CIMGUITextInput>("##OffsetInput_ScaleX", 100.f, 20.f);
	m_vecWidget.push_back(m_OffsetInputScaleX);
	m_OffsetInputScaleX->SetNumberFloat(true);
	m_OffsetInputScaleX->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputScaleX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");

	m_OffsetInputScaleY = m_Owner->AddWidget<CIMGUITextInput>("##OffsetInput_ScaleY", 100.f, 20.f);
	m_vecWidget.push_back(m_OffsetInputScaleY);
	m_OffsetInputScaleY->SetNumberFloat(true);
	m_OffsetInputScaleY->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputScaleY);

	m_OffsetInputScaleX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_OffsetInputScaleY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion



	return true;
}

void CIMGUICollider2DComponent::Update(float DeltaTime)
{
}


void CIMGUICollider2DComponent::InputPosX()
{
	float x = m_OffsetInputPosX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosX(x);
}

void CIMGUICollider2DComponent::InputPosY()
{
	float y = m_OffsetInputPosY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosY(y);
}



void CIMGUICollider2DComponent::InputScaleX()
{
	float x = m_OffsetInputScaleX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleX(x);
}

void CIMGUICollider2DComponent::InputScaleY()
{
	float y = m_OffsetInputScaleY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleY(y);
}

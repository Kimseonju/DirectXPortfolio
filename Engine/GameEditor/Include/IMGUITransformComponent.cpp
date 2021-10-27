#include "pch.h"
#include "IMGUITransformComponent.h"
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

CIMGUITransformComponent::CIMGUITransformComponent()
{
}

CIMGUITransformComponent::~CIMGUITransformComponent()
{
}

void CIMGUITransformComponent::SetPosition(const Vector3& Pos)
{
	m_InputPosX->SetFloat(Pos.x);
	m_InputPosY->SetFloat(Pos.y);
	m_InputPosZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetRotation(const Vector3& Pos)
{
	m_InputRotX->SetFloat(Pos.x);
	m_InputRotY->SetFloat(Pos.y);
	m_InputRotZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetScale(const Vector3& Pos)
{
	m_InputScaleX->SetFloat(Pos.x);
	m_InputScaleY->SetFloat(Pos.y);
	m_InputScaleZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetPivot(const Vector3& Pos)
{
	m_InputPivotX->SetFloat(Pos.x);
	m_InputPivotY->SetFloat(Pos.y);
	m_InputPivotZ->SetFloat(Pos.z);
}
void CIMGUITransformComponent::SetComponent(CSceneComponent* Component)
{
	m_Component = Component;
	SetPosition(m_Component->GetWorldPos());
	SetRotation(m_Component->GetWorldRotation());
	SetScale(m_Component->GetWorldScale());
	SetPivot(m_Component->GetPivot());

}
bool CIMGUITransformComponent::Init()
{
	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("À§Ä¡");
	Text->SetFont("DefaultFont");
	m_vecWidget.push_back(Text);

#pragma region Position


	CIMGUIText* Label = m_Owner->AddWidget<CIMGUIText>("Label_Title", 100.f, 20.f);
	m_vecWidget.push_back(Label);
	Label->SetText("Transform");

	Label = m_Owner->AddWidget<CIMGUIText>("Label_Position", 100.f, 20.f);
	m_vecWidget.push_back(Label);
	Label->SetText("Position");
	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputPosX = m_Owner->AddWidget<CIMGUITextInput>("##Input_PosX", 100.f, 20.f);
	m_vecWidget.push_back(m_InputPosX);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputPosY = m_Owner->AddWidget<CIMGUITextInput>("##Input_PosY", 100.f, 20.f);
	m_vecWidget.push_back(m_InputPosY);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputPosZ = m_Owner->AddWidget<CIMGUITextInput>("##Input_PosZ", 100.f, 20.f);
	m_vecWidget.push_back(m_InputPosZ);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosZ);


	m_InputPosX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPosZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion
#pragma region Rotation
	Label = m_Owner->AddWidget<CIMGUIText>("Label_Rotation", 100.f, 20.f);
	Label->SetText("Rotation");
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Label);
	m_vecWidget.push_back(SameLine);

	m_InputRotX = m_Owner->AddWidget<CIMGUITextInput>("##Input_RotationX", 100.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputRotX);
	m_vecWidget.push_back(SameLine);

	m_InputRotY = m_Owner->AddWidget<CIMGUITextInput>("##Input_RotationY", 100.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputRotY);
	m_vecWidget.push_back(SameLine);

	m_InputRotZ = m_Owner->AddWidget<CIMGUITextInput>("##Input_RotationZ", 100.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotZ);
	m_vecWidget.push_back(m_InputRotZ);


	m_InputRotX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputRotZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
#pragma endregion

#pragma region Scale

	Label = m_Owner->AddWidget<CIMGUIText>("Label_Scale", 100.f, 20.f);
	Label->SetText("Scale");
	SameLine->SetSize(20.f, 20.f);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Label);
	m_vecWidget.push_back(SameLine);

	m_InputScaleX = m_Owner->AddWidget<CIMGUITextInput>("##Input_ScaleX", 100.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputScaleX);
	m_vecWidget.push_back(SameLine);

	m_InputScaleY = m_Owner->AddWidget<CIMGUITextInput>("##Input_ScaleY", 100.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputScaleY);
	m_vecWidget.push_back(SameLine);

	m_InputScaleZ = m_Owner->AddWidget<CIMGUITextInput>("##Input_ScaleZ", 100.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleZ);
	m_vecWidget.push_back(m_InputScaleZ);


	m_InputScaleX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputScaleZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion

#pragma region Pivot


	Label = m_Owner->AddWidget<CIMGUIText>("Label_Pivot", 100.f, 20.f);
	Label->SetText("Pivot");
	SameLine->SetSize(20.f, 20.f);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Label);
	m_vecWidget.push_back(SameLine);

	m_InputPivotX = m_Owner->AddWidget<CIMGUITextInput>("##Input_PivotX", 100.f, 20.f);
	m_InputPivotX->SetNumberFloat(true);
	m_InputPivotX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPivotX);
	m_vecWidget.push_back(SameLine);

	m_InputPivotY = m_Owner->AddWidget<CIMGUITextInput>("##Input_PivotY", 100.f, 20.f);
	m_InputPivotY->SetNumberFloat(true);
	m_InputPivotY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPivotY);
	m_vecWidget.push_back(SameLine);

	m_InputPivotZ = m_Owner->AddWidget<CIMGUITextInput>("##Input_PivotZ", 100.f, 20.f);
	m_InputPivotZ->SetNumberFloat(true);
	m_InputPivotZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleZ);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPivotZ);
	m_vecWidget.push_back(SameLine);


	m_InputPivotX->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPivotY->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_InputPivotZ->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);

#pragma endregion





	return true;
}

void CIMGUITransformComponent::Update(float DeltaTime)
{
	if(m_Component)
		SetComponent(m_Component);
}


void CIMGUITransformComponent::InputPosX()
{
	float x = m_InputPosX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosX(x);
}

void CIMGUITransformComponent::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosY(y);
}

void CIMGUITransformComponent::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPosZ(z);
}

void CIMGUITransformComponent::InputRotX()
{
	float x = m_InputRotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetRotX(x);
}

void CIMGUITransformComponent::InputRotY()
{
	float y = m_InputRotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetRotY(y);
}

void CIMGUITransformComponent::InputRotZ()
{
	float z = m_InputRotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetRotZ(z);
}

void CIMGUITransformComponent::InputScaleX()
{
	float x = m_InputScaleX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleX(x);
}

void CIMGUITransformComponent::InputScaleY()
{
	float y = m_InputScaleY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleY(y);
}

void CIMGUITransformComponent::InputScaleZ()
{
	float z = m_InputScaleZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetScaleZ(z);
}

void CIMGUITransformComponent::InputPivotX()
{
	float z = m_InputPivotX->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPivotX(z);
}

void CIMGUITransformComponent::InputPivotY()
{
	float y = m_InputPivotY->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPivotY(y);
}

void CIMGUITransformComponent::InputPivotZ()
{
	float z = m_InputPivotZ->GetValueFloat();

	CObjectWindow* Window = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	Window->SetPivotZ(z);
}

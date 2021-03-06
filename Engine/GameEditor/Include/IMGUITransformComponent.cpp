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
#include "IMGUIDrag.h"
#include "IMGUICollapsingHeader.h"
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

	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;
	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Transform");
#pragma region Position


	Text = m_Owner->AddWidget<CIMGUIText>("Text_Title");
	m_vecWidget.push_back(Text);
	Text->SetText("Transform");

	Text = m_Owner->AddWidget<CIMGUIText>("Text_Position");
	m_vecWidget.push_back(Text);
	Text->SetText("Position");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputPosX = m_Owner->AddWidget<CIMGUIDrag>("##Input_PosX", 60.f, 20.f);
	m_vecWidget.push_back(m_InputPosX);
	m_InputPosX->SetNumberFloat(true);
	m_InputPosX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputPosY = m_Owner->AddWidget<CIMGUIDrag>("##Input_PosY", 60.f, 20.f);
	m_vecWidget.push_back(m_InputPosY);
	m_InputPosY->SetNumberFloat(true);
	m_InputPosY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputPosZ = m_Owner->AddWidget<CIMGUIDrag>("##Input_PosZ", 60.f, 20.f);
	m_vecWidget.push_back(m_InputPosZ);
	m_InputPosZ->SetNumberFloat(true);
	m_InputPosZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPosZ);

#pragma endregion
#pragma region Rotation
	Text = m_Owner->AddWidget<CIMGUIText>("Text_Rotation");
	Text->SetText("Rotation");
	m_vecWidget.push_back(Text);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputRotX = m_Owner->AddWidget<CIMGUIDrag>("##Input_RotationX", 60.f, 20.f);
	m_InputRotX->SetNumberFloat(true);
	m_InputRotX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputRotX);
	m_vecWidget.push_back(SameLine);

	m_InputRotY = m_Owner->AddWidget<CIMGUIDrag>("##Input_RotationY", 60.f, 20.f);
	m_InputRotY->SetNumberFloat(true);
	m_InputRotY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputRotY);
	m_vecWidget.push_back(SameLine);

	m_InputRotZ = m_Owner->AddWidget<CIMGUIDrag>("##Input_RotationZ", 60.f, 20.f);
	m_InputRotZ->SetNumberFloat(true);
	m_InputRotZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputRotZ);
	m_vecWidget.push_back(m_InputRotZ);


#pragma endregion

#pragma region Scale

	Text = m_Owner->AddWidget<CIMGUIText>("Text_Scale");
	Text->SetText("Scale");
	m_vecWidget.push_back(Text);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_InputScaleX = m_Owner->AddWidget<CIMGUIDrag>("##Input_ScaleX", 60.f, 20.f);
	m_InputScaleX->SetNumberFloat(true);
	m_InputScaleX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputScaleX);
	m_vecWidget.push_back(SameLine);

	m_InputScaleY = m_Owner->AddWidget<CIMGUIDrag>("##Input_ScaleY", 60.f, 20.f);
	m_InputScaleY->SetNumberFloat(true);
	m_InputScaleY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputScaleY);
	m_vecWidget.push_back(SameLine);

	m_InputScaleZ = m_Owner->AddWidget<CIMGUIDrag>("##Input_ScaleZ", 60.f, 20.f);
	m_InputScaleZ->SetNumberFloat(true);
	m_InputScaleZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputScaleZ);
	m_vecWidget.push_back(m_InputScaleZ);



#pragma endregion

#pragma region Pivot


	Text = m_Owner->AddWidget<CIMGUIText>("Text_Pivot");
	Text->SetText("Pivot");
	SameLine->SetSize(20.f, 20.f);
	m_vecWidget.push_back(Text);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine); 
	m_InputPivotX = m_Owner->AddWidget<CIMGUIDrag>("##Input_PivotX", 100.f, 20.f);
	m_InputPivotX->SetNumberFloat(true);
	m_InputPivotX->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPivotX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPivotX);
	m_vecWidget.push_back(SameLine);

	m_InputPivotY = m_Owner->AddWidget<CIMGUIDrag>("##Input_PivotY", 100.f, 20.f);
	m_InputPivotY->SetNumberFloat(true);
	m_InputPivotY->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPivotY);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(m_InputPivotY);
	m_vecWidget.push_back(SameLine);

	m_InputPivotZ = m_Owner->AddWidget<CIMGUIDrag>("##Input_PivotZ", 100.f, 20.f);
	m_InputPivotZ->SetNumberFloat(true);
	m_InputPivotZ->SetInputCallback<CIMGUITransformComponent>(this, &CIMGUITransformComponent::InputPivotZ);
	m_vecWidget.push_back(m_InputPivotZ);

#pragma endregion


	m_Header->WidgetPush(m_vecWidget);
	m_vecWidget.push_back(m_Header);

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

	Vector3 Pos=m_Component->GetRelativePos();
	Pos.x = x;
	m_Component->SetRelativePos(Pos);
}

void CIMGUITransformComponent::InputPosY()
{
	float y = m_InputPosY->GetValueFloat();

	Vector3 Pos = m_Component->GetRelativePos();
	Pos.y = y;
	m_Component->SetRelativePos(Pos);
}

void CIMGUITransformComponent::InputPosZ()
{
	float z = m_InputPosZ->GetValueFloat();

	Vector3 Pos = m_Component->GetRelativePos();
	Pos.z = z;
	m_Component->SetRelativePos(Pos);
}

void CIMGUITransformComponent::InputRotX()
{
	float x = m_InputRotX->GetValueFloat();

	m_Component->SetRelativeRotationX(x);
}

void CIMGUITransformComponent::InputRotY()
{
	float y = m_InputRotY->GetValueFloat();

	m_Component->SetRelativeRotationY(y);
}

void CIMGUITransformComponent::InputRotZ()
{
	float z = m_InputRotZ->GetValueFloat();

	m_Component->SetRelativeRotationZ(z);
}

void CIMGUITransformComponent::InputScaleX()
{
	float x = m_InputScaleX->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.x =x;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUITransformComponent::InputScaleY()
{
	float y = m_InputScaleY->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.y = y;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUITransformComponent::InputScaleZ()
{
	float z = m_InputScaleZ->GetValueFloat();

	Vector3 Scale = m_Component->GetRelativeScale();
	Scale.z =z;
	m_Component->SetRelativeScale(Scale);
}

void CIMGUITransformComponent::InputPivotX()
{
	float x = m_InputPivotX->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.x = x;
	m_Component->SetPivot(Pivot);
}

void CIMGUITransformComponent::InputPivotY()
{
	float y = m_InputPivotY->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.y = y;
	m_Component->SetPivot(Pivot);
}

void CIMGUITransformComponent::InputPivotZ()
{
	float z = m_InputPivotZ->GetValueFloat();

	Vector3 Pivot = m_Component->GetPivot();
	Pivot.z = z;
	m_Component->SetPivot(Pivot);
}

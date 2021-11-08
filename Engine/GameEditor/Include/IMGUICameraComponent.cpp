#include "pch.h"
#include "IMGUICameraComponent.h"
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
#include <Component/Collider.h>
#include <Component/Camera.h>
#include <IMGUIDrag.h>
#include <Scene/CameraManager.h>
#include <Scene/Scene.h>
#include <Resource/ResourceManager.h>
#include "IMGUICollapsingHeader.h"
CIMGUICameraComponent::CIMGUICameraComponent()
{
}

CIMGUICameraComponent::~CIMGUICameraComponent()
{
}

void CIMGUICameraComponent::UpdateInfo(CCamera* CCamera)
{
	m_Camera = CCamera;
	float Zoom=m_Camera->GetCameraZoom();
	Camera_Type Type=m_Camera->GetCameraType();
	float Left = m_Camera->GetCameraLeft();
	float Bottom = m_Camera->GetCameraBottom();
	Vector2 Min = m_Camera->GetMin();
	Vector2 Max = m_Camera->GetMax();
	m_CameraMinX->SetFloat(Min.x);
	m_CameraMinY->SetFloat(Min.y);
	m_CameraMaxX->SetFloat(Max.x);
	m_CameraMaxY->SetFloat(Max.x);
	switch (Type)
	{
	case Camera_Type::Cam3D:
		m_CameraType->SetText("Cam3D");
		break;
	case Camera_Type::Cam2D:
		m_CameraType->SetText("Cam2D");
		break;
	case Camera_Type::CamUI:
		m_CameraType->SetText("CamUI");
		break;
	}

	m_CameraZoom->SetFloat(Zoom);
	m_CameraLeft->SetText(std::to_string(Left).c_str());
	m_CameraBottom->SetText(std::to_string(Bottom).c_str());


	Enable(true);

}

bool CIMGUICameraComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Camera");
#pragma region Type

	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("##Type");
	Text->SetText("Type");
	m_vecWidget.push_back(Text);
	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraType = m_Owner->AddWidget<CIMGUIText>("##CameraType", 300.f, 20.f);

	m_vecWidget.push_back(m_CameraType);

#pragma endregion

#pragma region Info


	Text = m_Owner->AddWidget<CIMGUIText>("##Zoom");
	Text->SetText("Zoom");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraZoom = m_Owner->AddWidget<CIMGUIDrag>("##CameraZoom", 300.f, 20.f);
	m_CameraZoom->SetInputCallback<CIMGUICameraComponent>(this, &CIMGUICameraComponent::InputZoom);
	m_CameraZoom->SetNumberFloat(true);
	m_vecWidget.push_back(m_CameraZoom);


	Text = m_Owner->AddWidget<CIMGUIText>("##Left");
	Text->SetText("Left");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraLeft = m_Owner->AddWidget<CIMGUIText>("##CameraLeft", 300.f, 20.f);
	m_vecWidget.push_back(m_CameraLeft);


	Text = m_Owner->AddWidget<CIMGUIText>("##Bottom");
	Text->SetText("Bottom");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraBottom = m_Owner->AddWidget<CIMGUIText>("##CameraBottom", 300.f, 20.f);
	m_vecWidget.push_back(m_CameraBottom);

#pragma endregion

#pragma region MINMAX
	Text = m_Owner->AddWidget<CIMGUIText>("##CameraMin");
	Text->SetText("CameraMin");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraMinX = m_Owner->AddWidget<CIMGUIDrag>("##CameraMinX", 100.f, 20.f);
	m_CameraMinX->SetInputCallback<CIMGUICameraComponent>(this, &CIMGUICameraComponent::InputMinX);
	m_CameraMinX->SetNumberFloat(true);
	m_vecWidget.push_back(m_CameraMinX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraMinY = m_Owner->AddWidget<CIMGUIDrag>("##m_CameraMinY", 100.f, 20.f);
	m_CameraMinY->SetInputCallback<CIMGUICameraComponent>(this, &CIMGUICameraComponent::InputMinY);
	m_CameraMinY->SetNumberFloat(true);
	m_vecWidget.push_back(m_CameraMinY);


	Text = m_Owner->AddWidget<CIMGUIText>("##CameraMax");
	Text->SetText("CameraMax");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraMaxX = m_Owner->AddWidget<CIMGUIDrag>("##CameraMaxX", 100.f, 20.f);
	m_CameraMaxX->SetInputCallback<CIMGUICameraComponent>(this, &CIMGUICameraComponent::InputMaxX);
	m_CameraMaxX->SetNumberFloat(true);
	m_vecWidget.push_back(m_CameraMaxX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_CameraMaxY = m_Owner->AddWidget<CIMGUIDrag>("##m_CameraMinY", 100.f, 20.f);
	m_CameraMaxY->SetInputCallback<CIMGUICameraComponent>(this, &CIMGUICameraComponent::InputMaxY);
	m_CameraMaxY->SetNumberFloat(true);
	m_vecWidget.push_back(m_CameraMaxY);


#pragma endregion

	m_CurrentCamera = m_Owner->AddWidget<CIMGUIButton>("CurrentCameraButton", 100.f, 20.f);
	m_vecWidget.push_back(m_CurrentCamera);
	m_CurrentCamera->SetFont("DefaultFont");
	m_CurrentCamera->SetClickCallback<CIMGUICameraComponent>(this, &CIMGUICameraComponent::CurrentCameraButtonClick);

	m_Header->WidgetPush(m_vecWidget);
	m_vecWidget.push_back(m_Header);

	return true;
}

void CIMGUICameraComponent::Update(float DeltaTime)
{
}

void CIMGUICameraComponent::CurrentCameraButtonClick()
{
	CCameraManager* CameraManager=m_Camera->GetScene()->GetCameraManager();
	CameraManager->SetCurrentCamera(m_Camera->GetName());
	float Zoom = m_Camera->GetCameraZoom();
	Camera_Type Type = m_Camera->GetCameraType();
	float Left = m_Camera->GetCameraLeft();
	float Bottom = m_Camera->GetCameraBottom();
	Vector2 Min = m_Camera->GetMin();
	Vector2 Max = m_Camera->GetMax();
	m_CameraMinX->SetFloat(Min.x);
	m_CameraMinY->SetFloat(Min.y);
	m_CameraMaxX->SetFloat(Max.x);
	m_CameraMaxY->SetFloat(Max.x);
}

void CIMGUICameraComponent::InputZoom()
{
	float Zoom = m_CameraZoom->GetValueFloat();

	m_Camera->SetCameraZoom(Zoom);

}

void CIMGUICameraComponent::InputMinX()
{
	float x = m_CameraMinX->GetValueFloat();
	float y = m_CameraMinY->GetValueFloat();
	m_Camera->SetMin(x, y);
}

void CIMGUICameraComponent::InputMinY()
{
	float x = m_CameraMinX->GetValueFloat();
	float y = m_CameraMinY->GetValueFloat();
	m_Camera->SetMin(x, y);
}

void CIMGUICameraComponent::InputMaxX()
{
	float x = m_CameraMaxX->GetValueFloat();
	float y = m_CameraMaxY->GetValueFloat();
	m_Camera->SetMax(x, y);
}

void CIMGUICameraComponent::InputMaxY()
{
	float x = m_CameraMaxX->GetValueFloat();
	float y = m_CameraMaxY->GetValueFloat();
	m_Camera->SetMax(x, y);
}



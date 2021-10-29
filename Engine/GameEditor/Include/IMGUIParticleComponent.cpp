#include "pch.h"
#include "IMGUIParticleComponent.h"
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
#include "IMGUICheckBox.h"
#include "IMGUICollapsingHeader.h"
CIMGUIParticleComponent::CIMGUIParticleComponent()
{
}

CIMGUIParticleComponent::~CIMGUIParticleComponent()
{
}

void CIMGUIParticleComponent::InfoUpdate(CGameObject* Object)
{
	m_Object = Object;
	m_ObjectName->SetText(m_Object->GetName().c_str());
	m_EnableCheckBox->SetCheck(m_Object->IsEnable());
	Enable(true);
}

bool CIMGUIParticleComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ObjectInfo");




	Text = m_Owner->AddWidget<CIMGUIText>("##Title");
	Text->SetText("ObjectInfo");
	m_vecWidget.push_back(Text);

#pragma region Name
	Text = m_Owner->AddWidget<CIMGUIText>("##ObjectName1");
	Text->SetText("ObjectName");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ObjectName = m_Owner->AddWidget<CIMGUITextInput>("##ObjectName", 100.f, 20.f);
	m_ObjectName->SetInputCallback<CIMGUIParticleComponent>(this, &CIMGUIParticleComponent::InputObjectName);
	m_ObjectName->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_vecWidget.push_back(m_ObjectName);

#pragma endregion
	m_EnableCheckBox = m_Owner->AddWidget<CIMGUICheckBox>("Enable", 300.f, 20.f);
	m_EnableCheckBox->SetCheckCallback<CIMGUIParticleComponent>(this, &CIMGUIParticleComponent::EnableCheckBoxClick);
	m_vecWidget.push_back(m_EnableCheckBox);


	m_Header->WidgetPush(m_vecWidget);
	m_vecWidget.push_back(m_Header);
	return true;
}

void CIMGUIParticleComponent::Update(float DeltaTime)
{
}

void CIMGUIParticleComponent::InputObjectName()
{
	m_Object->SetName(m_ObjectName->GetTextMultibyte());
}

void CIMGUIParticleComponent::EnableCheckBoxClick(bool Enable)
{
	m_Object->Enable(Enable);
}

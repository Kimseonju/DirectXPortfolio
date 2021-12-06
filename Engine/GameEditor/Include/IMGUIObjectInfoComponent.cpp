#include "pch.h"
#include "IMGUIObjectInfoComponent.h"
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
CIMGUIObjectInfoComponent::CIMGUIObjectInfoComponent()
{
}

CIMGUIObjectInfoComponent::~CIMGUIObjectInfoComponent()
{
}

void CIMGUIObjectInfoComponent::UpdateInfo(CGameObject* Object)
{
	m_Object = Object;
	if (!m_Object)
	{
		return;
	}
	m_ObjectName->SetText(m_Object->GetName().c_str());
	m_EnableCheckBox->SetCheck(m_Object->IsEnable());

	Client_Class_Type ClassType = m_Object->GetClassType();
	Client_Object_Type ObjectType = m_Object->GetObjectType();
	Client_Enemy_Type EnemyType = m_Object->GetEnemyType();
	m_CreateEnemyEffect->SetCheck(m_Object->GetCreateEnemyEffect());
	m_CreateEnemyOrder->SetInt(m_Object->GetCreateEnemyOrder());
	Door_Dir DoorDir = m_Object->GetDoorDir();
	m_ClassType->SetPrevName((int)ClassType);
	m_ObjectType->SetPrevName((int)ObjectType);
	m_EnemyType->SetPrevName((int)EnemyType);
	m_DoorDir->SetPrevName((int)DoorDir);

	Enable(true);

}

bool CIMGUIObjectInfoComponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("ObjectInfo");




	Text = m_Owner->AddWidget<CIMGUIText>("##Title");
	Text->SetText("Info");
	m_vecWidget.push_back(Text);

#pragma region Name
	Text = m_Owner->AddWidget<CIMGUIText>("ObjectName1");
	Text->SetText("Name");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ObjectName = m_Owner->AddWidget<CIMGUITextInput>("##ObjectName", 100.f, 20.f);
	m_ObjectName->SetInputCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::InputObjectName);
	m_ObjectName->AddFlag(ImGuiInputTextFlags_EnterReturnsTrue);
	m_vecWidget.push_back(m_ObjectName);

#pragma endregion

#pragma region ClassType
	Text = m_Owner->AddWidget<CIMGUIText>("ClassType");
	Text->SetText("ClassType");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ClassType = m_Owner->AddWidget<CIMGUIComboBox>("##ClassTypeCombo", 100.f, 20.f);

	m_ClassType->AddItem("Default");
	m_ClassType->AddItem("Object");
	m_ClassType->AddItem("Enemy");
	m_ClassType->AddItem("Boss");
	m_ClassType->AddItem("Spawn");
	m_ClassType->AddItem("End");
	m_ClassType->SetSelectCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::ClassTypeComboCallback);
	m_vecWidget.push_back(m_ClassType);

#pragma endregion

#pragma region ObjectType
	Text = m_Owner->AddWidget<CIMGUIText>("ObjectType");
	Text->SetText("ObjectType");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ObjectType = m_Owner->AddWidget<CIMGUIComboBox>("##ObjectTypeCombo", 100.f, 20.f);
	m_ObjectType->AddItem("MainDoor");
	m_ObjectType->AddItem("House");
	m_ObjectType->AddItem("Door");
	m_ObjectType->AddItem("Torch");
	m_ObjectType->AddItem("BossTorch");
	m_ObjectType->AddItem("Shop");
	m_ObjectType->AddItem("Restaurant");
	m_ObjectType->AddItem("TresureBox");
	m_ObjectType->AddItem("BossTresureBox");
	m_ObjectType->AddItem("Gate");
	m_ObjectType->AddItem("End");

	m_ObjectType->SetSelectCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::ObjectTypeComboCallback);
	m_vecWidget.push_back(m_ObjectType);

#pragma endregion

#pragma region EnemyType
	Text = m_Owner->AddWidget<CIMGUIText>("Enemy1");
	Text->SetText("Enemy");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_EnemyType = m_Owner->AddWidget<CIMGUIComboBox>("##EnemyTypeCombo", 100.f, 20.f);
	m_EnemyType->AddItem("SmallSkel_Sword");
	m_EnemyType->AddItem("SmallSkel_Bow");
	m_EnemyType->AddItem("Ghost");
	m_EnemyType->AddItem("Banshee");
	m_EnemyType->AddItem("Giant_Red");
	m_EnemyType->AddItem("Minotaurs");
	m_EnemyType->AddItem("Ovibos");
	m_EnemyType->AddItem("Big_Normal");
	m_EnemyType->AddItem("End");
	m_EnemyType->SetSelectCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::EnemyTypeComboCallback);


	m_vecWidget.push_back(m_EnemyType);
#pragma endregion



	
#pragma region Doordir
	Text = m_Owner->AddWidget<CIMGUIText>("DoorDir1");
	Text->SetText("DoorDir");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_DoorDir = m_Owner->AddWidget<CIMGUIComboBox>("##DoorDirCombo", 100.f, 20.f);
	m_DoorDir->AddItem("Door_Left");
	m_DoorDir->AddItem("Door_Up");
	m_DoorDir->AddItem("Door_Right");
	m_DoorDir->AddItem("Door_Down");
	m_DoorDir->SetSelectCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::DoorDirComboCallback);

	m_vecWidget.push_back(m_DoorDir);

#pragma endregion

	m_EnableCheckBox = m_Owner->AddWidget<CIMGUICheckBox>("Enable", 300.f, 20.f);
	m_EnableCheckBox->SetCheckCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::EnableCheckBoxClick);
	m_vecWidget.push_back(m_EnableCheckBox);




	m_CreateEnemyEffect = m_Owner->AddWidget<CIMGUICheckBox>("CreateEnemyEffect", 300.f, 20.f);
	m_CreateEnemyEffect->SetCheckCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::CreateEnemyEffectCheckBoxClick);
	m_vecWidget.push_back(m_CreateEnemyEffect);
	Text = m_Owner->AddWidget<CIMGUIText>("Scale");
	Text->SetFont("DefaultFont");
	Text->SetText("Scale");

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_CreateEnemyOrder = m_Owner->AddWidget<CIMGUITextInput>("##CreateEnemyOrder", 100.f, 20.f);
	m_CreateEnemyOrder->SetNumberInt(true);
	m_CreateEnemyOrder->SetInt(0);
	m_CreateEnemyOrder->SetInputCallback<CIMGUIObjectInfoComponent>(this, &CIMGUIObjectInfoComponent::InputCreateEnemyOrder);
	m_vecWidget.push_back(m_CreateEnemyOrder);


	m_Header->WidgetPush(m_vecWidget);

	return true;
}

void CIMGUIObjectInfoComponent::Update(float DeltaTime)
{
	Client_Class_Type ClassType=m_Object->GetClassType();
	Client_Object_Type ObjectType = m_Object->GetObjectType();
	Client_Enemy_Type EnemyType = m_Object->GetEnemyType();
	Door_Dir DoorDir = m_Object->GetDoorDir();
	m_ClassType->SetPrevName((int)ClassType);
	m_ObjectType->SetPrevName((int)ObjectType);
	m_EnemyType->SetPrevName((int)EnemyType);
	m_DoorDir->SetPrevName((int)DoorDir);
}

void CIMGUIObjectInfoComponent::InputObjectName()
{
	m_Object->SetName(m_ObjectName->GetTextMultibyte());
}

void CIMGUIObjectInfoComponent::EnableCheckBoxClick(bool Enable)
{
	m_Object->Enable(Enable);
}

void CIMGUIObjectInfoComponent::ClassTypeComboCallback(int SelectIndex, const char* Item)
{
	m_Object->SetClassType((Client_Class_Type)SelectIndex);
}

void CIMGUIObjectInfoComponent::ObjectTypeComboCallback(int SelectIndex, const char* Item)
{
	m_Object->SetObjectType((Client_Object_Type)SelectIndex);
}

void CIMGUIObjectInfoComponent::EnemyTypeComboCallback(int SelectIndex, const char* Item)
{
	m_Object->SetEnemyType((Client_Enemy_Type)SelectIndex);
}

void CIMGUIObjectInfoComponent::DoorDirComboCallback(int SelectIndex, const char* Item)
{
	m_Object->SetDoorDir((Door_Dir)SelectIndex);
}

void CIMGUIObjectInfoComponent::CreateEnemyEffectCheckBoxClick(bool Enable)
{
	m_Object->SetCreateEnemyEffect(Enable);
}

void CIMGUIObjectInfoComponent::InputCreateEnemyOrder()
{
	m_Object->SetCreateEnemyOrder(m_CreateEnemyOrder->GetValueInt());
}

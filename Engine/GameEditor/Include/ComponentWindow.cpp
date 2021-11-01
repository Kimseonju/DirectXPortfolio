#include "pch.h"
#include "ComponentWindow.h"
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

#include "IMGUITransformComponent.h"
#include "IMGUISpriteComponent.h"
#include "IMGUICollider2DComponent.h"
#include "IMGUICameraComponent.h"
#include "ObjectWindow.h"
#include "InspectorWindow.h"
#include <Component/Collider.h>
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/Camera.h"
#include "Component/SpringArm.h"
#include "Component/SpringArm2D.h"
CComponentWindow::CComponentWindow():
	m_SelectComponent(nullptr),
	m_CreateComponentIndex(-1)
{
}

CComponentWindow::~CComponentWindow()
{

}

bool CComponentWindow::Init()
{
	m_ComponentListBox = AddWidget<CIMGUIListBox>("ComponentListBox", 300.f, 100.f);
	m_ComponentListBox->SetBorder(false);
	m_ComponentListBox->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::ComponentListCallback);


	m_ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");

	CIMGUIButton* CreateObjButton = AddWidget<CIMGUIButton>("컴포넌트생성", 100.f, 30.f);

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CComponentWindow>(this, &CComponentWindow::CreateComponentButtonClick);
	return true;
}

void CComponentWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CComponentWindow::ComponentListCallback(int SelectIndex, const char* Item)
{
	m_SelectComponentIndex = SelectIndex;
	CGameObject* Obj=m_ObjectWindow->GetSelectObject();
	if (Obj)
	{
		m_SelectComponent =Obj->FindSceneComponent(Item);

		CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
		InspectorWindow->AllComponentClose();

		ComponentUpdateInfo(m_SelectComponent);
	}
}

void CComponentWindow::ComponentUpdateInfo(CSceneComponent* Compoonent)
{
	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->AllComponentClose();
	SceneComponent_Type Type = Compoonent->GetSceneComponentType();

	switch (Type)
	{
	case SceneComponent_Type::Scene:
	{
		InspectorWindow->TransformUpdate(Compoonent);
		break;
	}
	case SceneComponent_Type::Primitive:
	{
		InspectorWindow->TransformUpdate(Compoonent);
		CPrimitiveComponent* PrimitiveComponent = (CPrimitiveComponent*)Compoonent;
		PrimitiveComponent_ClassType ClassType = PrimitiveComponent->GetPrimitiveClassType();

		switch (ClassType)
		{
		case PrimitiveComponent_ClassType::Default:
			break;
		case PrimitiveComponent_ClassType::Mesh:
			break;
		case PrimitiveComponent_ClassType::Sprite:
			InspectorWindow->SpriteUpdate((CSpriteComponent*)Compoonent);
			break;
		case PrimitiveComponent_ClassType::Collider:
			InspectorWindow->ColliderUpdate((CCollider*)Compoonent);

		case PrimitiveComponent_ClassType::Particle:
			break;
		case PrimitiveComponent_ClassType::Widget:
			break;
		case PrimitiveComponent_ClassType::TileMap:
			break;
		}
		break;
	}
	case SceneComponent_Type::Camera:
	{
		CCamera* CameraComponent = (CCamera*)Compoonent;
		InspectorWindow->TransformUpdate(Compoonent);
		InspectorWindow->CameraUpdate(CameraComponent);
		break;
	}
	case SceneComponent_Type::SpringArm:
		InspectorWindow->TransformUpdate(Compoonent);
		break;
	}

}

void CComponentWindow::ComponentComboCallback(int SelectIndex, const char* Item)
{
	if (!m_ObjectWindow->GetSelectObject())
		return;

	m_CreateComponentIndex = SelectIndex;
}

void CComponentWindow::CreateComponentButtonClick()
{
	if (!m_ObjectWindow->GetSelectObject())
		return;
	// 이름을 지정하기 위한 Popup 창을 열어준다.
	CIMGUIText* Text = AddPopupWidget<CIMGUIText>("CreateComponent");
	Text->SetText("CreateComponent");

	Text = AddPopupWidget<CIMGUIText>("CreateComponent");
	Text->SetText("ComponentName");

	CIMGUISameLine* SameLine = AddPopupWidget<CIMGUISameLine>("SameLine");
	m_NameInput = AddPopupWidget<CIMGUITextInput>("##NameInput", 100.f, 20.f);

	CIMGUIComboBox* ComponentCombo = AddPopupWidget<CIMGUIComboBox>("##ComponentCombo", 100.f, 100.f);

	ComponentCombo->SetSelectCallback<CComponentWindow>(this, &CComponentWindow::ComponentComboCallback);

	ComponentCombo->AddItem("Scene");
	ComponentCombo->AddItem("Sprite");
	ComponentCombo->AddItem("Box2D");
	ComponentCombo->AddItem("Circle");
	ComponentCombo->AddItem("Pixel");
	ComponentCombo->AddItem("Camera");
	ComponentCombo->AddItem("SpringArm");
	ComponentCombo->AddItem("SpringArm2D");


	CIMGUIButton* CreateObjButton = AddPopupWidget<CIMGUIButton>("생성");
	CreateObjButton->SetFont("DefaultFont");
	CreateObjButton->SetClickCallback<CComponentWindow>(this, &CComponentWindow::InputComponentPopupButton);

	m_CreateComponentIndex = -1;
	SetPopupTitle("Component");
	EnableModalPopup();
}

void CComponentWindow::InputComponentPopupButton()
{
	if (!m_ObjectWindow->GetSelectObject())
		return;
	if (m_CreateComponentIndex == -1)
		return;
	CSceneComponent* NewComponent = nullptr;

	const char* Name = m_NameInput->GetTextMultibyte();

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	switch ((Component_Class_Type)m_CreateComponentIndex)
	{
	case Component_Class_Type::Scene:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSceneComponent>(Name);
		break;
	case Component_Class_Type::Sprite:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSpriteComponent>(Name);
		break;
	case Component_Class_Type::Box2D:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CColliderBox2D>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::Circle:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CColliderCircle>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::Pixel:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CColliderPixel>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::Camera:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CCamera>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::SpringArm:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSpringArm>(Name);
		break;
	case Component_Class_Type::SpringArm2D:
		NewComponent = m_ObjectWindow->GetSelectObject()->CreateSceneComponent<CSpringArm2D>(Name);
		break;
	}

	m_ComponentListBox->AddItem(NewComponent->GetName().c_str());
	if (m_ObjectWindow->GetSelectObject()->GetRootComponent()->GetName() == "DefaultRoot")
	{
		m_ObjectWindow->GetSelectObject()->SetRootComponent(NewComponent);
		SetSelectComponent(NewComponent);

		std::vector<std::string>	vecName;

		m_ObjectWindow->GetSelectObject()->GetComponentName(vecName);

		m_ComponentListBox->Clear();

		size_t	Size = vecName.size();


		for (size_t i = 0; i < vecName.size(); ++i)
		{
			AddItem(vecName[i].c_str());
		}

		CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
		InspectorWindow->AllComponentClose();
		ComponentUpdateInfo(NewComponent);


	}
	else
	{
		m_ObjectWindow->GetSelectObject()->GetRootComponent()->AddChild(NewComponent);
	}

	NewComponent->SetRelativePos(10.f, 20.f, 30.f);

	ClosePopup();
}

void CComponentWindow::CloseComponentPopupButton()
{
	ClosePopup();
}

void CComponentWindow::Clear()
{
	m_ComponentListBox->Clear();
}

void CComponentWindow::AddItem(const char* Item)
{
	m_ComponentListBox->AddItem(Item);
}

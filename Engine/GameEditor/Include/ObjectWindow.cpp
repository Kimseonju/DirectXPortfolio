#include "pch.h"
#include "ObjectWindow.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "GameObject.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderPixel.h"
#include "Component/Camera.h"
#include "Component/SpringArm.h"
#include "Component/SpringArm2D.h"
#include "DetailWindow.h"
#include "IMGUIManager.h"
#include "InspectorWindow.h"
#include "PrefabWindow.h"

CObjectWindow::CObjectWindow() :
	m_CreateObjectCount(0),
	m_SelectObjectIndex(-1),
	m_SelectComponentIndex(-1),
	m_CreateComponentIndex(-1)
{
}

CObjectWindow::~CObjectWindow()
{
}

bool CObjectWindow::Init()
{
	m_ObjListBox = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);

	m_ObjListBox->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ListCallback);

	m_ComponentListBox = AddWidget<CIMGUIListBox>("ComponentListBox", 300.f, 100.f);

	m_ComponentListBox->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ComponentListCallback);


	CIMGUIButton* CreateObjButton = AddWidget<CIMGUIButton>("오브젝트생성");

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::CreateObjectButtonClick);

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");


	CreateObjButton = AddWidget<CIMGUIButton>("오브젝트삭제");

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::DeleteObjectButtonClick);


	CreateObjButton = AddWidget<CIMGUIButton>("컴포넌트생성");

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::CreateComponentButtonClick);


	CIMGUIButton* SaveBtn = AddWidget<CIMGUIButton>("저장", 100.f, 40.f);
	SaveBtn->SetFont("DefaultFont");
	SaveBtn->SetClickCallback<CObjectWindow>(this, &CObjectWindow::SaveButton);

	CIMGUISameLine* Line2 = AddWidget<CIMGUISameLine>("");

	CIMGUIButton* LoadBtn = AddWidget<CIMGUIButton>("불러오기", 100.f, 40.f);
	LoadBtn->SetFont("DefaultFont");
	LoadBtn->SetClickCallback<CObjectWindow>(this, &CObjectWindow::LoadButton);


	CIMGUIButton* Prefab = AddWidget<CIMGUIButton>("AddPrefab", 100.f, 40.f);
	Prefab->SetFont("DefaultFont");
	Prefab->SetClickCallback<CObjectWindow>(this, &CObjectWindow::AddPrefab);


	return true;
}

void CObjectWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	m_ObjListBox->Clear();
	for (size_t i = 0; i < m_VecObject.size(); i++)
	{
		m_ObjListBox->AddItem(m_VecObject[i]->GetName().c_str());
	}
	
}


void CObjectWindow::ListCallback(int SelectIndex, const char* Item)
{
	m_SelectObjectIndex = SelectIndex;
	m_SelectComponent = nullptr;

	std::string SelectName = Item;

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	m_SelectObject = m_VecObject[m_SelectObjectIndex];

	// 가지고 있는 컴포넌트의 이름을 얻어온다.
	std::vector<std::string>	vecName;

	m_SelectObject->GetComponentName(vecName);

	m_ComponentListBox->Clear();
	
	size_t	Size = vecName.size();

	//CDetailWindow* DetailWindow = (CDetailWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("DetailWindow");
	//DetailWindow->Open();
	//DetailWindow->SetPosition(m_SelectObject->GetWorldPos());
	//DetailWindow->SetRotation(m_SelectObject->GetWorldRotation());
	//DetailWindow->SetScale(m_SelectObject->GetWorldScale());
	//DetailWindow->SetPivot(m_SelectObject->GetPivot());

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->AllComponentClose();
	for (size_t i = 0; i < vecName.size(); ++i)
	{
		m_ComponentListBox->AddItem(vecName[i].c_str());
	}

	CSceneComponent* Compoonent = m_SelectObject->FindSceneComponent(vecName[0]);
	InspectorWindow->TransformUpdate(Compoonent);
	InspectorWindow->ObjectUpdateInfo(m_SelectObject);

}

void CObjectWindow::ComponentListCallback(int SelectIndex, const char* Item)
{
	m_SelectComponentIndex = SelectIndex;

	m_SelectComponent = m_SelectObject->FindSceneComponent(Item);

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->AllComponentClose();
	
	ComponentUpdateInfo(m_SelectComponent.Get());
}

void CObjectWindow::ComponentComboCallback(int SelectIndex, const char* Item)
{
	if (!m_SelectObject)
		return;

	m_CreateComponentIndex = SelectIndex;
	
}

void CObjectWindow::CreateObjectButtonClick()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	char	ObjName[256] = {};

	sprintf_s(ObjName, "GameObject_%d", m_CreateObjectCount);

	++m_CreateObjectCount;

	CGameObject* Obj = Scene->SpawnObject<CGameObject>(ObjName);
	m_VecObject.push_back(Obj);
	
}

void CObjectWindow::DeleteObjectButtonClick()
{
	size_t Size=m_VecObject.size();
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		if ((*iter) == m_SelectObject)
		{
			m_VecObject.erase(iter);
			m_SelectObject->Active(false);
			m_SelectObject = nullptr;
			break;
		}
	}
	
	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->AllComponentClose();
}

void CObjectWindow::CreateComponentButtonClick()
{
	if (!m_SelectObject)
		return;
	// 이름을 지정하기 위한 Popup 창을 열어준다.
	CIMGUIText* Text=AddPopupWidget<CIMGUIText>("CreateComponent");
	Text->SetText("CreateComponent");

	Text = AddPopupWidget<CIMGUIText>("CreateComponent");
	Text->SetText("ComponentName");

	CIMGUISameLine* SameLine = AddPopupWidget<CIMGUISameLine>("SameLine");
	m_NameInput = AddPopupWidget<CIMGUITextInput>("##NameInput", 100.f, 20.f);

	CIMGUIComboBox* ComponentCombo = AddPopupWidget<CIMGUIComboBox>("##ComponentCombo", 100.f, 100.f);

	ComponentCombo->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ComponentComboCallback);

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

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::InputComponentPopupButton);


	SetPopupTitle("Component");
	EnableModalPopup();
}


void CObjectWindow::InputComponentPopupButton()
{
	if (!m_SelectObject)
		return;
	if (m_CreateComponentIndex==-1)
		return;
	CSceneComponent* NewComponent = nullptr;

	const char* Name = m_NameInput->GetTextMultibyte();

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	switch ((Component_Class_Type)m_CreateComponentIndex)
	{
	case Component_Class_Type::Scene:
		NewComponent = m_SelectObject->CreateSceneComponent<CSceneComponent>(Name);
		break;
	case Component_Class_Type::Sprite:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpriteComponent>(Name);
		break;
	case Component_Class_Type::Box2D:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderBox2D>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::Circle:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderCircle>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::Pixel:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderPixel>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::Camera:
		NewComponent = m_SelectObject->CreateSceneComponent<CCamera>(Name);
		NewComponent->Start();
		break;
	case Component_Class_Type::SpringArm:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpringArm>(Name);
		break;
	case Component_Class_Type::SpringArm2D:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpringArm2D>(Name);
		break;
	}

	m_ComponentListBox->AddItem(NewComponent->GetName().c_str());
	if (m_SelectObject->GetRootComponent()->GetName() == "DefaultRoot")
	{
		m_SelectObject->SetRootComponent(NewComponent);
		m_SelectComponent = NewComponent;

		std::vector<std::string>	vecName;

		m_SelectObject->GetComponentName(vecName);

		m_ComponentListBox->Clear();

		size_t	Size = vecName.size();


		for (size_t i = 0; i < vecName.size(); ++i)
		{
			m_ComponentListBox->AddItem(vecName[i].c_str());
		}

		CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
		InspectorWindow->AllComponentClose();
		ComponentUpdateInfo(m_SelectComponent.Get());

		
	}
	else
	{
		m_SelectObject->GetRootComponent()->AddChild(NewComponent);
	}

	NewComponent->SetRelativePos(10.f, 20.f, 30.f);

	ClosePopup();
}

void CObjectWindow::AddPrefab()
{
	if (!m_SelectObject)
	{
		return;
	}
	if (!m_PrefabWindow)
	{
		m_PrefabWindow = (CPrefabWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("PrefabWindow");
	}
	m_PrefabWindow->AddPrefab(m_SelectObject);
}

void CObjectWindow::ComponentUpdateInfo(CSceneComponent* Compoonent)
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


void CObjectWindow::SetPosX(float x)
{
	if (!m_SelectComponent)
		return;

	Vector3	Pos = m_SelectComponent->GetWorldPos();
	Pos.x = x;

	m_SelectComponent->SetWorldPos(Pos);
}

void CObjectWindow::SetPosY(float y)
{
	if (!m_SelectComponent)
		return;

	Vector3	Pos = m_SelectComponent->GetWorldPos();
	Pos.y = y;

	m_SelectComponent->SetWorldPos(Pos);
}

void CObjectWindow::SetPosZ(float z)
{
	if (!m_SelectComponent)
		return;

	Vector3	Pos = m_SelectComponent->GetWorldPos();
	Pos.z = z;

	m_SelectComponent->SetWorldPos(Pos);
}

void CObjectWindow::SetRotX(float x)
{
	if (!m_SelectComponent)
		return;

	
	Vector3	Rot = m_SelectComponent->GetWorldRotation();
	Rot.x = x;

	m_SelectComponent->SetWorldRotation(Rot);
}

void CObjectWindow::SetRotY(float y)
{
	if (!m_SelectComponent)
		return;

	Vector3	Rot = m_SelectComponent->GetWorldRotation();
	Rot.y = y;

	m_SelectComponent->SetWorldRotation(Rot);
}

void CObjectWindow::SetRotZ(float z)
{
	if (!m_SelectComponent)
		return;

	Vector3	Rot = m_SelectComponent->GetWorldRotation();
	Rot.z = z;

	m_SelectComponent->SetWorldRotation(Rot);
}

void CObjectWindow::SetScaleX(float x)
{
	if (!m_SelectComponent)
		return;

	Vector3	Scale = m_SelectComponent->GetWorldScale();
	Scale.x = x;

	m_SelectComponent->SetWorldScale(Scale);
}

void CObjectWindow::SetScaleY(float y)
{
	if (!m_SelectComponent)
		return;

	Vector3	Scale = m_SelectComponent->GetWorldScale();
	Scale.y = y;

	m_SelectComponent->SetWorldScale(Scale);
}

void CObjectWindow::SetScaleZ(float z)
{
	if (!m_SelectComponent)
		return;

	Vector3	Scale = m_SelectComponent->GetWorldScale();
	Scale.z = z;

	m_SelectComponent->SetWorldScale(Scale);
}

void CObjectWindow::SetPivotX(float x)
{
	if (!m_SelectComponent)
		return;

	Vector3	Scale = m_SelectComponent->GetPivot();
	Scale.x = x;

	m_SelectComponent->SetPivot(Scale);
}

void CObjectWindow::SetPivotY(float y)
{
	if (!m_SelectComponent)
		return;

	Vector3	Scale = m_SelectComponent->GetPivot();
	Scale.y = y;

	m_SelectComponent->SetPivot(Scale);
}

void CObjectWindow::SetPivotZ(float z)
{
	if (!m_SelectComponent)
		return;

	Vector3	Scale = m_SelectComponent->GetPivot();
	Scale.z = z;

	m_SelectComponent->SetPivot(Scale);
}

void CObjectWindow::SaveButton()
{
	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(FALSE, TEXT("*.txt"), TEXT(""), OFN_OVERWRITEPROMPT,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();

		AfxMessageBox(Path);
	}
}

void CObjectWindow::LoadButton()
{
	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(TRUE, TEXT("*.txt"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();

		AfxMessageBox(Path);
	}
}
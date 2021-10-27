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
	m_ObjListBox = AddWidget<CIMGUIListBox>("ListBox", 300.f, 100.f);

	m_ObjListBox->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ListCallback);

	m_ComponentListBox = AddWidget<CIMGUIListBox>("ComponentListBox", 300.f, 100.f);

	m_ComponentListBox->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ComponentListCallback);


	CIMGUIButton* CreateObjButton = AddWidget<CIMGUIButton>("������Ʈ����");

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::CreateObjectButtonClick);

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	CIMGUIComboBox* ComponentCombo = AddWidget<CIMGUIComboBox>("ComponentCombo", 300.f, 100.f);

	ComponentCombo->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ComponentComboCallback);

	ComponentCombo->AddItem("Scene");
	ComponentCombo->AddItem("Sprite");
	ComponentCombo->AddItem("Circle");
	ComponentCombo->AddItem("Box2D");
	ComponentCombo->AddItem("Circle");
	ComponentCombo->AddItem("Pixel");
	ComponentCombo->AddItem("Camera");
	ComponentCombo->AddItem("SpringArm");
	ComponentCombo->AddItem("SpringArm2D");


	CIMGUIButton* SaveBtn = AddWidget<CIMGUIButton>("����", 100.f, 40.f);
	SaveBtn->SetFont("DefaultFont");
	SaveBtn->SetClickCallback<CObjectWindow>(this, &CObjectWindow::SaveButton);

	CIMGUISameLine* Line2 = AddWidget<CIMGUISameLine>("");

	CIMGUIButton* LoadBtn = AddWidget<CIMGUIButton>("�ҷ�����", 100.f, 40.f);
	LoadBtn->SetFont("DefaultFont");
	LoadBtn->SetClickCallback<CObjectWindow>(this, &CObjectWindow::LoadButton);

	return true;
}

void CObjectWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}


void CObjectWindow::ListCallback(int SelectIndex, const char* Item)
{
	m_SelectObjectIndex = SelectIndex;

	std::string SelectName = Item;

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	m_SelectObject = Scene->FindObject(SelectName);

	// ������ �ִ� ������Ʈ�� �̸��� ���´�.
	std::vector<std::string>	vecName;

	m_SelectObject->GetComponentName(vecName);

	m_ComponentListBox->Clear();

	size_t	Size = vecName.size();

	CDetailWindow* DetailWindow = (CDetailWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("DetailWindow");
	DetailWindow->Open();
	DetailWindow->SetPosition(m_SelectObject->GetWorldPos());
	DetailWindow->SetRotation(m_SelectObject->GetWorldRotation());
	DetailWindow->SetScale(m_SelectObject->GetWorldScale());
	DetailWindow->SetPivot(m_SelectObject->GetPivot());

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	for (size_t i = 0; i < vecName.size(); ++i)
	{
		m_ComponentListBox->AddItem(vecName[i].c_str());

		if (vecName[i] == "Sprite")
		{
			CSpriteComponent* Component= (CSpriteComponent *)m_SelectObject->FindSceneComponent(vecName[i]);
			InspectorWindow->SpriteUpdate(Component);
		}
		else if (vecName[i] == "Box2D")
		{

		}
		else if (vecName[i] == "Circle")
		{

		}
		else if (vecName[i] == "Pixel")
		{

		}
		else if (vecName[i] == "Camera")
		{

		}
		else if (vecName[i] == "SpringArm")
		{

		}
		else if (vecName[i] == "SpringArm2D")
		{

		}
		else if (vecName[i] == "ParticleSystem")
		{

		}
	}
}

void CObjectWindow::ComponentListCallback(int SelectIndex, const char* Item)
{
	m_SelectComponentIndex = SelectIndex;

	m_SelectComponent = m_SelectObject->FindSceneComponent(Item);


	Vector3	Pos = m_SelectComponent->GetWorldPos();
	Vector3	Rot = m_SelectComponent->GetWorldRotation();
	Vector3	Scale = m_SelectComponent->GetWorldScale();
	Vector3	Pivot = m_SelectComponent->GetPivot();

	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");

	if (InspectorWindow)
	{
		InspectorWindow->TransformUpdate(m_SelectComponent);
	}
	
}

void CObjectWindow::ComponentComboCallback(int SelectIndex, const char* Item)
{
	if (!m_SelectObject || !m_SelectComponent)
		return;

	m_CreateComponentIndex = SelectIndex;
	CSceneComponent* NewComponent = nullptr;

	switch ((Component_Class_Type)m_CreateComponentIndex)
	{
	case Component_Class_Type::Scene:
		NewComponent = m_SelectObject->CreateSceneComponent<CSceneComponent>("Scene");
		break;
	case Component_Class_Type::Sprite:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpriteComponent>("Sprite");
		break;
	case Component_Class_Type::Box2D:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
		break;
	case Component_Class_Type::Circle:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderCircle>("ColliderCircle");
		break;
	case Component_Class_Type::Pixel:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderPixel>("ColliderPixel");
		break;
	case Component_Class_Type::Camera:
		NewComponent = m_SelectObject->CreateSceneComponent<CCamera>("Camera");
		break;
	case Component_Class_Type::SpringArm:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpringArm>("SpringArm");
		break;
	case Component_Class_Type::SpringArm2D:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpringArm2D>("SpringArm2D");
		break;
	}

	m_ComponentListBox->AddItem(NewComponent->GetName().c_str());

	m_SelectComponent->AddChild(NewComponent);

	NewComponent->SetRelativePos(10.f, 20.f, 30.f);

	ClosePopup();

	//// �̸��� �����ϱ� ���� Popup â�� �����ش�.
	//m_NameInput = AddPopupWidget<CIMGUITextInput>("NameInput");
	//
	//CIMGUIButton* NameButton = AddPopupWidget<CIMGUIButton>("NameButton");
	//
	//NameButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::InputNamePopupButton);
	//
	//SetPopupTitle("Component Name");
	//EnableModalPopup();
}

void CObjectWindow::CreateObjectButtonClick()
{
	CScene* Scene = CSceneManager::GetInst()->GetScene();

	char	ObjName[256] = {};

	sprintf_s(ObjName, "GameObject_%d", m_CreateObjectCount);

	++m_CreateObjectCount;

	CGameObject* Obj = Scene->SpawnObject<CGameObject>(ObjName);
	Obj->SetWorldScale(100.f, 100.f, 1.f);
	m_ObjListBox->AddItem(ObjName);
}

void CObjectWindow::InputNamePopupButton()
{
	if (!m_SelectObject)
		return;

	// �̸��� ���´�.
	const char* Name = m_NameInput->GetTextMultibyte();

	CSceneComponent* NewComponent = nullptr;

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
		break;
	case Component_Class_Type::Circle:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderCircle>(Name);
		break;
	case Component_Class_Type::Pixel:
		NewComponent = m_SelectObject->CreateSceneComponent<CColliderPixel>(Name);
		break;
	case Component_Class_Type::Camera:
		NewComponent = m_SelectObject->CreateSceneComponent<CCamera>(Name);
		break;
	case Component_Class_Type::SpringArm:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpringArm>(Name);
		break;
	case Component_Class_Type::SpringArm2D:
		NewComponent = m_SelectObject->CreateSceneComponent<CSpringArm2D>(Name);
		break;
	}

	m_ComponentListBox->AddItem(Name);

	m_SelectComponent->AddChild(NewComponent);

	NewComponent->SetRelativePos(10.f, 20.f, 30.f);

	ClosePopup();
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
	static TCHAR Filter[] = TEXT("�ؽ�Ʈ ����(*.txt)|*.txt|�������(*.*)|*.*||");
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
	static TCHAR Filter[] = TEXT("�ؽ�Ʈ ����(*.txt)|*.txt|�������(*.*)|*.*||");
	CFileDialog	dlg(TRUE, TEXT("*.txt"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();

		AfxMessageBox(Path);
	}
}
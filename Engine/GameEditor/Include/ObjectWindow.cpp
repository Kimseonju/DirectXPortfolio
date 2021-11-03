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
#include "DetailWindow.h"
#include "IMGUIManager.h"
#include "InspectorWindow.h"
#include "PrefabWindow.h"
#include <Scene/Scene.h>
#include <Scene/SceneCollision.h>
#include <Scene/SceneManager.h>
#include "Component/Collider.h"
#include "ComponentWindow.h"

CObjectWindow::CObjectWindow() :
	m_CreateObjectCount(0),
	m_CreateComponentIndex(-1)
{
}

CObjectWindow::~CObjectWindow()
{
}



bool CObjectWindow::Init()
{
	m_ObjListBox = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);
	m_ObjListBox->SetBorder(false);
	m_ObjListBox->SetSelectCallback<CObjectWindow>(this, &CObjectWindow::ListCallback);


	CIMGUIButton* CreateObjButton = AddWidget<CIMGUIButton>("오브젝트생성",100.f,30.f);

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::CreateObjectButtonClick);

	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");


	CreateObjButton = AddWidget<CIMGUIButton>("오브젝트삭제", 100.f, 30.f);

	CreateObjButton->SetFont("DefaultFont");

	CreateObjButton->SetClickCallback<CObjectWindow>(this, &CObjectWindow::DeleteObjectButtonClick);




	CIMGUIButton* SaveBtn = AddWidget<CIMGUIButton>("저장", 100.f, 30.f);
	SaveBtn->SetFont("DefaultFont");
	SaveBtn->SetClickCallback<CObjectWindow>(this, &CObjectWindow::SaveButton);

	CIMGUISameLine* Line2 = AddWidget<CIMGUISameLine>("");

	CIMGUIButton* LoadBtn = AddWidget<CIMGUIButton>("불러오기", 100.f, 30.f);
	LoadBtn->SetFont("DefaultFont");
	LoadBtn->SetClickCallback<CObjectWindow>(this, &CObjectWindow::LoadButton);

	 
	CIMGUIButton* Prefab = AddWidget<CIMGUIButton>("AddPrefab", 100.f, 30.f);
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

void CObjectWindow::DeleteColliderMouseObject()
{
	CCollider* Collision=m_Scene->GetCollisionManager()->GetMouseCollisionCollider_Edit();
	if (Collision)
	{
		CGameObject* Obj=Collision->GetOwner();

		size_t Size = m_VecObject.size();
		auto iter = m_VecObject.begin();
		auto iterEnd = m_VecObject.end();
		for (; iter != iterEnd; ++iter)
		{
			if ((*iter) == Obj)
			{
				m_VecObject.erase(iter);
				Obj->Active(false);
				break;
			}
		}
		CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
		InspectorWindow->AllComponentClose();
	}
}

void CObjectWindow::ListCallback(int SelectIndex, const char* Item)
{
	m_SelectObjectIndex = SelectIndex;
	if (!m_ComponentWindow)
	{
		m_ComponentWindow = (CComponentWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ComponentWindow");
	}
	m_ComponentWindow->SetSelectComponent(nullptr);

	std::string SelectName = Item;

	CScene* Scene = CSceneManager::GetInst()->GetScene();

	m_SelectObject = m_VecObject[m_SelectObjectIndex];

	// 가지고 있는 컴포넌트의 이름을 얻어온다.
	std::vector<std::string>	vecName;

	m_SelectObject->GetComponentName(vecName);

	m_ComponentWindow->Clear();
	
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
		m_ComponentWindow->AddItem(vecName[i].c_str());
	}

	CSceneComponent* Compoonent = m_SelectObject->FindSceneComponent(vecName[0]);
	InspectorWindow->TransformUpdate(Compoonent);
	InspectorWindow->ObjectUpdateInfo(m_SelectObject);

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
	m_ComponentWindow->Clear();
	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->ObjectUpdateInfo(nullptr);
	InspectorWindow->AllComponentClose();
}

void CObjectWindow::DeleteAllObject()
{
	size_t Size = m_VecObject.size();
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Active(false);
		
	}
	
	m_SelectObject = nullptr;
	m_ComponentWindow->Clear();
	m_VecObject.clear();
	CInspectorWindow* InspectorWindow = (CInspectorWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("InspectorWindow");
	InspectorWindow->ObjectUpdateInfo(nullptr);
	InspectorWindow->AllComponentClose();
}

void CObjectWindow::SaveAllObject(FILE* pFile)
{
	size_t Size = m_VecObject.size();
	fwrite(&Size, sizeof(size_t), 1, pFile);
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Save(pFile);
	}

}

void CObjectWindow::ClientSaveObject(FILE* pFile)
{
	size_t Size = m_VecObject.size();
	fwrite(&Size, sizeof(size_t), 1, pFile);
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (; iter != iterEnd; ++iter)
	{
		(*iter)->ClientSave(pFile);
	}
}

void CObjectWindow::LoadAllObject(FILE* pFile)
{
	DeleteAllObject();
	size_t Size;
	fread(&Size, sizeof(size_t), 1, pFile);
	auto iter = m_VecObject.begin();
	auto iterEnd = m_VecObject.end();
	for (size_t i = 0; i < Size; i++)
	{
		CreateObjectButtonClick();
		CGameObject* Obj = m_VecObject[m_VecObject.size() - 1];
		Obj->Load(pFile);

	}
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


void CObjectWindow::SetPosX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Pos = m_ComponentWindow->GetSelectComponent()->GetWorldPos();
	Pos.x = x;

	m_ComponentWindow->GetSelectComponent()->SetWorldPos(Pos);
}

void CObjectWindow::SetPosY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Pos = m_ComponentWindow->GetSelectComponent()->GetWorldPos();
	Pos.y = y;

	m_ComponentWindow->GetSelectComponent()->SetWorldPos(Pos);
}

void CObjectWindow::SetPosZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Pos = m_ComponentWindow->GetSelectComponent()->GetWorldPos();
	Pos.z = z;

	m_ComponentWindow->GetSelectComponent()->SetWorldPos(Pos);
}

void CObjectWindow::SetRotX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	
	Vector3	Rot = m_ComponentWindow->GetSelectComponent()->GetWorldRotation();
	Rot.x = x;

	m_ComponentWindow->GetSelectComponent()->SetWorldRotation(Rot);
}

void CObjectWindow::SetRotY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Rot = m_ComponentWindow->GetSelectComponent()->GetWorldRotation();
	Rot.y = y;

	m_ComponentWindow->GetSelectComponent()->SetWorldRotation(Rot);
}

void CObjectWindow::SetRotZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Rot = m_ComponentWindow->GetSelectComponent()->GetWorldRotation();
	Rot.z = z;

	m_ComponentWindow->GetSelectComponent()->SetWorldRotation(Rot);
}

void CObjectWindow::SetScaleX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetWorldScale();
	Scale.x = x;

	m_ComponentWindow->GetSelectComponent()->SetWorldScale(Scale);
}

void CObjectWindow::SetScaleY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetWorldScale();
	Scale.y = y;

	m_ComponentWindow->GetSelectComponent()->SetWorldScale(Scale);
}

void CObjectWindow::SetScaleZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetWorldScale();
	Scale.z = z;

	m_ComponentWindow->GetSelectComponent()->SetWorldScale(Scale);
}

void CObjectWindow::SetPivotX(float x)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetPivot();
	Scale.x = x;

	m_ComponentWindow->GetSelectComponent()->SetPivot(Scale);
}

void CObjectWindow::SetPivotY(float y)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetPivot();
	Scale.y = y;

	m_ComponentWindow->GetSelectComponent()->SetPivot(Scale);
}

void CObjectWindow::SetPivotZ(float z)
{
	if (!m_ComponentWindow->GetSelectComponent())
		return;

	Vector3	Scale = m_ComponentWindow->GetSelectComponent()->GetPivot();
	Scale.z = z;

	m_ComponentWindow->GetSelectComponent()->SetPivot(Scale);
}

void CObjectWindow::SaveButton()
{
	if (!m_SelectObject.Get())
	{
		return;
	}
	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(FALSE, TEXT("*.txt"), TEXT(""), OFN_OVERWRITEPROMPT,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();
		m_SelectObject->SaveFullPath(Path);
	}
}

void CObjectWindow::LoadButton()
{



	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(TRUE, TEXT("*.txt"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CreateObjectButtonClick();
		CGameObject* Obj = m_VecObject[m_VecObject.size() - 1];
		CString	Path = dlg.GetPathName();
		Obj->LoadFullPath(Path);
	}
}
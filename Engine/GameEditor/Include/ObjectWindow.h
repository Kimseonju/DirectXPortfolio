#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
#include "Component/SceneComponent.h"
class CObjectWindow :
	public CIMGUIWindow
{
public:
	CObjectWindow();
	virtual ~CObjectWindow();

private:
	unsigned int	m_CreateObjectCount;
	class CIMGUIListBox* m_ObjListBox;
	std::vector<CSharedPtr<CGameObject>> m_VecObject;
	class CIMGUIListBox* m_ComponentListBox;
	CSharedPtr<CGameObject> m_SelectObject;
	int		m_SelectObjectIndex;
	CSharedPtr<CSceneComponent> m_SelectComponent;
	int		m_SelectComponentIndex;
	int		m_CreateComponentIndex;

	class CIMGUITextInput* m_NameInput;
	class CPrefabWindow* m_PrefabWindow;
public:

	CGameObject* GetSelectObject()
	{
		return m_SelectObject.Get();
	}
	void AddObject(CGameObject* Obj)
	{
		m_VecObject.push_back(Obj);
	}
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void ListCallback(int SelectIndex, const char* Item);
	void ComponentListCallback(int SelectIndex, const char* Item);
	void ComponentComboCallback(int SelectIndex, const char* Item);
	void CreateObjectButtonClick();
	void DeleteObjectButtonClick();
	void CreateComponentButtonClick();
	void InputComponentPopupButton();

	void AddPrefab();
	void ComponentUpdateInfo(CSceneComponent* Compoonent);
public:
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);

	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	void SetPivotX(float x);
	void SetPivotY(float y);
	void SetPivotZ(float z);
	void SaveButton();
	void LoadButton();
};

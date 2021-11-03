#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
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

	CSharedPtr<CGameObject> m_SelectObject;
	int		m_SelectObjectIndex;
	int		m_CreateComponentIndex;

	class CPrefabWindow* m_PrefabWindow;
	class CComponentWindow* m_ComponentWindow;
	class CScene* m_Scene;
public:
	void SetComponentWindow(class CComponentWindow* Window)
	{
		m_ComponentWindow = Window;
	}
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
	void SetScene(class CScene* Scene)
	{
		m_Scene = Scene;
	}
	void DeleteColliderMouseObject();
public:
	void ListCallback(int SelectIndex, const char* Item);
	void CreateObjectButtonClick();
	void DeleteObjectButtonClick();
	void DeleteAllObject();
	void SaveAllObject(FILE* pFile);
	void ClientSaveObject(FILE* pFile);
	void LoadAllObject(FILE* pFile);
	void AddPrefab();
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

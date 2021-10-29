#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
class CPrefabWindow :
	public CIMGUIWindow
{
public:
	CPrefabWindow();
	virtual ~CPrefabWindow();

private:

	class CIMGUIListBox* m_ObjListBox;
	CSharedPtr<CGameObject> m_SelectPrefab;
	std::vector<CSharedPtr<CGameObject>> m_VecPrefab;
public:
	void AddPrefab(CGameObject* Prefab)
	{
		m_VecPrefab.push_back(Prefab);
	}

	CGameObject* GetSelectObject()
	{
		return m_SelectPrefab.Get();
	}
public:

	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void ListCallback(int SelectIndex, const char* Item);
};

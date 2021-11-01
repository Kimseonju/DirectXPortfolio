#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
#include "Component/SceneComponent.h"
class CComponentWindow :
	public CIMGUIWindow
{
public:
	CComponentWindow();
	virtual ~CComponentWindow();

private:
	class CIMGUIListBox* m_ComponentListBox;
	CSceneComponent* m_SelectComponent;
	class CIMGUITextInput* m_NameInput;
	int		m_SelectComponentIndex;
	class CObjectWindow* m_ObjectWindow;
	int		m_CreateComponentIndex;
public:
	CSceneComponent* GetSelectComponent()
	{
		return m_SelectComponent;
	}


	void SetSelectComponent(CSceneComponent* Component)
	{
		m_SelectComponent=Component;
	}
	virtual bool Init();
	virtual void Update(float DeltaTime);
public:
	void ComponentListCallback(int SelectIndex, const char* Item);
	void ComponentUpdateInfo(CSceneComponent* Compoonent);
	void ComponentComboCallback(int SelectIndex, const char* Item);
	void CreateComponentButtonClick();
	void InputComponentPopupButton();
	void CloseComponentPopupButton();
public:
	void Clear();
	void AddItem(const char* Item);
};

#pragma once
#include "IMGUIWidgetComponent.h"
#include "GameObject.h"
class CIMGUIObjectInfoComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUIObjectInfoComponent();
	virtual ~CIMGUIObjectInfoComponent();

private:
	class CIMGUITextInput* m_ObjectName;
	class CIMGUIComboBox* m_ClassType;
	class CIMGUIComboBox* m_ObjectType;
	class CIMGUIComboBox* m_EnemyType;
	class CIMGUICheckBox* m_EnableCheckBox;

	CSharedPtr<CGameObject> m_Object;

public:
	void UpdateInfo(CGameObject* Object);
	bool IsObject() const
	{
		if (!m_Object)
			return false;
		return true;
	}
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputObjectName();
	void EnableCheckBoxClick(bool Enable);
	void ClassTypeComboCallback(int SelectIndex, const char* Item);
	void ObjectTypeComboCallback(int SelectIndex, const char* Item);
	void EnemyTypeComboCallback(int SelectIndex, const char* Item);

};

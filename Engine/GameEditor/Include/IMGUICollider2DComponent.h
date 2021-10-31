#pragma once
#include "IMGUIWidgetComponent.h"
class CIMGUICollider2DComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUICollider2DComponent();
	virtual ~CIMGUICollider2DComponent();

private:
	class CIMGUIText* m_ColliderType;
	class CIMGUIText* m_ColliderSpace;
	class CIMGUIComboBox* m_ColliderProfileCombo;


	class CIMGUIDrag* m_ColliderLengthX;
	class CIMGUIDrag* m_ColliderLengthY;
	

	class CIMGUIDrag* m_ColliderRadius;

	class CCollider* m_Collider;

public:
	void UpdateInfo(CCollider* Collider);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Enable(bool Enable);

public:
	void InputLength();
	void InputRadius();
	void ProfileComboCallback(int SelectIndex, const char* Item);
};

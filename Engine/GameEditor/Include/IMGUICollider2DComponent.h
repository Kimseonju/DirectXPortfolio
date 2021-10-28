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

	class CCollider* m_Collider;

public:
	void InfoUpdate(CCollider* Collider);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

};

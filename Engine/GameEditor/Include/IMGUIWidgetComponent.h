#pragma once
#include "IMGUIWindow.h"
#include "IMGUIWidget.h"

class CIMGUIWidgetComponent
{
	
public:
	CIMGUIWidgetComponent();
	virtual ~CIMGUIWidgetComponent();

protected:
	CIMGUIWindow* m_Owner;
	std::vector<CIMGUIWidget*> m_vecWidget;
	class CIMGUICollapsingHeader* m_Header;
public:
	virtual bool Init();
	virtual void Enable(bool Enable);
	void SetOwner(CIMGUIWindow* Owner)
	{
		m_Owner = Owner;
	}
};


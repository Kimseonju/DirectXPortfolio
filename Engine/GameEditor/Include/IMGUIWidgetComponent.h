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

public:
	void Enable(bool Enable);
	void SetOwner(CIMGUIWindow* Owner)
	{
		m_Owner = Owner;
	}
};


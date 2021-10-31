#pragma once
#include "IMGUIWidget.h"
class CIMGUITab :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUITab();
	virtual ~CIMGUITab();
	std::vector<CIMGUIWidget*> m_vecWidget;
public:
	void WidgetPush(CIMGUIWidget* Widget);
	void WidgetPush(std::vector<CIMGUIWidget*>& Widget);
public:
	virtual bool Init();
	virtual void Render();
};

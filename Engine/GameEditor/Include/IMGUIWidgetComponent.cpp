#include "pch.h"
#include "IMGUIWidgetComponent.h"
#include "IMGUIWidget.h"

CIMGUIWidgetComponent::CIMGUIWidgetComponent():
	m_Owner(nullptr)
{
}

CIMGUIWidgetComponent::~CIMGUIWidgetComponent()
{
}

void CIMGUIWidgetComponent::Enable(bool Enable)
{
	size_t Size = m_vecWidget.size();
	for (size_t i = 0; i < Size; i++)
	{
		m_vecWidget[i]->Enable(Enable);
	}
}

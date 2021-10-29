#include "pch.h"
#include "IMGUIWidgetComponent.h"
#include "IMGUIWidget.h"
#include <IMGUICollapsingHeader.h>
CIMGUIWidgetComponent::CIMGUIWidgetComponent():
	m_Owner(nullptr)
{
}

CIMGUIWidgetComponent::~CIMGUIWidgetComponent()
{
}

bool CIMGUIWidgetComponent::Init()
{

	return true;
}

void CIMGUIWidgetComponent::Enable(bool Enable)
{
	size_t Size = m_vecWidget.size();
	for (size_t i = 0; i < Size; i++)
	{
		m_vecWidget[i]->Enable(Enable);
	}
}

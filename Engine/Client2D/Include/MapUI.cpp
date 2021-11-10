#include "MapUI.h"

CMapUI::CMapUI() 
{
}

CMapUI::CMapUI(const CMapUI& widget)
{
}

CMapUI::~CMapUI()
{
}

bool CMapUI::Init()
{
	CWidgetWindow::Init();


	return true;
}

void CMapUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CMapUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMapUI::Render()
{
	CWidgetWindow::Render();
}

CMapUI* CMapUI::Clone()
{
	return new CMapUI(*this);
}

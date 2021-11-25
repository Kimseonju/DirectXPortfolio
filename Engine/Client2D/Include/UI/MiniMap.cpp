
#include "MiniMap.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include <UI/Text.h>
CMiniMap::CMiniMap()
{
}


CMiniMap::~CMiniMap()
{
}

bool CMiniMap::Init()
{
	CWidgetWindow::Init();
	SetZOrder(UI_ZOrder::PlayerUI);

	
	return true;
}

void CMiniMap::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

}

void CMiniMap::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CMiniMap::Render()
{
	CWidgetWindow::Render();
}

CMiniMap* CMiniMap::Clone()
{
	return new CMiniMap(*this);
}


#include "MiniMap.h"
#include "MiniMapWidget.h"
CMiniMap::CMiniMap()

{
}


CMiniMap::~CMiniMap()
{
}

void CMiniMap::TileUpdate()
{
	m_MiniMapWidget->TileUpdate();
}

bool CMiniMap::Init()
{
	CWidgetWindow::Init();
	m_MiniMapWidget = CreateWidget<CMiniMapWidget>("MiniMapWidget");
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

void CMiniMap::PushMiniMapInfoTile(Vector2 Pos, Vector2 Size, Vector4 Color, Vector4 EmvColor, float Opacity)
{
	m_MiniMapWidget->PushMiniMapInfoTile(Pos, Size, Color, EmvColor, Opacity);
}

void CMiniMap::PushMiniMapInfoObject(Vector2 Pos, Vector2 Size, Vector4 Color, Vector4 EmvColor, float Opacity)
{

	m_MiniMapWidget->PushMiniMapInfoObject(Pos, Size, Color, EmvColor, Opacity);
}
void CMiniMap::PushMiniMapInfoEnemy(Vector2 Pos, Vector2 Size, Vector4 Color, Vector4 EmvColor, float Opacity)
{

	m_MiniMapWidget->PushMiniMapInfoEnemy(Pos, Size, Color, EmvColor, Opacity);
}

void CMiniMap::ObjectClear()
{
	m_MiniMapWidget->ObjectClear();
}

void CMiniMap::Clear()
{

	m_MiniMapWidget->Clear();
}

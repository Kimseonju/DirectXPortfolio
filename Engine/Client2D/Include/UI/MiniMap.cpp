
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
}

bool CMiniMap::Init()
{
	CWidgetWindow::Init();
	m_MiniMapWidget = CreateWidget<CMiniMapWidget>("MiniMapWidget");
	m_MiniMapWidget->SetPos(100.f, 100.f);
	m_MiniMapWidget->SetSize(200.f, 200.f);
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

void CMiniMap::PushMiniMapInfoTile(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity)
{
	m_MiniMapWidget->PushMiniMapInfoTile(Pos, Color, EmvColor, Opacity);
}

void CMiniMap::PushMiniMapInfoObject(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity)
{

	m_MiniMapWidget->PushMiniMapInfoObject(Pos, Color, EmvColor, Opacity);
}
void CMiniMap::PushMiniMapInfoEnemy(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity)
{

	m_MiniMapWidget->PushMiniMapInfoEnemy(Pos, Color, EmvColor, Opacity);
}

void CMiniMap::ObjectClear()
{
	m_MiniMapWidget->ObjectClear();
}

void CMiniMap::Clear()
{

	m_MiniMapWidget->Clear();
}

void CMiniMap::SetMesh(const std::string& Name)
{

	m_MiniMapWidget->SetMesh(Name);
}
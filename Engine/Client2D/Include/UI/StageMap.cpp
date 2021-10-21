
#include "StageMap.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Stage.h"
#include "../Room.h"
CStageMap::CStageMap() :
	m_StageUpdate(true)
{
}

CStageMap::CStageMap(const CStageMap& widget) :
	CWidgetWindow(widget)
{
}

CStageMap::~CStageMap()
{
}

bool CStageMap::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector2 Pos;


	m_MapBase1_0 = CreateWidget<CImage>("MapBase1_0");

	m_MapBase1_0->SetPos(0.f, RS.Height-32.f*4);
	m_MapBase1_0->SetTexture("MapBase1_0", TEXT("UI/map/MapBase1_0.png"));
	m_MapBase1_0->SetSize(320.f*4, 32.f*4);

	m_MapBase1_1 = CreateWidget<CImage>("MapBase1_1");
			   
	m_MapBase1_1->SetPos((float)RS.Width/2.f, 150.f*2);
	m_MapBase1_1->SetPivot(0.5f, 0.5f);
	m_MapBase1_1->SetTexture("MapBase1_1", TEXT("UI/map/MapBase1_1.png"));
	m_MapBase1_1->SetSize(260.f * 4, 132.f * 4);





	return true;
}

void CStageMap::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	CreateStage();
}

void CStageMap::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CStageMap::Render()
{
	CWidgetWindow::Render();
}

CStageMap* CStageMap::Clone()
{
	return new CStageMap(*this);
}

void CStageMap::CreateStage()
{
	if (!m_StageUpdate)
	{
		return;
	}

	m_StageUpdate = false;
	Resolution RS = CDevice::GetInst()->GetResolution();
	for (int i = 0; i < 20; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			CRoom* room = m_Stage->GetRooms(i, j);
			if (room == nullptr)
				continue;

			m_MapBase1_0 = CreateWidget<CImage>("Room");
			m_MapBase1_0->SetPos((float)RS.Width/2.f+(26.f * ((float)i-4.f)*4.f), (float)RS.Height / 2.f+(26.f*((float)j-4.f)*4.f));
			m_MapBase1_0->SetTexture("Room", TEXT("UI/map/Room.png"));
			m_MapBase1_0->SetSize(24.f * 4, 24.f * 4);
		}
	}
}

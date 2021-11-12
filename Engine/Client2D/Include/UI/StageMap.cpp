
#include "StageMap.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include <UI/Text.h>
CStageMap::CStageMap() :
	m_StageUpdate(true),
	m_MapBase1_0(nullptr),
	m_MapBase1_1(nullptr),
	m_BackCloud(nullptr),
	m_Stage(nullptr)
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
	std::vector<std::vector<StageInfo>>& Info = CStageManager::GetInst()->GetvecStageInfo();
	CStageManager::GetInst()->GetCurPos();
	int Size = CStageManager::GetInst()->GetMapSize();

	SetZOrder(UI_ZOrder::MapUI);
	for (int x= 0; x < Size; ++x)
	{
		for (int y = 0; y < Size; ++y)
		{
			if (Info[x][y].StageType == StageType::None)
				continue;
			std::string str1 = std::to_string(x);
			std::string str2 = std::to_string(y);
			CImage* Base=CreateWidget<CImage>("Base"+str1+str2);
			Base->SetPos(30.f * 4.f *x+300.f, 30.f * 4.f *y+100.f);
			Base->SetTexture("BaseStage", TEXT("UI/map/Room.png"));
			Base->SetSize(24.f*4.f, 24.f * 4.f);
			Base->SetCollision(false);
			if (!Info[x][y].Wall[(int)WallDir::Left])
			{
				std::string str3 = std::to_string((int)WallDir::Left);
				CImage* Arrow = CreateWidget<CImage>("Arrow" + str1 + str2+ str3);
				Vector2 Pos = Base->GetPos();
				Pos += Base->GetSize() / 2.f;
				Pos.x -= 40.f;
				Arrow->SetPos(Pos);
				Arrow->SetTexture("Room", TEXT("object/door/openEffect.png"));
				Arrow->SetSize(10.f * 4.f, 10.f);
				Arrow->SetCollision(false);
			}
			if (!Info[x][y].Wall[(int)WallDir::Up])
			{
				std::string str3 = std::to_string((int)WallDir::Up);
				CImage* Arrow = CreateWidget<CImage>("Arrow" + str1 + str2 + str3);
				Vector2 Pos = Base->GetPos();
				Pos += Base->GetSize() / 2.f;
				Pos.y += 40.f;
				Arrow->SetPos(Pos);
				Arrow->SetTexture("Room", TEXT("object/door/openEffect.png"));
				Arrow->SetSize(10.f, 10.f * 4.f);
				Arrow->SetCollision(false);
			}
			if (!Info[x][y].Wall[(int)WallDir::Right])
			{

				std::string str3 = std::to_string((int)WallDir::Right);
				CImage* Arrow = CreateWidget<CImage>("Arrow" + str1 + str2 + str3);
				Vector2 Pos = Base->GetPos();
				Pos += Base->GetSize() / 2.f;
				Pos.x += 40.f;
				Arrow->SetPos(Pos);
				
				Arrow->SetTexture("Room", TEXT("object/door/openEffect.png"));
				Arrow->SetSize(10.f * 4.f, 10.f);
				Arrow->SetCollision(false);
			}
			if (!Info[x][y].Wall[(int)WallDir::Down])
			{

				std::string str3 = std::to_string((int)WallDir::Down);
				CImage* Arrow = CreateWidget<CImage>("Arrow" + str1 + str2 + str3);
				Vector2 Pos = Base->GetPos();
				Pos += Base->GetSize() / 2.f;
				Pos.y -= 40.f;
				Arrow->SetPos(Pos);
				Arrow->SetTexture("Room", TEXT("object/door/openEffect.png"));
				Arrow->SetSize(10.f, 10.f * 4.f);
				Arrow->SetCollision(false);
			}
		}
	}

	m_PosX = CreateWidget<CText>("PosX");
	m_PosX->SetPos(100.f, 100.f);
	m_PosX->SetCollision(false);
	m_PosY = CreateWidget<CText>("PosY");
	m_PosY->SetPos(200.f, 100.f);
	m_PosY->SetCollision(false);
	m_Name1 = CreateWidget<CText>("Name");
	m_Name1->SetPos(300.f, 100.f);
	m_Name1->SetCollision(false);


	m_MapBase1_0 = CreateWidget<CImage>("MapBase1_0");

	m_MapBase1_0->SetPos(0.f, RS.Height-32.f*4);
	m_MapBase1_0->SetTexture("MapBase1_0", TEXT("UI/map/MapBase1_0.png"));
	m_MapBase1_0->SetSize(320.f*4, 32.f*4);
	m_MapBase1_0->SetCollision(false);

	m_MapBase1_1 = CreateWidget<CImage>("MapBase1_1");
			   
	m_MapBase1_1->SetPos((float)RS.Width/2.f, 150.f*2);
	m_MapBase1_1->SetPivot(0.5f, 0.5f);
	m_MapBase1_1->SetTexture("MapBase1_1", TEXT("UI/map/MapBase1_1.png"));
	m_MapBase1_1->SetSize(260.f * 4, 132.f * 4);
	m_MapBase1_1->SetCollision(false);





	return true;
}

void CStageMap::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	Vector2 Pos=CStageManager::GetInst()->GetCurPos();
	m_PosX->SetText(CA2T(std::to_string(Pos.x).c_str()));
	m_PosY->SetText(CA2T(std::to_string(Pos.y).c_str()));
	std::string Name = CStageManager::GetInst()->GetCurName();
	m_Name1->SetText(CA2T(Name.c_str()));
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
	//for (int i = 0; i < 20; ++i)
	//{
	//	for (int j = 0; j < 20; ++j)
	//	{
	//		CRoom* room = m_Stage->GetRooms(i, j);
	//		if (room == nullptr)
	//			continue;
	//
	//		m_MapBase1_0 = CreateWidget<CImage>("Room");
	//		m_MapBase1_0->SetPos((float)RS.Width/2.f+(26.f * ((float)i-4.f)*4.f), (float)RS.Height / 2.f+(26.f*((float)j-4.f)*4.f));
	//		m_MapBase1_0->SetTexture("Room", TEXT("UI/map/Room.png"));
	//		m_MapBase1_0->SetSize(24.f * 4, 24.f * 4);
	//	}
	//}
}


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
	m_Stage(nullptr),
	m_CurMapTimer(0.f),
	m_CurMapTimerMax(0.3f),
	m_CurMapEnable(false),
	m_GateIn(false)
{
}


CStageMap::~CStageMap()
{
	size_t Size = m_MapInfoBase.size();
	for (size_t i = 0; i < Size; ++i)
	{
		m_MapInfoBase[i].clear();
	}
	m_MapInfoBase.clear();
}

void CStageMap::Enable(bool bEnable)
{
	CWidgetWindow::Enable(bEnable);
	if (!bEnable)
	{
		m_GateMoveLine->Enable(false);
		m_GateIn = false;
	}
}

bool CStageMap::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector2 Pos;
	std::vector<std::vector<StageInfo>>& Info = CStageManager::GetInst()->GetvecStageInfo();
	int Size = CStageManager::GetInst()->GetMapSize();
	m_GateMoveLine = CreateWidget<CImage>("GateMoveLine");
	m_GateMoveLine->SetSize(10.f, 10.f);
	m_GateMoveLine->SetColorTint(46.f / 255.f, 248.f / 255.f, 233.f / 255.f, 1.f);
	m_GateMoveLine->SetZOrder(3);
	m_GateMoveLine->SetCollision(false);
	m_MapInfoBase.resize(Size);
	for (int i = 0; i < Size; ++i)
	{
		m_MapInfoBase[i].resize(Size);
	}

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
			Base->SetPos(30.f * 4.f *x+300.f, 30.f * 4.f *y+ 80.f);
			Base->SetTexture("BaseStage", TEXT("UI/map/Room.png"));
			Base->SetSize(24.f*4.f, 24.f * 4.f);
			Base->SetCollision(false);
			Base->SetZOrder(2);
			Base->SetColorTint(1.f, 1.f, 1.f, 1.f);
			switch (Info[x][y].StageType)
			{
			case StageType::Base:
				break;
			case StageType::Start:
				Base->SetColorTint(1.f, 0.f, 0.f, 1.f);
				break;
			case StageType::End:
				Base->SetColorTint(0.f, 0.f, 1.f, 1.f);
				break;
			case StageType::Shop:
				Base->SetColorTint(0.f, 1.f, 0.f, 1.f);
				break;
			case StageType::Restaurant:
				Base->SetColorTint(0.f, 1.f, 1.f, 1.f);
				break;
			}
			m_MapBase.push_back(Base);

			MapInfoBase InfoBase;
			InfoBase.MapBase = Base;
			m_MapInfoBase[x][y] = InfoBase;




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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
			}
		}
	}

	m_MapBase1_0 = CreateWidget<CImage>("MapBase1_0");

	m_MapBase1_0->SetPos(0.f, RS.Height-32.f*4);
	m_MapBase1_0->SetTexture("MapBase1_0", TEXT("UI/map/MapBase1_0.png"));
	m_MapBase1_0->SetSize(320.f*4, 32.f*4);
	m_MapBase1_0->SetCollision(false);
	m_MapBase1_0->SetZOrder(1);

	m_MapBase1_1 = CreateWidget<CImage>("MapBase1_1");
			   
	m_MapBase1_1->SetPos((float)RS.Width/2.f, 150.f*2);
	m_MapBase1_1->SetPivot(0.5f, 0.5f);
	m_MapBase1_1->SetTexture("MapBase1_1", TEXT("UI/map/MapBase1_1.png"));
	m_MapBase1_1->SetSize(260.f * 4, 132.f * 4);
	m_MapBase1_1->SetCollision(false);
	m_MapBase1_1->SetZOrder(1);

	m_CurMapImage = CreateWidget<CImage>("CurMapImage");
	m_CurMapImage->SetSize(24.f * 4.f, 24.f * 4.f);
	m_CurMapImage->SetTexture("MapEffect", TEXT("object/door/MapEffect.png"));
	m_CurMapImage->SetColorTint(0.f, 1.f, 0.f, 1.f);
	m_CurMapImage->SetCollision(false);
	m_CurMapImage->SetZOrder(0);
	CImage* Base = CreateWidget<CImage>("Base11");
	Base->SetPos(0.f, 0.f);
	Base->SetColorTint(0.f, 0.f, 0.f, 0.4f);
	Base->SetSize(1280.f, 720.f);
	Base->SetCollision(false);
	Base->SetZOrder(0);

	return true;
}

void CStageMap::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	Vector2 Pos = CStageManager::GetInst()->GetCurPos();
	m_CurMapTimer += DeltaTime;
	m_CurMapImage->SetPos(30.f * 4.f * Pos.x + 300.f, 30.f * 4.f * Pos.y + 80.f);

	if (m_CurMapTimer >= m_CurMapTimerMax)
	{
		m_CurMapTimer -= m_CurMapTimerMax;
		m_CurMapImage->Enable(m_CurMapEnable);
		m_CurMapEnable = !m_CurMapEnable;
	}
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

void CStageMap::StageMove()
{
	CStage* Stage=CStageManager::GetInst()->GetCurStage();
	Vector2 CurPos = CStageManager::GetInst()->GetCurPos();

	if (m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].Move)
	{
		return;
	}
	m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].Move = true;

	//게이트가 있다면
	int IconCount = 0;
	CGateButton* Gate = nullptr;
	if (Stage->IsGate())
	{
		//아이콘제작
		Gate = CreateWidget<CGateButton>("GateButton");
		Gate->SetSize(34.f, 28.f);

		Gate->SetStateTexture(Button_State::Normal, "Worm", TEXT("UI/Map/Worm.png"));
		Gate->SetStateTexture(Button_State::MouseOn, "Worm_Selected", TEXT("UI/Map/Worm_Selected.png"));
		Gate->SetStateTexture(Button_State::Click, "Worm_Selected", TEXT("UI/Map/Worm_Selected.png"));
		Gate->SetMouseOnCallback<CStageMap>(this, &CStageMap::MosueOnCallback);
		Gate->SetClickCallback<CStageMap>(this, &CStageMap::ClickCallback);
		Gate->SetMouseOutCallback<CStageMap>(this, &CStageMap::MouseOutCallback);
		Gate->SetZOrder(4);
		Gate->SetPivot(0.5f, 0.5f);
		Gate->SetCurPos(CurPos);
		m_vecGateButton.push_back(Gate);
		m_MapIcon.push_back(Gate);
		m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].GateButton = Gate;
		IconCount++;

	}
	//다른것들 아이콘 제작
	StageType Type=Stage->GetStageType();
	CImage* Image = nullptr;
	switch (Type)
	{
	case StageType::Start:
		Image= CreateWidget<CImage>("StartIcon");
		Image->SetTexture("EnteranceIcon", TEXT("UI/Map/Enterance.png"));
		IconCount++;
		break;
	case StageType::End:
		Image = CreateWidget<CImage>("ExitIcon");
		Image->SetTexture("ExitIcon", TEXT("UI/Map/Exit.png"));
		IconCount++;
		break;
	case StageType::Shop:
		Image = CreateWidget<CImage>("ShopIcon");
		Image->SetTexture("ShopIcon", TEXT("UI/Map/Shop.png"));
		IconCount++;
		break;
	case StageType::Restaurant:
		Image = CreateWidget<CImage>("RestaurantIcon");
		Image->SetTexture("FoodIcon", TEXT("UI/Map/Food.png"));
		IconCount++;
		break;
	}
	if (Image)
	{
		Image->SetSize(34.f, 28.f);
		Image->SetZOrder(4);
		Image->SetPivot(0.5f, 0.5f);
		Image->SetCollision(false);
		m_MapIcon.push_back(Image);
	}
	CImage* Base = m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].MapBase;
	Vector2 Pos = Base->GetPos();
	Vector2 Size = Base->GetSize();
	Pos =Pos+ Size / 2.f;
	if (IconCount == 1)
	{//둘중에 하나
		if (Gate)
			Gate->SetPos(Pos);
		if (Image)
			Image->SetPos(Pos);
	}
	else if (IconCount == 2)
	{
		//게이트랑 일반아이콘 둘다있음
		Vector2 IconSize=Gate->GetSize();
		Pos.x -= IconSize.x / 2.f;
		Gate->SetPos(Pos);
		Pos.x += IconSize.x;
		Image->SetPos(Pos);
	}
}

void CStageMap::MapUpdate()
{
	for (size_t i = 0; i < m_MapBase.size(); i++)
	{
		m_MapBase[i]->Active(false);
	}
	m_MapBase.clear();
	for (size_t i = 0; i < m_MapArrow.size(); i++)
	{
		m_MapArrow[i]->Active(false);
	}
	m_MapArrow.clear();

	for (size_t i = 0; i < m_MapIcon.size(); i++)
	{
		m_MapIcon[i]->Active(false);
	}
	m_MapIcon.clear();
	//Icon과 겹쳐잇음
	m_vecGateButton.clear();
	std::vector<std::vector<StageInfo>>& Info = CStageManager::GetInst()->GetvecStageInfo();

	SetZOrder(UI_ZOrder::MapUI);
	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 1; ++y)
		{
			if (Info[x][y].StageType == StageType::None)
				continue;
			std::string str1 = std::to_string(x);
			std::string str2 = std::to_string(y);
			CImage* Base = CreateWidget<CImage>("Base" + str1 + str2);
			Base->SetPos(30.f * 4.f * x + 300.f, 30.f * 4.f * y + 80.f);
			Base->SetTexture("BaseStage", TEXT("UI/map/Room.png"));
			Base->SetSize(24.f * 4.f, 24.f * 4.f);
			Base->SetCollision(false);
			Base->SetZOrder(2);
			switch (Info[x][y].StageType)
			{
			case StageType::Base:
				break;
			case StageType::Start:
				Base->SetColorTint(1.f, 0.f, 0.f, 1.f);
				break;
			case StageType::End:
				Base->SetColorTint(0.f, 0.f, 1.f, 1.f);
				break;
			case StageType::Shop:
				Base->SetColorTint(0.f, 1.f, 0.f, 1.f);
				break;
			case StageType::Restaurant:
				Base->SetColorTint(0.f, 1.f, 1.f, 1.f);
				break;
			}
			m_MapBase.push_back(Base);

			MapInfoBase InfoBase;
			InfoBase.MapBase = Base;
			m_MapInfoBase[x][y] = InfoBase;

			if (!Info[x][y].Wall[(int)WallDir::Left])
			{
				std::string str3 = std::to_string((int)WallDir::Left);
				CImage* Arrow = CreateWidget<CImage>("Arrow" + str1 + str2 + str3);
				Vector2 Pos = Base->GetPos();
				Pos += Base->GetSize() / 2.f;
				Pos.x -= 40.f;
				Arrow->SetPos(Pos);
				Arrow->SetTexture("Room", TEXT("object/door/openEffect.png"));
				Arrow->SetSize(10.f * 4.f, 10.f);
				Arrow->SetCollision(false);
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
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
				Arrow->SetZOrder(1);
				m_MapArrow.push_back(Arrow);
			}
		}
	}

	m_CurMapImage->SetZOrder(0);
}

void CStageMap::MosueOnCallback()
{
	//밝아지기만할뿐 길은 안만들어준다.
	if (!m_GateIn)
		return;

	Vector2 CurPos = CStageManager::GetInst()->GetCurPos();
	size_t Size = m_vecGateButton.size();
	if (!m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].GateButton)
	{
		return;
	}
	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecGateButton[i]->IsMouseOn())
		{
			if (m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].GateButton == m_vecGateButton[i])
			{
				m_GateMoveLine->Enable(false);
				return;
			}
			m_GateMoveLine->Enable(true);
			Vector2 CurGatePos = m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].GateButton->GetNotPivotPos();
			Vector2 MouseOnPos = m_vecGateButton[i]->GetNotPivotPos();
			float Angle= MouseOnPos.GetAngle(CurGatePos);
			Angle += 90.f;
			float Length= MouseOnPos.Distance(CurGatePos);
			m_GateMoveLine->SetRotation(Angle);
			m_GateMoveLine->SetSize(10.f, Length);
			m_GateMoveLine->SetPos(CurGatePos);
			//이위치로 옮기기
			return;
		}
	}
	m_GateMoveLine->Enable(false);
}

void CStageMap::ClickCallback()
{
	if (!m_GateIn)
		return;

	Vector2 CurPos = CStageManager::GetInst()->GetCurPos();
	size_t Size = m_vecGateButton.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (m_vecGateButton[i]->IsClick())
		{
			if (m_MapInfoBase[(int)CurPos.x][(int)CurPos.y].GateButton == m_vecGateButton[i])
				return;
			CStage* Stage=CStageManager::GetInst()->GetCurStage();
			Stage->MoveStageGate(m_vecGateButton[i]->GetCurPos());
			Enable(false);
			m_GateMoveLine->Enable(false);
			//이위치로 스테이지이동 스테이지맵끄고 게이트는 씹어먹고하는등
			return;
		}
	}
}

void CStageMap::MouseOutCallback()
{
	m_GateMoveLine->Enable(false);
}

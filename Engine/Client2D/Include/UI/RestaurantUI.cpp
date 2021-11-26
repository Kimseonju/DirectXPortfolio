
#include "RestaurantUI.h"
#include <Device.h>
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include <UI/Text.h>
CRestaurantUI::CRestaurantUI()
{
}


CRestaurantUI::~CRestaurantUI()
{
}

bool CRestaurantUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetZOrder(UI_ZOrder::MapUI);

	//m_BackGround = CreateWidget<CImage>("BackGround");
	//m_BackGround->SetPos(0.f,0.f);
	//m_BackGround->SetSize(1280.f, 720.f);
	//m_BackGround->SetCollision(false);

	m_Label = CreateWidget<CImage>("Label");
	m_Label->SetPos(0.f, RS.Height - 32.f * 4);
	m_Label->SetTexture("restaurantLabel", TEXT("UI/restaurant/Label.png"));
	m_Label->SetSize(320.f * 4, 32.f * 4);
	m_Label->SetCollision(false);

	m_RestaurantTable = CreateWidget<CImage>("RestaurantTable");
	m_RestaurantTable->SetPos((float)RS.Width / 2.f, 150.f * 2);
	m_RestaurantTable->SetPivot(0.5f, 0.5f);
	//m_RestaurantTable->CreateAnimation2D<CAnimation2D>();
	//CAnimation2D* Animation2D = m_RestaurantTable->GetAnimation2D();
	//Animation2D->AddAnimationSequence2D("RestaurantTable");
	m_RestaurantTable->SetSize(191.f * 4, 130.f * 4);
	m_RestaurantTable->SetCollision(false);

	m_BaseTable = CreateWidget<CImage>("BaseTable1");
	m_BaseTable->SetTexture("Base_3", TEXT("UI/restaurant/Base_3.png"));
	m_BaseTable->SetPos((float)RS.Width / 2.f, 150.f * 2);
	m_BaseTable->SetPivot(0.5f, 0.5f);
	m_BaseTable->SetSize(193.f * 4, 132.f * 4);
	m_BaseTable->SetCollision(false);

	m_FoodSelectBase = CreateWidget<CImage>("FoodSelectBase");
	m_BaseTable->SetTexture("Base_0", TEXT("UI/restaurant/Base_0.png"));
	m_FoodSelectBase->SetPos((float)RS.Width / 2.f, 150.f * 2);
	m_FoodSelectBase->SetPivot(0.5f, 0.5f);
	m_FoodSelectBase->SetSize(111.f * 4, 132.f * 4);
	m_FoodSelectBase->SetCollision(false);


	m_AltarGaugeBase = CreateWidget<CImage>("AltarGaugeBase");
	m_AltarGaugeBase->SetTexture("AltarGaugeBase", TEXT("UI/restaurant/AltarGaugeBase.png"));
	m_AltarGaugeBase->SetPos((float)RS.Width / 2.f, 150.f * 2);
	m_AltarGaugeBase->SetPivot(0.5f, 0.5f);
	m_AltarGaugeBase->SetSize(116.f * 4, 21.f * 4);
	m_AltarGaugeBase->SetCollision(false);


	m_AltarGaugeIcon = CreateWidget<CImage>("AltarGaugeIcon");
	m_AltarGaugeIcon->SetTexture("AltarGaugeIcon", TEXT("UI/restaurant/SatietyRate.png"));
	m_AltarGaugeIcon->SetPos((float)RS.Width / 2.f, 150.f * 2);
	m_AltarGaugeIcon->SetPivot(0.5f, 0.5f);
	m_AltarGaugeIcon->SetSize(17.f * 4, 14.f * 4);
	m_AltarGaugeIcon->SetCollision(false);


	return true;
}

void CRestaurantUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CRestaurantUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CRestaurantUI::Render()
{
	CWidgetWindow::Render();
}

CRestaurantUI* CRestaurantUI::Clone()
{
	return new CRestaurantUI(*this);
}

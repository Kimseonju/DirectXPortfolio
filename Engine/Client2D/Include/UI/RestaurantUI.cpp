
#include "RestaurantUI.h"
#include <Device.h>
#include "../Stage/Stage.h"
#include "../Stage/StageManager.h"
#include <UI/Text.h>
#include "../Object/Player.h"
#define RatioY 0.9375f
CRestaurantUI::CRestaurantUI():
	m_EatFoodImageAlpha(1.f)
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

	m_BackGround = CreateWidget<CImage>("BackGround");
	m_BackGround->SetPos(0.f,0.f);
	m_BackGround->SetSize(1280.f, 720.f);
	m_BackGround->SetTexture("restaurantBackGround", TEXT("UI/restaurant/restaurantBackGround.png"));
	m_BackGround->SetCollision(false);

	m_Label = CreateWidget<CImage>("Label");
	m_Label->SetPos(0.f, RS.Height - 32.f * 4* RatioY);
	m_Label->SetTexture("restaurantLabel", TEXT("UI/restaurant/Label.png"));
	m_Label->SetSize(320.f * 4, 32.f * 4* RatioY);
	m_Label->SetCollision(false);

	m_RestaurantTable = CreateWidget<CImage>("RestaurantTable");
	m_RestaurantTable->SetPos(882.f,350.f);
	m_RestaurantTable->CreateAnimation2D<CAnimation2D>();
	CAnimation2D* Animation2D = m_RestaurantTable->GetAnimation2D();
	Animation2D->AddAnimationSequence2D("RestaurantTable");
	m_RestaurantTable->SetPivot(0.5f, 0.5f);
	m_RestaurantTable->SetSize(764.f, 520.f * RatioY);
	m_RestaurantTable->SetCollision(false);

	m_BaseTable = CreateWidget<CImage>("BaseTable1");
	m_BaseTable->SetTexture("Base_3", TEXT("UI/restaurant/Base_3.png"));
	m_BaseTable->SetPos(882.f, 350.f);
	m_BaseTable->SetPivot(0.5f, 0.5f);
	m_BaseTable->SetSize(193.f * 4, 132.f * 4 * RatioY);
	m_BaseTable->SetCollision(false);



	m_SatietyBase = CreateWidget<CImage>("SatietyBase");
	m_SatietyBase->SetTexture("SatietyBase", TEXT("UI/restaurant/SatietyBase.png"));
	m_SatietyBase->SetPos(10.f, 5.f);
	m_SatietyBase->SetSize(116.f * 4, 21.f * 4 * RatioY);
	m_SatietyBase->SetCollision(false);
	m_SatietyBase->SetZOrder(2);


	m_SatietyIcon = CreateWidget<CImage>("SatietyIcon");
	m_SatietyIcon->SetTexture("SatietyIcon", TEXT("UI/restaurant/SatietyRate.png"));
	m_SatietyIcon->SetPos(74.f,45.f);
	m_SatietyIcon->SetPivot(0.5f, 0.5f);
	m_SatietyIcon->SetSize(17.f * 4, 14.f * 4 * RatioY);
	m_SatietyIcon->SetCollision(false);
	m_SatietyIcon->SetZOrder(3);

	m_SatietyBar = CreateWidget<CProgressBar>("SatietyBar");
	m_SatietyBar->SetBackTint(1.f, 1.f, 1.f, 0.f);
	m_SatietyBar->SetTint(247.f / 255.f, 183.f / 255.f, 60.f / 255.f, 1.f);
	m_SatietyBar->SetSize(330.f, 44.f);
	m_SatietyBar->SetPivot(0.5f, 0.5f);
	m_SatietyBar->SetPos(295.f, 45.f);
	m_SatietyBar->SetPercent(1.f);
	m_SatietyBar->SetZOrder(1);

	//CSharedPtr<CText>    m_SatietyLeft;
	//CSharedPtr<CText>    m_SatietyMiddle;
	//CSharedPtr<CText>    m_SatietyRight;
	m_SatietyLeft = CreateWidget<CText>("SatietyLeft");
	m_SatietyLeft->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_SatietyLeft->SetText(TEXT("100"));
	m_SatietyLeft->SetAlignH(TEXT_ALIGN_H::Left);
	m_SatietyLeft->SetFontSize(25.f);
	m_SatietyLeft->SetPos(209.f, 45.f);
	m_SatietyLeft->SetPivot(0.5f, 0.5f);
	m_SatietyLeft->SetSize(40.f, 28.f);
	m_SatietyLeft->SetCollision(false);
	m_SatietyLeft->SetZOrder(4);

	m_SatietyMiddle = CreateWidget<CText>("SatietyMiddle");
	m_SatietyMiddle->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_SatietyMiddle->SetText(TEXT("/"));
	m_SatietyMiddle->SetAlignH(TEXT_ALIGN_H::Left);
	m_SatietyMiddle->SetFontSize(25.f);
	m_SatietyMiddle->SetPos(269.f, 45.f);
	m_SatietyMiddle->SetPivot(0.5f, 0.5f);
	m_SatietyMiddle->SetSize(40.f, 28.f);
	m_SatietyMiddle->SetCollision(false);
	m_SatietyMiddle->SetZOrder(4);

	m_SatietyRight = CreateWidget<CText>("SatietyRight");
	m_SatietyRight->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_SatietyRight->SetText(TEXT("100"));
	m_SatietyRight->SetAlignH(TEXT_ALIGN_H::Left);
	m_SatietyRight->SetFontSize(25.f);
	m_SatietyRight->SetPos(299.f, 45.f);
	m_SatietyRight->SetPivot(0.5f, 0.5f);
	m_SatietyRight->SetSize(40.f, 28.f);
	m_SatietyRight->SetCollision(false);
	m_SatietyRight->SetZOrder(4);

	m_FoodSelectBase = CreateWidget<CImage>("FoodSelectBase");
	m_FoodSelectBase->SetTexture("Base_0", TEXT("UI/restaurant/Base_0.png"));
	m_FoodSelectBase->SetPos(230.f, 350.f);
	m_FoodSelectBase->SetPivot(0.5f, 0.5f);
	m_FoodSelectBase->SetSize(111.f * 4, 132.f * 4 * RatioY);
	m_FoodSelectBase->SetCollision(false);


	for (int i = 0; i < 5; ++i)
	{

		std::string str = std::to_string(i);

		int SelectFood = i;
		CRestaurantButton* RestaurantButton;
		CText* FoodName;
		CText* FoodPrice;
		RestaurantButton = CreateWidget<CRestaurantButton>("ShopUIButton" + str);
		RestaurantButton->SetSize(396.f, 76.f);
		RestaurantButton->SetPos(30.f, 130.f + 80.f * i);
		RestaurantButton->SetPivot(0.f, 0.f);
		RestaurantButton->SetStateTexture(Button_State::Normal, "RestaurantMenu", TEXT("UI/restaurant/RestaurantMenu.png"));
		RestaurantButton->SetStateTexture(Button_State::MouseOn, "RestaurantMenu_Selected", TEXT("UI/restaurant/RestaurantMenu_Selected.png"));
		RestaurantButton->SetStateTexture(Button_State::Click, "RestaurantMenu_Selected", TEXT("UI/restaurant/RestaurantMenu_Selected.png"));
		RestaurantButton->SetMouseOnCallback< CRestaurantUI>(this, &CRestaurantUI::MosueOnCallback);
		RestaurantButton->SetClickCallback< CRestaurantUI>(this, &CRestaurantUI::ClickCallback);
		RestaurantButton->SetFoodType((FoodType)i);
		RestaurantButton->SetZOrder(2);
		//RestaurantButton->SetClickCallback< CRestaurantUI>(this, &CRestaurantUI::ShopButtonClick);
		//ShopUIButton->SetItem(Item);
		FoodName = CreateWidget<CText>("FoodName");
		FoodName->SetSize(396.f, 76.f);
		FoodName->SetPos(40.f, 120.f + 80.f * i);
		FoodName->SetFontSize(23.f);
		FoodName->SetAlignH(TEXT_ALIGN_H::Left);
		FoodName->SetAlignV(TEXT_ALIGN_V::Top);
		FoodName->SetText(RestaurantButton->GetFoodstr().c_str());
		FoodName->SetFont("DungreedFont");
		FoodName->SetCollision(false);
		FoodName->SetZOrder(3);


		int Price = RestaurantButton->GetPrice();

		TCHAR buf[10];
		memset(buf, 0, sizeof(buf));
		_itot_s(Price, buf, 10);

		FoodPrice = CreateWidget<CText>("FoodPrice");
		FoodPrice->SetSize(150.f, 100.f);
		FoodPrice->SetPos(200.f, 70.f + 80.f * i);
		FoodPrice->SetFontSize(20.f);
		FoodPrice->SetColor(1.f, 1.f, 0.f);
		FoodPrice->SetText(buf);
		FoodPrice->SetAlignV(TEXT_ALIGN_V::Top);
		FoodPrice->SetAlignH(TEXT_ALIGN_H::Right);
		FoodPrice->SetFont("DungreedFont");
		FoodPrice->SetCollision(false);
		FoodPrice->SetZOrder(3);
		RestaurantInfo Info;

		Info.RestaurantButton = RestaurantButton;
		Info.FoodName = FoodName;
		Info.FoodPrice = FoodPrice;

		m_RestaurantInfo.push_back(Info);
	}

	m_GoldBase = CreateWidget<CImage>("GoldBase");
	m_GoldBase->SetTexture("RestaurantGoldBase", TEXT("UI/restaurant/RestaurantGoldBase.png"));
	m_GoldBase->SetPos(1130.f, 50.f);
	m_GoldBase->SetPivot(0.5f, 0.5f);
	m_GoldBase->SetSize(200.f, 80.f);
	m_GoldBase->SetCollision(false);

	m_GoldIcon = CreateWidget<CImage>("GoldIcon");
	m_GoldIcon->SetTexture("GoldCoin0", TEXT("UI/restaurant/GoldCoin0.png"));
	m_GoldIcon->SetPos(1180.f, 50.f);
	m_GoldIcon->SetPivot(0.5f, 0.5f);
	m_GoldIcon->SetSize(35.f, 35.f);
	m_GoldIcon->SetCollision(false);
	m_GoldIcon->SetZOrder(1);

	m_GoldText = CreateWidget<CText>("GoldText");
	m_GoldText->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_GoldText->SetText(TEXT("100000"));
	m_GoldText->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldText->SetFontSize(20.f);
	m_GoldText->SetPos(1050.f, 50.f);
	m_GoldText->SetPivot(0.5f, 0.5f);
	m_GoldText->SetSize(28.f, 28.f);
	m_GoldText->SetCollision(false);
	m_GoldText->SetZOrder(1);

	//음식 이미지 초기화
	CImage* FoodImage = CreateWidget<CImage>("01_Bread");
	FoodImage->SetSize(292.f, 120.f);
	FoodImage->SetPos(882.f, 350.f);
	FoodImage->SetTexture("01_Bread", TEXT("UI/restaurant/foods/01_Bread.png"));
	FoodImage->SetCollision(false);
	FoodImage->SetZOrder(3);
	FoodImage->SetPivot(0.5f, 0.5f);
	FoodImage->Enable(false);
	m_mapFoodImage.insert({ FoodType::Bread, FoodImage });

	FoodImage = CreateWidget<CImage>("02_FriedEgg");
	FoodImage->SetSize(292.f, 120.f);
	FoodImage->SetPos(882.f, 350.f);
	FoodImage->SetTexture("02_FriedEgg", TEXT("UI/restaurant/foods/02_FriedEgg.png"));
	FoodImage->SetCollision(false);
	FoodImage->SetZOrder(3);
	FoodImage->SetPivot(0.5f, 0.5f);
	FoodImage->Enable(false);
	m_mapFoodImage.insert({ FoodType::FriedEgg, FoodImage });
	
	FoodImage = CreateWidget<CImage>("04_TamatoSoup");
	FoodImage->SetSize(292.f, 120.f);
	FoodImage->SetPos(882.f, 350.f);
	FoodImage->SetTexture("04_TamatoSoup", TEXT("UI/restaurant/foods/04_TamatoSoup.png"));
	FoodImage->SetCollision(false);
	FoodImage->SetZOrder(3);
	FoodImage->SetPivot(0.5f, 0.5f);
	FoodImage->Enable(false);
	m_mapFoodImage.insert({ FoodType::TomatoSoup, FoodImage });

	FoodImage = CreateWidget<CImage>("08_Lemonade");
	FoodImage->SetSize(100.f, 152.f);
	FoodImage->SetPos(882.f, 350.f);
	FoodImage->SetTexture("08_Lemonade", TEXT("UI/restaurant/foods/08_Lemonade.png"));
	FoodImage->SetCollision(false);
	FoodImage->SetZOrder(3);
	FoodImage->SetPivot(0.5f, 0.5f);
	FoodImage->Enable(false);
	m_mapFoodImage.insert({ FoodType::Lemonade, FoodImage });

	FoodImage = CreateWidget<CImage>("18_StrawberryPie");
	FoodImage->SetSize(292.f, 120.f);
	FoodImage->SetPos(882.f, 350.f);
	FoodImage->SetTexture("18_StrawberryPie", TEXT("UI/restaurant/foods/18_StrawberryPie.png"));
	FoodImage->SetCollision(false);
	FoodImage->SetZOrder(3);
	FoodImage->SetPivot(0.5f, 0.5f);
	FoodImage->Enable(false);
	m_mapFoodImage.insert({FoodType::StrawberryPie, FoodImage });
	return true;
}

void CRestaurantUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_EatStart)
	{
		if (m_EatFoodImage)
		{
			m_EatFoodImage->SetSize(m_EatFoodImage->GetSize() * 1.1f);
			m_EatFoodImage->SetColorTint(1.f, 1.f, 1.f, m_EatFoodImageAlpha);
			m_EatFoodImageAlpha -= DeltaTime;
			if (m_EatFoodImageAlpha <= 0.f)
			{
				m_EatStart = false;
				m_EatFoodImage->Enable(false);
				m_EatFoodImage = nullptr;
			}
		}
	}
	int Satiety=CGlobalValue::MainPlayer->GetStatus()->GetSatiety();
	std::wstring str;
	str = std::to_wstring(Satiety);
	m_SatietyLeft->SetText(str.c_str());
	float Percent = (float)Satiety / 100.f;
	m_SatietyBar->SetPercent(Percent);

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

void CRestaurantUI::MosueOnCallback()
{
	if (m_Eat)
	{
		m_Eat = false;
		m_EatStart = true;
		m_EatFoodImageAlpha = 1.f;
		return;
	}
	if (m_EatStart)
		return;
	//먹고나서 이미지가 사라졌을때서야 업데이트

	size_t Size = m_RestaurantInfo.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (m_RestaurantInfo[i].RestaurantButton->IsMouseOn())
		{
			CImage* FoodImage = m_mapFoodImage.find(m_RestaurantInfo[i].RestaurantButton->GetFoodType())->second;
			if(m_SelectFoodImage)
				m_SelectFoodImage->Enable(false);
			FoodImage->Enable(true);
			m_SelectFoodImage = FoodImage;
			return;
		}
	}
	if (m_SelectFoodImage)
		m_SelectFoodImage->Enable(false);
}

void CRestaurantUI::ClickCallback()
{
	if (m_Eat)
	{
		return;
	}
	if (m_EatStart)
		return;
	size_t Size = m_RestaurantInfo.size();
	for (size_t i = 0; i < Size; i++)
	{
		if (m_RestaurantInfo[i].RestaurantButton->IsClick())
		{
			if (m_RestaurantInfo[i].RestaurantButton->PlayerEat())
			{
				m_RestaurantInfo[i].RestaurantButton->SetStateTexture(Button_State::Normal, "ThankYouKorean", TEXT("UI/restaurant/ThankYouKorean.png"));
				m_RestaurantInfo[i].RestaurantButton->SetStateTexture(Button_State::MouseOn, "ThankYouKorean", TEXT("UI/restaurant/ThankYouKorean.png"));
				m_RestaurantInfo[i].RestaurantButton->SetStateTexture(Button_State::Click, "ThankYouKorean", TEXT("UI/restaurant/ThankYouKorean.png"));
				m_RestaurantInfo[i].FoodName->Enable(false);
				m_RestaurantInfo[i].FoodPrice->Enable(false);

				if (m_SelectFoodImage)
				{
					m_EatFoodImage = m_SelectFoodImage;
					m_SelectFoodImage = nullptr;
					m_Eat = true;
				}
			}
			return;
		}
	}
}

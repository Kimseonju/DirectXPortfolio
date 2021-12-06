
#include "ResturantInfoWidget.h"
#include "UI/Image.h"
#include "UI/Text.h"
CResturantInfoWidget::CResturantInfoWidget()
{
}

CResturantInfoWidget::CResturantInfoWidget(const CResturantInfoWidget& widget) :
	CWidgetWindow(widget)
{
}

CResturantInfoWidget::~CResturantInfoWidget()
{
}

void CResturantInfoWidget::Active(bool bActive)
{
	CWidgetWindow::Active(bActive);

	m_Base->Active(bActive);
	m_FoodName->Active(bActive);
	m_FoodDescription->Active(bActive);
	m_OneNumber->Active(bActive);
	m_OneDescription->Active(bActive);
	m_TwoNumber->Active(bActive);
	m_TwoDescription->Active(bActive);
	m_GoldImage->Active(bActive);
	m_GoldPrice->Active(bActive);
	m_SatietyImage->Active(bActive);
	m_SatietyNumber->Active(bActive);
}

bool CResturantInfoWidget::Init()
{
	CWidgetWindow::Init();

	SetSize(400.f, 240.f);
	m_Base = CreateWidget<CImage>("Base");
	m_Base->SetSize(400.f, 240.f);
	m_Base->SetColorTint(34.f / 255.f, 32.f / 255.f, 52.f / 255.f, 0.9f);
	m_Base->SetPos(0.f, 0.f);


	m_FoodName = CreateWidget<CText>("FoodName");
	m_FoodName->SetSize(400.f, 235.f);
	m_FoodName->SetFontSize(35.f);
	m_FoodName->SetColorTint(243.f / 255.f, 197.f / 255.f, 174.f / 255.f, 1.f);
	m_FoodName->SetAlignH(TEXT_ALIGN_H::Center);
	m_FoodName->SetAlignV(TEXT_ALIGN_V::Top);
	m_FoodName->SetText(TEXT("음식이름"));
	m_FoodName->SetFont("DungreedFont");



	m_FoodDescription = CreateWidget<CText>("FoodDescription");
	m_FoodDescription->SetSize(380.f, 120.f);
	m_FoodDescription->SetPos(10.f, 50.f);
	m_FoodDescription->SetFontSize(15.f);
	m_FoodDescription->SetText(TEXT("음식설명"));
	m_FoodDescription->SetAlignV(TEXT_ALIGN_V::Top);
	m_FoodDescription->SetFont("DungreedFont");


	m_OneNumber = CreateWidget<CText>("OneNumber");
	m_OneNumber->SetSize(150.f, 100.f);
	m_OneNumber->SetPos(10.f, 70.f);
	m_OneNumber->SetFontSize(15.f);
	m_OneNumber->SetColor(1.f, 1.f, 0.f);
	m_OneNumber->SetText(TEXT("999"));
	m_OneNumber->SetAlignV(TEXT_ALIGN_V::Middle);
	m_OneNumber->SetFont("DungreedFont");

	m_OneDescription = CreateWidget<CText>("OneDescription");
	m_OneDescription->SetPos(50.f, 70.f);
	m_OneDescription->SetSize(200.f, 100.f);
	m_OneDescription->SetFontSize(15.f);
	m_OneDescription->SetText(TEXT("어떤효과"));
	m_OneDescription->SetAlignV(TEXT_ALIGN_V::Middle);
	m_OneDescription->SetFont("DungreedFont");


	m_TwoNumber = CreateWidget<CText>("TwoNumber");
	m_TwoNumber->SetSize(150.f, 100.f);
	m_TwoNumber->SetPos(10.f, 40.f);
	m_TwoNumber->SetFontSize(15.f);
	m_TwoNumber->SetColor(1.f, 1.f, 0.f);
	m_TwoNumber->SetText(TEXT("999"));
	m_TwoNumber->SetAlignV(TEXT_ALIGN_V::Middle);
	m_TwoNumber->SetFont("DungreedFont");

	m_TwoDescription = CreateWidget<CText>("TwoDescription");
	m_TwoDescription->SetPos(50.f, 40.f);
	m_TwoDescription->SetSize(200.f, 100.f);
	m_TwoDescription->SetFontSize(15.f);
	m_TwoDescription->SetText(TEXT("어떤효과"));
	m_TwoDescription->SetAlignV(TEXT_ALIGN_V::Middle);
	m_TwoDescription->SetFont("DungreedFont");


	m_GoldImage = CreateWidget<CImage>("GoldImage");
	m_GoldImage->SetPos(320.f, 50.f);
	m_GoldImage->SetSize(14.f, 14.f);
	m_GoldImage->SetPivot(0.5f, 0.f);
	m_GoldImage->SetTexture("GoldCoin", TEXT("UI/restaurant/GoldCoin0.png"));
	m_GoldPrice = CreateWidget<CText>("GoldPrice");
	m_GoldPrice->SetPos(340.f, 50.f);
	m_GoldPrice->SetSize(50.f, 100.f);
	m_GoldPrice->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_GoldPrice->SetAlignH(TEXT_ALIGN_H::Right);
	m_GoldPrice->SetFontSize(15.f);
	m_GoldPrice->SetText(TEXT("999"));
	m_GoldPrice->SetFont("DungreedFont");


	m_SatietyImage = CreateWidget<CImage>("SatietyImage");
	m_SatietyImage->SetPos(320.f, 15.f);
	m_SatietyImage->SetSize(28.f, 28.f);
	m_SatietyImage->SetPivot(0.5f, 0.f);
	m_SatietyImage->SetTexture("SatietyIcon", TEXT("UI/restaurant/SatietyRate.png"));
	m_SatietyNumber = CreateWidget<CText>("SatietyNumber");
	m_SatietyNumber->SetPos(340.f, 20.f);
	m_SatietyNumber->SetSize(50.f, 100.f);
	m_SatietyNumber->SetAlignV(TEXT_ALIGN_V::Bottom);
	m_SatietyNumber->SetAlignH(TEXT_ALIGN_H::Right);
	m_SatietyNumber->SetFontSize(15.f);
	m_SatietyNumber->SetText(TEXT("999"));
	m_SatietyNumber->SetFont("DungreedFont");
	return true;
}

void CResturantInfoWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CResturantInfoWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CResturantInfoWidget::Render()
{
	CWidgetWindow::Render();
}

CResturantInfoWidget* CResturantInfoWidget::Clone()
{
	return new CResturantInfoWidget(*this);
}

void CResturantInfoWidget::SetFoodName(const TCHAR* Text)
{
	m_FoodName->SetText(Text);
}

void CResturantInfoWidget::SetFoodDescription(const TCHAR* Text)
{
	m_FoodDescription->SetText(Text);
}

void CResturantInfoWidget::SetOneNumber(int Number)
{
	if (Number == 0)
	{
		m_TwoNumber->SetText(TEXT(""));
		return;
	}
	std::wstring str;
	str = std::to_wstring(Number);

	m_OneNumber->SetText(str.c_str());
}

void CResturantInfoWidget::SetOneDescription(const TCHAR* Text)
{
	m_OneDescription->SetText(Text);
}

void CResturantInfoWidget::SetTwoNumber(int Number)
{
	if (Number == 0)
	{
		m_TwoNumber->SetText(TEXT(""));
		return;
	}
	std::wstring str;
	str = std::to_wstring(Number);

	m_TwoNumber->SetText(str.c_str());
}

void CResturantInfoWidget::SetTwoDescription(const TCHAR* Text)
{
	m_TwoDescription->SetText(Text);
}

void CResturantInfoWidget::SetPrice(int Price)
{
	std::wstring str;
	str = std::to_wstring(Price);

	m_GoldPrice->SetText(str.c_str());
}

void CResturantInfoWidget::SetSatietyNumber(int Number)
{
	std::wstring str;
	str = std::to_wstring(Number);

	m_SatietyNumber->SetText(str.c_str());
}

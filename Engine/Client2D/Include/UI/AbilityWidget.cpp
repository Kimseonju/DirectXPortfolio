
#include "AbilityWidget.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include <Device.h>
#include "InventoryButton.h"
#include <Scene/SceneManager.h>

#include "../Object/ShortSword.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Item.h"
CAbilityWidget::CAbilityWidget() :
	m_AbilityBase(nullptr),
	m_AbilityName(nullptr),
	m_AbilityPoint(nullptr),
	m_AbilityStatus1(nullptr),
	m_AbilityStatusText1(nullptr),
	m_AbilityStatus2(nullptr),
	m_AbilityStatusText2(nullptr),
	m_FivePointImage(nullptr),
	m_TenPointImage(nullptr),
	m_TwentyPointImage(nullptr),
	m_PointPlusButton(nullptr),
	m_PointFiveText(nullptr),
	m_PointTenText(nullptr),
	m_PointTwentyText(nullptr)

{
}


CAbilityWidget::~CAbilityWidget()
{
}

bool CAbilityWidget::Init()
{
	CWidgetWindow::Init();
	m_AbilityBase = CreateWidget<CImage>("AbilityBase");
	m_AbilityBase->SetPos(0.f,0.f);
	m_AbilityBase->SetSize(264.f,468.f);
	m_AbilityBase->SetTexture("Ability_WrathBase", TEXT("UI/Ability/AbilityBackground_Wrath.png"));
	m_AbilityBase->SetCollision(false);
	
	m_AbilityName = CreateWidget<CText>("AbilityName");
	m_AbilityName->SetPos(0.f, 230.f);
	m_AbilityName->SetSize(264.f, 100.f);
	m_AbilityName->SetText(TEXT("분노"));
	m_AbilityName->SetAlignH(TEXT_ALIGN_H::Center);
	m_AbilityName->SetFontSize(30.f);
	m_AbilityName->SetFont("DungreedFont");
	m_AbilityName->SetCollision(false);
	
	
	m_AbilityPoint = CreateWidget<CText>("AbilityPoint");
	m_AbilityPoint->SetPos(0.f, 200.f);
	m_AbilityPoint->SetSize(264.f, 100.f);
	m_AbilityPoint->SetText(TEXT("10"));
	m_AbilityPoint->SetAlignH(TEXT_ALIGN_H::Center);
	m_AbilityPoint->SetFontSize(30.f);
	m_AbilityPoint->SetFont("DungreedFont");
	m_AbilityPoint->SetCollision(false);
	

	m_AbilityStatus2 = CreateWidget<CText>("AbilityStatus2");
	m_AbilityStatus2->SetPos(0.f, 140.f);
	m_AbilityStatus2->SetSize(132.f, 100.f);
	m_AbilityStatus2->SetText(TEXT("+10%"));
	m_AbilityStatus2->SetAlignH(TEXT_ALIGN_H::Right);
	m_AbilityStatus2->SetFontSize(20.f);
	m_AbilityStatus2->SetFont("DungreedFont");
	m_AbilityStatus2->SetCollision(false);

	m_AbilityStatusText2 = CreateWidget<CText>("AbilityStatusText2");
	m_AbilityStatusText2->SetPos(134.f, 140.f);
	m_AbilityStatusText2->SetSize(264.f, 100.f);
	m_AbilityStatusText2->SetText(TEXT("위"));
	m_AbilityStatusText2->SetAlignH(TEXT_ALIGN_H::Left);
	m_AbilityStatusText2->SetFontSize(20.f);
	m_AbilityStatusText2->SetFont("DungreedFont");
	m_AbilityStatusText2->SetCollision(false);

	m_AbilityStatus1 = CreateWidget<CText>("AbilityStatus1");
	m_AbilityStatus1->SetPos(2.f, 120.f);
	m_AbilityStatus1->SetSize(132.f, 100.f);
	m_AbilityStatus1->SetText(TEXT("+10"));
	m_AbilityStatus1->SetAlignH(TEXT_ALIGN_H::Right);
	m_AbilityStatus1->SetFontSize(20.f);
	m_AbilityStatus1->SetFont("DungreedFont");
	m_AbilityStatus1->SetCollision(false);
	
	m_AbilityStatusText1 = CreateWidget<CText>("AbilityStatusText1");
	m_AbilityStatusText1->SetPos(134.f, 120.f);
	m_AbilityStatusText1->SetSize(264.f, 100.f);
	m_AbilityStatusText1->SetText(TEXT("아래"));
	m_AbilityStatusText1->SetAlignH(TEXT_ALIGN_H::Left);
	m_AbilityStatusText1->SetFontSize(20.f);
	m_AbilityStatusText1->SetFont("DungreedFont");
	m_AbilityStatusText1->SetCollision(false);
	
	
	
	m_PointFiveText = CreateWidget<CText>("PointFiveText");
	m_PointFiveText->SetPos(50.f, 90.f);
	m_PointFiveText->SetSize(56.f, 100.f);
	m_PointFiveText->SetText(TEXT("5"));
	m_PointFiveText->SetAlignH(TEXT_ALIGN_H::Center);
	m_PointFiveText->SetFontSize(15.f);
	m_PointFiveText->SetFont("DungreedFont");
	m_PointFiveText->SetCollision(false);

	m_PointTenText = CreateWidget<CText>("PointTenText");
	m_PointTenText->SetPos(110.f, 90.f);
	m_PointTenText->SetSize(56.f, 100.f);
	m_PointTenText->SetText(TEXT("10"));
	m_PointTenText->SetAlignH(TEXT_ALIGN_H::Center);
	m_PointTenText->SetFontSize(15.f);
	m_PointTenText->SetFont("DungreedFont");
	m_PointTenText->SetCollision(false);



	m_PointTwentyText = CreateWidget<CText>("PointTwentyText");
	m_PointTwentyText->SetPos(170.f, 90.f);
	m_PointTwentyText->SetSize(56.f, 100.f);
	m_PointTwentyText->SetText(TEXT("20"));
	m_PointTwentyText->SetAlignH(TEXT_ALIGN_H::Center);
	m_PointTwentyText->SetFontSize(15.f);
	m_PointTwentyText->SetFont("DungreedFont");
	m_PointTwentyText->SetCollision(false);

	m_FivePointImage = CreateWidget<CImage>("FivePointImage");
	m_FivePointImage->SetPos(50.f, 100.f);
	m_FivePointImage->SetSize(50.f, 50.f);
	m_FivePointImage->SetCollision(false);
	
	
	m_TenPointImage = CreateWidget<CImage>("TenPointImage");
	m_TenPointImage->SetPos(105.f, 100.f);
	m_TenPointImage->SetSize(50.f, 50.f);
	m_TenPointImage->SetCollision(false);
	
	
	m_TwentyPointImage = CreateWidget<CImage>("TwentyPointImage");
	m_TwentyPointImage->SetPos(160.f, 100.f);
	m_TwentyPointImage->SetSize(50.f, 50.f);
	m_TwentyPointImage->SetCollision(false);
	


	m_PointPlusButton = CreateWidget<CButton>("PointPlusButton");
	m_PointPlusButton->SetSize(76.f, 76.f);
	m_PointPlusButton->SetPos(128.f, 40.f);
	m_PointPlusButton->SetPivot(0.5f, 0.5f);
	m_PointPlusButton->SetStateTexture(Button_State::Normal, "ButtonDisable_Wrath", TEXT("UI/Ability/AbilityBackgroundButtonDisable_Wrath.png"));
	m_PointPlusButton->SetStateTexture(Button_State::MouseOn, "Button_Wrath", TEXT("UI/Ability/AbilityBackgroundButton_Wrath.png"));
	m_PointPlusButton->SetStateTexture(Button_State::Click, "Button_Wrath", TEXT("UI/Ability/AbilityBackgroundButton_Wrath.png"));
	m_PointPlusButton->SetZOrder(1);
	m_PointPlusButton->SetCollision(true);

	return true;
}

void CAbilityWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	
}

void CAbilityWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CAbilityWidget::Render()
{
	CWidgetWindow::Render();
}

CAbilityWidget* CAbilityWidget::Clone()
{
	return new CAbilityWidget(*this);
}


#include "RestaurantButton.h"
#include "Resource/UITransformConstantBuffer.h"
#include "../GlobalValue.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
#include <Scene/Viewport.h>
#include "ResturantInfoWidget.h"
#include "../Object/Player.h"
CRestaurantButton::CRestaurantButton() :
	m_ResturantInfoWidget(nullptr),
	m_Type(FoodType::Lemonade),
	m_Eat(false),
	m_Price(-1),
	m_SatietyNumber(-1)
{
}

CRestaurantButton::~CRestaurantButton()
{
}

void CRestaurantButton::Active(bool bActive)
{
	CButton::Active(bActive);
	m_ResturantInfoWidget->Active(bActive);
}

void CRestaurantButton::Start()
{
	CButton::Start();
	Vector2 Pos = GetPos();
	Vector2 Size = m_ResturantInfoWidget->GetSize();
	Pos.x += Size.x;
	m_ResturantInfoWidget->SetPos(Pos);
	m_ResturantInfoWidget->SetCollision(false);
}

bool CRestaurantButton::Init()
{
	CButton::Init();

	m_ResturantInfoWidget = m_Scene->GetViewport()->AddWindow<CResturantInfoWidget>("ItemInfoWidget" + m_Name);
	m_ResturantInfoWidget->Enable(false);
	m_ResturantInfoWidget->SetZOrder(10);


	return true;
}

void CRestaurantButton::Update(float DeltaTime)
{
	CButton::Update(DeltaTime);
	
	if (m_State == Button_State::Click)
	{
		m_Eat = true;
		m_ResturantInfoWidget->Enable(false);
	}
}

void CRestaurantButton::PostUpdate(float DeltaTime)
{
	CButton::PostUpdate(DeltaTime);
}

void CRestaurantButton::Render()
{
	m_TintCBuffer->SetTint(m_ButtonState[(int)m_State].Tint);

	if (m_ButtonState[(int)m_State].Texture)
		m_TransformCBuffer->SetTextureEnable(true);

	else
		m_TransformCBuffer->SetTextureEnable(false);

	CWidget::Render();

	if (m_ButtonState[(int)m_State].Texture)
		m_ButtonState[(int)m_State].Texture->SetShader(0, TST_PIXEL);

	m_Mesh->Render();

	if (m_ButtonState[(int)m_State].Texture)
		m_ButtonState[(int)m_State].Texture->ResetShader(0, TST_PIXEL);
}

CRestaurantButton* CRestaurantButton::Clone()
{
	return new CRestaurantButton(*this);
}

void CRestaurantButton::CollisionMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
	{
		m_State = Button_State::MouseOn;
	}
	if (!m_Eat)
	{
		m_ResturantInfoWidget->Enable(true);
	}
	else
	{
		m_ResturantInfoWidget->Enable(false);
	}
}

void CRestaurantButton::CollisionUpdateMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionUpdateMouse(MousePos, DeltaTime);
	//CGlobalValue::MainMouse->InventoryMove(this);
}

void CRestaurantButton::CollisionReleaseMouse(const Vector2& MousePos, float DeltaTime)
{
	CWidget::CollisionReleaseMouse(MousePos, DeltaTime);

	if (m_State != Button_State::Disabled)
		m_State = Button_State::Normal;
	m_ResturantInfoWidget->Enable(false);
}

void CRestaurantButton::SetFoodType(FoodType Type)
{
	m_Type = Type;


	switch (m_Type)
	{
	case FoodType::FriedEgg:
	{
		m_ResturantInfoWidget->SetFoodName(TEXT("계란 후라이"));
		m_ResturantInfoWidget->SetFoodDescription(TEXT("약간의 소금과 후추 알레르기가 없다면 언제나 옳은 선택이에요! 만들이 편한 것도 덤이지요.후후."));
		m_ResturantInfoWidget->SetOneNumber(10);
		m_ResturantInfoWidget->SetOneDescription(TEXT("위력"));
		m_ResturantInfoWidget->SetTwoNumber(10);
		m_ResturantInfoWidget->SetTwoDescription(TEXT("최대체력"));
		m_ResturantInfoWidget->SetPrice(683);
		m_ResturantInfoWidget->SetSatietyNumber(20);
		m_Foodstr= TEXT("계란 후라이");
		m_Price=683;
		m_SatietyNumber= 20;
		break;
	}
	case FoodType::Bread:
	{
		m_ResturantInfoWidget->SetFoodName(TEXT("빵"));
		m_ResturantInfoWidget->SetFoodDescription(TEXT("막 구운 빵은 그 자체로도 훌륭한 진미지요."));
		m_ResturantInfoWidget->SetOneNumber(30);
		m_ResturantInfoWidget->SetOneDescription(TEXT("체력 회복"));
		m_ResturantInfoWidget->SetTwoNumber(0);
		m_ResturantInfoWidget->SetTwoDescription(TEXT(""));
		m_ResturantInfoWidget->SetPrice(1303);
		m_ResturantInfoWidget->SetSatietyNumber(10);
		m_Foodstr = TEXT("빵");
		m_Price = 1303;
		m_SatietyNumber = 10;
		break;
	}
	case FoodType::TomatoSoup:
	{
		m_ResturantInfoWidget->SetFoodName(TEXT("토마토수프"));
		m_ResturantInfoWidget->SetFoodDescription(TEXT("토마토에는 껍질이 없었으면 좋겠어요."));
		m_ResturantInfoWidget->SetOneNumber(5);
		m_ResturantInfoWidget->SetOneDescription(TEXT("위력"));
		m_ResturantInfoWidget->SetTwoNumber(5);
		m_ResturantInfoWidget->SetTwoDescription(TEXT("크리티컬"));
		m_ResturantInfoWidget->SetPrice(832);
		m_ResturantInfoWidget->SetSatietyNumber(10);
		m_Foodstr = TEXT("토마토수프");
		m_Price = 832;
		m_SatietyNumber = 10;
		break;
	}
	case FoodType::StrawberryPie:
	{

		m_ResturantInfoWidget->SetFoodName(TEXT("딸기 파이"));
		m_ResturantInfoWidget->SetFoodDescription(TEXT("맛있는 것만 잔뜩 넣었으니 분명 맛있을 거에요."));
		m_ResturantInfoWidget->SetOneNumber(2);
		m_ResturantInfoWidget->SetOneDescription(TEXT("방어력"));
		m_ResturantInfoWidget->SetTwoNumber(0);
		m_ResturantInfoWidget->SetTwoDescription(TEXT(""));
		m_ResturantInfoWidget->SetPrice(557);
		m_ResturantInfoWidget->SetSatietyNumber(10);
		m_Foodstr = TEXT("딸기 파이");
		m_Price = 557;
		m_SatietyNumber = 10;
		break;
	}
	case FoodType::Lemonade:
	{
		m_ResturantInfoWidget->SetFoodName(TEXT("레몬 에이드"));
		m_ResturantInfoWidget->SetFoodDescription(TEXT("시럽만 넣은 도시 제품과는 다르답니다. 빠르게 레몬 5개를 갈아넣은 '진짜'에요."));
		m_ResturantInfoWidget->SetOneNumber(-10);
		m_ResturantInfoWidget->SetOneDescription(TEXT("최대 체력"));
		m_ResturantInfoWidget->SetTwoNumber(0);
		m_ResturantInfoWidget->SetTwoDescription(TEXT(""));
		m_ResturantInfoWidget->SetPrice(557);
		m_ResturantInfoWidget->SetSatietyNumber(-100);
		m_Foodstr = TEXT("레몬 에이드");
		m_Price = 557;
		m_SatietyNumber = -100;
		break;
	}
	}

}

bool CRestaurantButton::PlayerEat()
{
	CPlayer* Player=CGlobalValue::MainPlayer;

	CPlayerStatus* Status=Player->GetStatus();
	if (!Status->AddSatiety(m_SatietyNumber))
		return false;
	if (!Player->SubCoin(m_Price))
	{
		Status->AddSatiety(-m_SatietyNumber);
		return false;
	}

	switch (m_Type)
	{
	case FoodType::FriedEgg:
		Status->SetDamage(Status->GetDamage() + 10);
		Status->SetDamageMax(Status->GetDamageMax() + 10);
		Status->SetHPMax(Status->GetHPMax() + 10);
		break;
	case FoodType::Bread:
		Player->GetStatus()->SetHP(Status->GetHP() + 30);
		break;
	case FoodType::TomatoSoup:
		Status->SetDamage(Status->GetDamage() + 5);
		Status->SetDamageMax(Status->GetDamageMax() + 5);
		Status->SetCritical(Status->GetCritical() + 5);
		break;
	case FoodType::StrawberryPie:
		break;
	case FoodType::Lemonade:
		break;
	case FoodType::End:
		break;
	default:
		break;
	}
	m_Eat = true;
	return true;
	
}

bool CRestaurantButton::IsClick()
{
	if (m_State == Button_State::Click)
	{
		return true;
	}
	return false;
}

bool CRestaurantButton::IsMouseOn()
{
	if (m_Eat)
		return false;
	if (m_State == Button_State::MouseOn)
	{
		return true;
	}
	return false;
}

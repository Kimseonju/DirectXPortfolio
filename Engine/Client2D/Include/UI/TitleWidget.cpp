
#include "TitleWidget.h"
#include <Device.h>
#include "../SceneMode/TestMainScene.h"
#include "Scene/SceneManager.h"
#include "../SceneMode/StartScene.h"
#include <UI/Button.h>
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
CTitleWidget::CTitleWidget() :
	m_Cloud(nullptr),
	m_BackCloud(nullptr)
{

}

CTitleWidget::CTitleWidget(const CTitleWidget& widget) :
	CWidgetWindow(widget)
{
}

CTitleWidget::~CTitleWidget()
{
}

bool CTitleWidget::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector2 Pos;


	CImage* Title = CreateWidget<CImage>("MainLogo");

	Title->SetSize(624.f, 300.f);
	Pos.x = RS.Width / 2.f;
	Pos.y = RS.Height / 2.f + 100.f;

	Title->SetPos(Pos);
	Title->SetPivot(0.5f, 0.5f);
	Title->SetTexture("MainLogo", TEXT("TitleScene/MainLogo.png"));


	CButton* PlayButton = CreateWidget<CButton>("StartButton");
	Pos.x = RS.Width / 2.f;
	Pos.y = RS.Height / 2.f - 100.f;
	PlayButton->SetPos(Pos);
	PlayButton->SetSize(144.f, 48.f);
	PlayButton->SetPivot(0.5f, 0.5f);
	PlayButton->SetStateTexture(Button_State::Normal, "StartButtonOff", TEXT("TitleScene/PlayOff_Kor.png"));
	PlayButton->SetStateTexture(Button_State::MouseOn, "StartButtonOn", TEXT("TitleScene/PlayOn_Kor.png"));
	PlayButton->SetStateTexture(Button_State::Click, "StartButtonOn", TEXT("TitleScene/PlayOn_Kor.png"));
	PlayButton->SetZOrder(1);


	PlayButton->SetClickCallback<CTitleWidget>(this, &CTitleWidget::StartButtonClick);

	PlayButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	PlayButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");

	CButton* ExitButton = CreateWidget<CButton>("ExitButton");
	Pos.x = RS.Width / 2.f;
	Pos.y = RS.Height / 2.f - 150.f;
	ExitButton->SetPos(Pos);
	ExitButton->SetSize(84.f, 48.f);
	ExitButton->SetPivot(0.5f, 0.5f);
	ExitButton->SetStateTexture(Button_State::Normal, "ExittButtonOff", TEXT("TitleScene/ExitOff_Kor.png"));
	ExitButton->SetStateTexture(Button_State::MouseOn, "ExittButtonOn", TEXT("TitleScene/ExitOn_Kor.png"));
	ExitButton->SetStateTexture(Button_State::Click, "ExittButtonOn", TEXT("TitleScene/ExitOn_Kor.png"));
	ExitButton->SetZOrder(1);



	ExitButton->SetClickCallback<CTitleWidget>(this, &CTitleWidget::ExitButtonClick);

	ExitButton->SetInteractionSound(Button_Sound_State::MouseOn, "ButtonMouseOn");
	ExitButton->SetInteractionSound(Button_Sound_State::Click, "ButtonClick");


	return true;
}

void CTitleWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CTitleWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CTitleWidget::Render()
{
	CWidgetWindow::Render();
}

CTitleWidget* CTitleWidget::Clone()
{
	return new CTitleWidget(*this);
}

void CTitleWidget::StartButtonClick()
{
	m_Scene->GetResource()->FindSound("title")->Stop();
	CSceneManager::GetInst()->SetChange(true);
}

void CTitleWidget::ExitButtonClick()
{

}


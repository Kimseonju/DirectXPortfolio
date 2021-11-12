
#include "BossSpawnUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include <Scene/CameraManager.h>
#include <Component/Camera.h>
CBossSpawnUI::CBossSpawnUI() :
	m_Spawn(false)

{
}

CBossSpawnUI::CBossSpawnUI(const CBossSpawnUI& widget) :
	CWidgetWindow(widget)
{
}

CBossSpawnUI::~CBossSpawnUI()
{
}

bool CBossSpawnUI::Init()
{
	CWidgetWindow::Init();


	m_BossUpDonwImage = CreateWidget<CImage>("BossLifeBack");
	m_BossUpDonwImage->SetSize(500.f, 64.f);
	m_BossUpDonwImage->SetTexture("BossLifeBack", TEXT("UI/BossLifeBack.png"));
	m_BossUpDonwImage->SetPos(0.f, 0.f);
	m_BossUpDonwImage->SetCollision(false);


	return true;
}

void CBossSpawnUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_Spawn)
	{
		CCamera* Camera=m_Scene->GetCameraManager()->GetCurrentCamera();
	}
}

void CBossSpawnUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBossSpawnUI::Render()
{
	CWidgetWindow::Render();
}

CBossSpawnUI* CBossSpawnUI::Clone()
{
	return new CBossSpawnUI(*this);
}

void CBossSpawnUI::Spawn()
{
	m_Spawn = true;
	m_Alpha = 0.f;
}



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
#include <Input.h>
#include "UIManager.h"
CBossSpawnUI::CBossSpawnUI() :
	m_Spawn(false),
	m_Alpha(0.f),
	m_NickNameAlpha(0.f),
	m_Play(false)

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

	SetZOrder(UI_ZOrder::BossSpawnUI);

	m_BossUpImage = CreateWidget<CImage>("BossUpImage");
	m_BossUpImage->SetSize(1280.f, 200.f);
	m_BossUpImage->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_BossUpImage->SetPos(0.f, 520.f);
	m_BossUpImage->SetCollision(false);


	m_BossDonwImage = CreateWidget<CImage>("BossDonwImage");
	m_BossDonwImage->SetSize(1280.f, 200.f);
	m_BossDonwImage->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_BossDonwImage->SetPos(0.f, 0.f);
	m_BossDonwImage->SetCollision(false);


	m_BossName = CreateWidget<CText>("BossName");
	m_BossName->SetText(TEXT("벨리알"));
	m_BossName->SetPos(250.f, 0.f);
	m_BossName->SetCollision(false);
	m_BossName->SetOpacity(0.f);
	m_BossName->SetAlphaEnable(true);

	m_BossNinkName = CreateWidget<CText>("BossNinkName");
	m_BossNinkName->SetText(TEXT("감옥의 수문장"));
	m_BossNinkName->SetColorTint(1.f, 1.f, 1.f, 0.f);
	m_BossNinkName->SetPos(300.f, 0.f);
	m_BossNinkName->SetCollision(false);
	m_BossNinkName->SetOpacity(0.f);
	m_BossNinkName->SetAlphaEnable(true);
	return true;
}

void CBossSpawnUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_Spawn)
	{
		m_Play = true;
		m_Alpha += DeltaTime;
		m_BossUpImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		m_BossDonwImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		m_BossName->SetOpacity(m_Alpha);
		if (m_Alpha > 1.f)
		{
			m_Alpha = 1.f;
			m_NickNameAlpha += DeltaTime;
			m_BossNinkName->SetOpacity(m_NickNameAlpha);
			CUIManager::GetInst()->GetBossUI()->Enable(true);

		}
	}
	else
	{
		m_Alpha -= DeltaTime;
		m_BossUpImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		m_BossDonwImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		m_BossName->SetOpacity(m_Alpha);
		m_BossNinkName->SetOpacity(m_Alpha);
		if (m_Alpha < 0.f)
		{
			if (m_Play)
			{
				Enable(false);
			}
				
		}
	}
}

void CBossSpawnUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CBossSpawnUI::PrevRender(float DeltaTime)
{
	CWidgetWindow::PrevRender(DeltaTime);
	CCamera* Camera = m_Scene->GetCameraManager()->GetCurrentCamera();
	if (!Camera->IsCameraMove())
	{
		m_Spawn = false;
		CInput::GetInst()->StartInput();
	}
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


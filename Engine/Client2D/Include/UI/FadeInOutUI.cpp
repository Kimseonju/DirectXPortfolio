
#include "FadeInOutUI.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include <Device.h>
#include "../Object/Player.h"
#include "../BasicStatus.h"
#include "../Animation2D/LifeWaveAnimation2D.h"
#include "BossUI.h"
#include "WeaponUI.h"
#include "../Stage/StageManager.h"
#include <Engine.h>
#include <Input.h>
#include "UIManager.h"
#include "MiniMap.h"
CFadeInOutUI::CFadeInOutUI():
	m_StageDir(Stage_Dir::END),
	m_FadeOut(false),
	m_FadeIn(false),
	m_StageMove(false),
	m_Alpha(0.f),
	m_StageGateMove(0.f,0.f),
	m_StageBoss(false)
{
}

CFadeInOutUI::~CFadeInOutUI()
{
}

bool CFadeInOutUI::Init()
{
	CWidgetWindow::Init();
	Resolution RS = CDevice::GetInst()->GetResolution();

	m_FadeImage = CreateWidget<CImage>("FadeImage");
	m_FadeImage->SetSize((float)RS.Width, (float)RS.Height);
	m_FadeImage->SetColorTint(0.f, 0.f, 0.f, 0.f);
	m_FadeImage->SetPos(0.f,0.f);
	m_FadeImage->SetCollision(false);

	return true;
}

void CFadeInOutUI::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
	if (m_FadeOut)
	{
		m_Alpha += DeltaTime*2.f;
		m_FadeImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		if (m_Alpha >= 1.f)
		{
			m_FadeIn = true;
			m_FadeOut = false;
			if (m_StageBoss)
			{

				CStageManager::GetInst()->CreateBossStage();
				CUIManager::GetInst()->GetStageMap()->MapUpdate();
				m_StageBoss = false;
			}
			else if (m_StageMove)
			{
				CStageManager::GetInst()->NextStage(m_StageDir);
      				CUIManager::GetInst()->GetStageMap()->StageMove();
				m_StageMove = false;
			}
			else if (m_StageGate)
			{
				CStageManager::GetInst()->GateStage(m_StageGateMove);
			}
			CUIManager::GetInst()->GetMiniMapUI()->TileUpdate();
		}
	}
	else if (m_FadeIn)
	{
		m_Alpha -= DeltaTime * 2.f;
		m_FadeImage->SetColorTint(0.f, 0.f, 0.f, m_Alpha);
		if (m_Alpha <=0.f)
		{
			m_FadeIn = false;
			CInput::GetInst()->SetUpdate(true);
			
		}
	}
}

void CFadeInOutUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CFadeInOutUI::Render()
{
	CWidgetWindow::Render();
}

CFadeInOutUI* CFadeInOutUI::Clone()
{
	return new CFadeInOutUI(*this);
}

void CFadeInOutUI::StageMoveIn(Stage_Dir Dir)
{
	m_StageDir = Dir;

	m_Alpha = 0.f;

	m_FadeOut = true;
	m_StageMove = true;
	m_StageGate = false;
	CInput::GetInst()->SetUpdate(false);
}

void CFadeInOutUI::StageGateIn(Vector2 Pos)
{
	m_StageGateMove = Pos;
	m_Alpha = 0.f;
	m_FadeOut = true;
	m_StageMove = false;
	m_StageGate = true;
	CInput::GetInst()->SetUpdate(false);

}

void CFadeInOutUI::StageBossIn()
{
	m_Alpha = 0.f;

	m_FadeOut = true;
	m_StageBoss = true;
	CInput::GetInst()->SetUpdate(false);
}

void CFadeInOutUI::SetPadeIn()
{
}

void CFadeInOutUI::SetPadeOut()
{
}

bool CFadeInOutUI::IsFadeIn()
{
	return false;
}

bool CFadeInOutUI::IsFadeOut()
{
	return false;
}

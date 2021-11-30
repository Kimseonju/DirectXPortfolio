#include "LoadingUI.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
CLoadingUI::CLoadingUI():
	m_LoadingPercent(1.f),
	m_ImageCount(0.f),
	m_ImageNum(0)
{
}

CLoadingUI::CLoadingUI(const CLoadingUI& widget)
{
	m_LoadingPercent = widget.m_LoadingPercent;
}

CLoadingUI::~CLoadingUI()
{
}

bool CLoadingUI::Init()
{
	CWidgetWindow::Init();

	//CImage* Back = CreateWidget<CImage>("LoadingBack");
	//
	//Back->SetPos(0.f, 0.f);
	//Back->SetSize(1280.f, 720.f);
	//Back->SetTexture("LoadingBack", TEXT("LoadingBack.jpg"));
	//Back->SetZOrder(0);

	//m_LoadingBar = CreateWidget<CProgressBar>("LoadingBar");
	//m_LoadingBar->SetPos(1280.f / 2.f - 400.f, 70.f);
	//m_LoadingBar->SetSize(800.f, 30.f);
	//m_LoadingBar->SetTint(1.f, 1.f, 0.f, 1.f);
	//m_LoadingBar->SetPercent(0.f);
	//m_LoadingBar->SetZOrder(1);
	//m_LoadingBar->Enable(false);
	m_LoadingPercent = 0.f;


	m_LoadingImage0 = CreateWidget<CImage>("LoadingImage0");
	m_LoadingImage0->SetPos(1280.f / 2.f, 720.f/2.f);
	m_LoadingImage0->SetSize(177.f, 192.f);
	m_LoadingImage0->SetPivot(0.5f, 0.5f);
	m_LoadingImage0->SetTexture("TeamLogo0", TEXT("UI/Loading/TeamLogo0.png"));
	m_LoadingImage0->SetZOrder(1);


	m_LoadingImage1 = CreateWidget<CImage>("LoadingImage1");
	m_LoadingImage1->SetPos(1280.f / 2.f, 720.f / 2.f);
	m_LoadingImage1->SetSize(177.f, 192.f);
	m_LoadingImage1->SetPivot(0.5f, 0.5f);
	m_LoadingImage1->SetTexture("TeamLogo1", TEXT("UI/Loading/TeamLogo1.png"));
	m_LoadingImage1->SetZOrder(1);
	m_LoadingImage1->SetColorTint(1.f, 1.f, 1.f, 0.f);


	m_LoadingImage2 = CreateWidget<CImage>("LoadingImage2");
	m_LoadingImage2->SetPos(1280.f / 2.f, 720.f / 2.f);
	m_LoadingImage2->SetSize(177.f, 192.f);
	m_LoadingImage2->SetPivot(0.5f, 0.5f);
	m_LoadingImage2->SetTexture("TeamLogo2", TEXT("UI/Loading/TeamLogo2.png"));
	m_LoadingImage2->SetZOrder(1);
	m_LoadingImage2->SetColorTint(1.f, 1.f, 1.f, 0.f);
	return true;
}

void CLoadingUI::Update(float DeltaTime)
{
 	CWidgetWindow::Update(DeltaTime);
	if (m_ImageNum == 0)
	{
		m_ImageCount += DeltaTime;
		m_LoadingImage0->SetColorTint(1.f, 1.f, 1.f, 1.f - m_ImageCount);
		m_LoadingImage1->SetColorTint(1.f, 1.f, 1.f, m_ImageCount);
		if (m_ImageCount >= 1.f)
		{
			m_ImageCount = 0.f;
			m_ImageNum++;
		}
	}
	else if (m_ImageNum == 1)
	{
		m_ImageCount += DeltaTime;
		m_LoadingImage1->SetColorTint(1.f, 1.f, 1.f, 1.f - m_ImageCount);
		m_LoadingImage2->SetColorTint(1.f, 1.f, 1.f, m_ImageCount);
		if (m_ImageCount >= 1.f)
		{
			m_ImageCount = 0.f;
			m_ImageNum++;
		}
	}
	else if (m_ImageNum == 2)
	{
		m_ImageCount += DeltaTime ;
		m_LoadingImage2->SetColorTint(1.f, 1.f, 1.f, 1.f - m_ImageCount);
		m_LoadingImage0->SetColorTint(1.f, 1.f, 1.f, m_ImageCount);
		if (m_ImageCount >= 1.f)
		{
			m_ImageCount = 0.f;
			m_ImageNum++;
			CSceneManager::GetInst()->SetChange(true);
		}
	}
}

void CLoadingUI::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CLoadingUI::Render()
{
	CWidgetWindow::Render();
}

CLoadingUI* CLoadingUI::Clone()
{
	return new CLoadingUI(*this);
}

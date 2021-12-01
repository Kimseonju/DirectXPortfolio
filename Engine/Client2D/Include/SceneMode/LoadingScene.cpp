#include "LoadingScene.h"
#include "../UI/LoadingUI.h"
#include "Scene/Scene.h"
#include "Scene/Viewport.h"
#include "LoadingThread.h"
#include "ThreadManager.h"
#include "Scene/SceneResource.h"

CLoadingScene::CLoadingScene():
	m_Thread(nullptr)
{
}

CLoadingScene::~CLoadingScene()
{
}

bool CLoadingScene::Init()
{
	m_Widget = m_pScene->GetViewport()->AddWindow<CLoadingUI>("Loading");

	// 로딩용 스레드를 생성한다.
	m_Thread = CThreadManager::GetInst()->CreateThread<CLoadingThread>("LoadingThread");

	m_Thread->SetLoop(false);
	m_Thread->Start();

	m_pScene->GetResource()->LoadSound("BGM", false, "Loading",
		"Loading.mp3");
	m_pScene->GetResource()->FindSound("Loading")->Play();
	return true;
}

void CLoadingScene::Update(float DeltaTime)
{
	m_Widget->SetPercent(m_Thread->GetPercent());
}

#include "LoadingThread.h"
#include "TestMainScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "StartScene.h"
CLoadingThread::CLoadingThread():
	m_Percent(0.f)
{
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	CScene* Scene = CSceneManager::GetInst()->CreateScene();
	m_Percent = 0.25f;
	
	Scene->SetSceneMode<CStartScene>();
	m_Percent = 0.5f;
	CSceneManager::GetInst()->SetNextScene(Scene);
	m_Percent = 0.99f;
	CSceneManager::GetInst()->SetChange(false);
}

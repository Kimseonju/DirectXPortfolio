#include "LoadingThread.h"
#include "TestMainScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
CLoadingThread::CLoadingThread()
{
}

CLoadingThread::~CLoadingThread()
{
}

void CLoadingThread::Run()
{
	CScene* Scene = CSceneManager::GetInst()->CreateScene();

	Scene->SetSceneMode<CTestMainScene>();
	CSceneManager::GetInst()->SetNextScene(Scene);
}

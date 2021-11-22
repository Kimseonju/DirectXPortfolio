
#include "EndingScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "../UI/TitleWidget.h"
#include "Scene/Viewport.h"
#include "../Object/StartScene/BackGround.h"
#include "../Object/Cloud.h"
#include "../Object/StartScene/Bird.h"
CEndingScene::CEndingScene()
{
}

CEndingScene::~CEndingScene()
{
}

bool CEndingScene::Init()
{
	CreateMaterial();
	CreateAnimationSequence2D();
	CreateParticle();

	CBackGround* pBackGround = m_pScene->SpawnObject<CBackGround>("BackGround");
	pBackGround->AddTexture("sky", TEXT("TitleScene/sky.png"));

	CCloud* pFront_CloudMove1 = m_pScene->SpawnObject<CCloud>("Front_CloudMove1");
	pFront_CloudMove1->SetRelativePos(-2300.f, 0.f, 0.f);
	pFront_CloudMove1->AddTexture("FrontCloud", TEXT("TitleScene/FrontCloud.png"));
	pFront_CloudMove1->SetSpeed(100.f);

	CCloud* pFront_CloudMove2 = m_pScene->SpawnObject<CCloud>("Front_CloudMove2");
	pFront_CloudMove2->AddTexture("FrontCloud", TEXT("TitleScene/FrontCloud.png"));
	pFront_CloudMove2->SetSpeed(100.f);

	CCloud* pFront_CloudMove3 = m_pScene->SpawnObject<CCloud>("Front_CloudMove3");
	pFront_CloudMove3->AddTexture("FrontCloud", TEXT("TitleScene/FrontCloud.png"));
	pFront_CloudMove3->SetSpeed(100.f);
	pFront_CloudMove3->SetRelativePos(2300.f, 0.f, 0.f);



	CCloud* pBack_CloudMove1 = m_pScene->SpawnObject<CCloud>("Back_CloudMove1");
	pBack_CloudMove1->SetRelativePos(-2560.f, 0.f, 0.f);
	pBack_CloudMove1->AddTexture("BackCloud", TEXT("TitleScene/BackCloud.png"));
	pBack_CloudMove1->SetSpeed(50.f);

	CCloud* pBack_CloudMove2 = m_pScene->SpawnObject<CCloud>("Back_CloudMove2");
	pBack_CloudMove2->AddTexture("BackCloud", TEXT("TitleScene/BackCloud.png"));
	pBack_CloudMove2->SetSpeed(50.f);
	CCloud* pBack_CloudMove3 = m_pScene->SpawnObject<CCloud>("Back_CloudMove3");
	pBack_CloudMove3->AddTexture("BackCloud", TEXT("TitleScene/BackCloud.png"));
	pBack_CloudMove3->SetSpeed(50.f);
	pBack_CloudMove3->SetRelativePos(2560.f, 0.f, 0.f);
	//새가 3마리 다 안나오는건 Y솔트때문이다.
	//나중에 구조를 수정해야함
	CBird* pBird1 = m_pScene->SpawnObject<CBird>("Bird1");
	CBird* pBird2 = m_pScene->SpawnObject<CBird>("Bird2");
	pBird2->SetRelativePos(-100.f, 300.f, 0.f);
	CBird* pBird3 = m_pScene->SpawnObject<CBird>("Bird3");
	pBird3->SetRelativePos(-500.f, 500.f, 0.f);

	CTitleWidget* Widget = m_pScene->GetViewport()->AddWindow<CTitleWidget>("TitleWidget");
	return true;
}

void CEndingScene::CreateMaterial()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("BirdMove");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BirdMove",
		"BirdAtlas", TEXT("TitleScene/bird.png"));

	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BirdMove",
			Vector2(i * 12.f, 0.f), Vector2((i + 1) * 12.f, 8.f));
	}
}

void CEndingScene::CreateAnimationSequence2D()
{

}

void CEndingScene::CreateParticle()
{

}

#include "EndingScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "../Object/EndingCloud.h"
#include "../Object/EndingHorse.h"
#include "../Object/EndingMountain.h"
#include "../Object/EndingPlayer.h"
#include "../Object/EndingTerrain.h"
#include "../Object/EndingCamera.h"
#include "../UI/EndingUI.h"
#include "Scene/Viewport.h"
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

	CEndingCloud* EndingCloud = m_pScene->SpawnObject<CEndingCloud>("EndingCloud");
	CEndingMountain* EndingMountain = m_pScene->SpawnObject<CEndingMountain>("EndingMountain");
	CEndingPlayer* EndingPlayer = m_pScene->SpawnObject<CEndingPlayer>("EndingPlayer");
	CEndingHorse* EndingHorse = m_pScene->SpawnObject<CEndingHorse>("EndingHorse");
	CEndingTerrain* EndingTerrain = m_pScene->SpawnObject<CEndingTerrain>("EndingTerrain");
	CEndingCamera* EndingCamera = m_pScene->SpawnObject<CEndingCamera>("EndingCamera");


	CEndingUI* Widget = m_pScene->GetViewport()->AddWindow<CEndingUI>("EndingUI");
	return true;
}

void CEndingScene::CreateMaterial()
{

}

void CEndingScene::CreateAnimationSequence2D()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("PlayerIdle",
		"PlayerIdle", TEXT("Characters/Basic/player_idle.png"));

	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("PlayerIdle",
			Vector2(i * 15.f, 0.f), Vector2((i + 1) * 15.f, 20.f));
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("Horse");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Horse",
		"Horse", TEXT("object/horse/Horse.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Horse",
			Vector2(i * 120.f, 0.f), Vector2((i + 1) * 120.f, 38.f));
	}

}

void CEndingScene::CreateParticle()
{

}
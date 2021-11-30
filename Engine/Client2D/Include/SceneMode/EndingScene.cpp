
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
#include <Input.h>
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

	m_pScene->GetResource()->LoadSound("BGM", true, "Town",
		"bgm/0.Town.wav");

	m_pScene->GetResource()->FindSound("Town")->Play();

	CEndingCloud* EndingCloud = m_pScene->SpawnObject<CEndingCloud>("EndingCloud");
	CEndingMountain* EndingMountain = m_pScene->SpawnObject<CEndingMountain>("EndingMountain");
	EndingMountain->SetWorldPos(-640.f, 70.f, 0.f);
	CEndingMountain* EndingMountain2 = m_pScene->SpawnObject<CEndingMountain>("EndingMountain2");
	EndingMountain2->SetWorldPos(-320.f, 70.f, 0.f);

	CEndingMountain* EndingMountain3 = m_pScene->SpawnObject<CEndingMountain>("EndingMountain3");
	EndingMountain3->SetWorldPos(0.f, 70.f, 0.f);
	CEndingPlayer* EndingPlayer = m_pScene->SpawnObject<CEndingPlayer>("EndingPlayer");
	CEndingHorse* EndingHorse = m_pScene->SpawnObject<CEndingHorse>("EndingHorse");
	CEndingTerrain* EndingTerrain = m_pScene->SpawnObject<CEndingTerrain>("EndingTerrain");
	EndingTerrain->SetWorldPos(-170.f, -155.f, 0.f);
	EndingTerrain = m_pScene->SpawnObject<CEndingTerrain>("EndingTerrain2");
	EndingTerrain->SetWorldPos(-650.f, -155.f, 0.f);
	CEndingCamera* EndingCamera = m_pScene->SpawnObject<CEndingCamera>("EndingCamera");


	CEndingUI* Widget = m_pScene->GetViewport()->AddWindow<CEndingUI>("EndingUI");
	CInput::GetInst()->ClearCallback();
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
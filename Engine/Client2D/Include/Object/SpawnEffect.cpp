#include "SpawnEffect.h"
#include "../GlobalValue.h"
#include "../Object/Player.h"
#include "../Object/SmallSkel.h"
#include "../Object/Belial.h"
#include "../Object/SmallSkel_Bow.h"
#include "../Object/Ghost.h"
#include "../Object/Banshee.h"
#include "../Object/Giant_Red.h"
#include "../Object/ShopNPC.h"
#include "../Object/BasicTresure.h"
#include "../Object/BossTresure.h"
#include "../Stage/StageManager.h"
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
CSpawnEffect::CSpawnEffect()
{
}

CSpawnEffect::CSpawnEffect(const CSpawnEffect& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CSpawnEffect::~CSpawnEffect()
{
}

void CSpawnEffect::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Sprite->Enable(bEnable);
}

void CSpawnEffect::Start()
{
	CGameObject::Start();
}

bool CSpawnEffect::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");


	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(48.f, 48.f, 0.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("SpawnEffect", false);
	m_Animation2D->SetFrameEndFunction<CSpawnEffect>(this, &CSpawnEffect::AnimationFrameEnd);
	Enable(false);
	return true;
}

void CSpawnEffect::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CSpawnEffect::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSpawnEffect::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CSpawnEffect::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CSpawnEffect* CSpawnEffect::Clone()
{
	return new CSpawnEffect(*this);
}

void CSpawnEffect::Spawn()
{
	if (m_ClassType == Client_Class_Type::Enemy)
	{
		switch (m_EnemyType)
		{
		case Client_Enemy_Type::SmallSkel_Sword:
			m_Obj = m_pScene->SpawnObject<CSmallSkel>("CSmallSkelSword");

			break;
		case Client_Enemy_Type::SmallSkel_Bow:
			m_Obj = m_pScene->SpawnObject<CSmallSkel_Bow>("SmallSkel_Bow");
			break;
		case Client_Enemy_Type::Ghost:
			m_Obj = m_pScene->SpawnObject<CGhost>("Ghost");
			break;
		case Client_Enemy_Type::Banshee:
			m_Obj = m_pScene->SpawnObject<CBanshee>("Banshee");
			break;
		case Client_Enemy_Type::Giant_Red:
			m_Obj = m_pScene->SpawnObject<CGiant_Red>("Giant_Red");
			break;
		case Client_Enemy_Type::Minotaurs:
			break;
		case Client_Enemy_Type::Ovibos:
			break;
		case Client_Enemy_Type::Big_Normal:
			break;
		}
		CStage* Stage = CStageManager::GetInst()->GetCurStage();
		if (Stage)
		{
			Stage->PushEnemy(m_Obj);
			m_Obj->SetWorldPos(2000.f, 2000.f, 0.f);
			m_pScene->GetResource()->FindSound("SpawnEnemy")->Play();
		}
	}
	else if (m_ClassType == Client_Class_Type::Object)
	{
		switch (m_ObjectType)
		{
		case Client_Object_Type::TresureBox:
			m_Obj = m_pScene->SpawnObject<CBasicTresure>("BasicTresure");
			break;
		case Client_Object_Type::BossTresureBox:
			m_Obj = m_pScene->SpawnObject<CBossTresure>("BossTresure");

			break;
		}
		CStage* Stage = CStageManager::GetInst()->GetCurStage();
		if (Stage)
		{
			
			Stage->PushObject(m_Obj);
			m_Obj->SetWorldPos(2000.f, 2000.f, 0.f);
		}
	}

}

void CSpawnEffect::AnimationFrameEnd(const std::string& Name)
{

	//몬스터나 기타등등 스폰시키기

	Active(false);
}

void CSpawnEffect::Animation2DNotify(const std::string& Name)
{
	if (Name == "Spawn")
	{
		if (m_Obj)
		{
			Vector3 Pos = GetWorldPos();
			m_Obj->SetWorldPos(GetWorldPos());
		}
	}
}


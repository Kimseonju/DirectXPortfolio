
#include "DaisyRing.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include "../BasicStatus.h"
#include "ShortSwordEffectObject.h"
#include "PlayerAttack.h"
#include <Scene/SceneResource.h>
CDaisyRing::CDaisyRing()
{
	Enable(false);
	SetItemTexture("DaisyRing", TEXT("Acc/DaisyRing.png"));
	m_Type = ITEM_TYPE::Acc;
	m_Rank = ITEM_RANK::Rare;
	SetStatus("DaisyRing");
	m_ItemName = TEXT("광기의 반지");
	m_ItemText = TEXT("\"무기가 더 손에 감기는 느낌을 받는다\"");
}

CDaisyRing::CDaisyRing(const CDaisyRing& obj) :
	CItem(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CDaisyRing::~CDaisyRing()
{
}

void CDaisyRing::Start()
{
	CItem::Start();
}

bool CDaisyRing::Init()
{
	CItem::Init();
	m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture("DaisyRing", TEXT("Acc/DaisyRing.png"));
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CDaisyRing::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);

	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CDaisyRing::PostUpdate(float DeltaTime)
{
	CItem::PostUpdate(DeltaTime);
}

void CDaisyRing::Collision(float DeltaTime)
{
	CItem::Collision(DeltaTime);
}

void CDaisyRing::Render(float DeltaTime)
{
	CItem::Render(DeltaTime);
}

CDaisyRing* CDaisyRing::Clone()
{
	return new CDaisyRing(*this);
}

void CDaisyRing::Animation2DNotify(const std::string& Name)
{
}

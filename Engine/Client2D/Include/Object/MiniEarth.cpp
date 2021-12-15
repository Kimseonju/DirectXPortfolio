
#include "MiniEarth.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include "../BasicStatus.h"
#include "ShortSwordEffectObject.h"
#include "PlayerAttack.h"
#include <Scene/SceneResource.h>
CMiniEarth::CMiniEarth()
{
	Enable(false);
	SetItemTexture("MiniEarth", TEXT("Acc/MiniEarth.png"));
	m_Type = ITEM_TYPE::Acc;
	m_Rank = ITEM_RANK::Rare;
	SetStatus("MiniEarth");
	m_ItemName = TEXT("초소형 행성");
	m_ItemText = TEXT("\"엄청난 과학력을 지닌 행성. 하지만 3개의 위성을 잃어 과학력을 잃었다\"");
}

CMiniEarth::CMiniEarth(const CMiniEarth& obj) :
	CItem(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CMiniEarth::~CMiniEarth()
{
}

void CMiniEarth::Start()
{
	CItem::Start();
}

bool CMiniEarth::Init()
{
	CItem::Init();
	m_Sprite->SetRelativeScale(0.f, 0.f, 0.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture("MiniEarth", TEXT("Acc/MiniEarth.png"));
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CMiniEarth::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);

	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CMiniEarth::PostUpdate(float DeltaTime)
{
	CItem::PostUpdate(DeltaTime);
}

void CMiniEarth::Collision(float DeltaTime)
{
	CItem::Collision(DeltaTime);
}

void CMiniEarth::Render(float DeltaTime)
{
	CItem::Render(DeltaTime);
}

CMiniEarth* CMiniEarth::Clone()
{
	return new CMiniEarth(*this);
}

void CMiniEarth::Animation2DNotify(const std::string& Name)
{
}

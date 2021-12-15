
#include "Taana.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "EffectObject.h"
#include "../BasicStatus.h"
#include "ShortSwordEffectObject.h"
#include "PlayerAttack.h"
#include <Scene/SceneResource.h>
#include "../GlobalValue.h"
#include "Player.h"
#include "../UI/UIManager.h"
CTaana::CTaana()
{
	Enable(false);
	SetItemTexture("TAANA", TEXT("Acc/TAANA.png"));
	m_Type = ITEM_TYPE::Acc;
	m_Rank = ITEM_RANK::Legend;
	SetStatus("Taana");
	m_ItemName = TEXT("TAANA");
	m_ItemText = TEXT("\"귀여운 것을 보호해주고 싶은 마음을 보호막으로 만들어주는 기계 인형\"");
}

CTaana::CTaana(const CTaana& obj) :
	CItem(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CTaana::~CTaana()
{
}

void CTaana::Enable(bool bEnable)
{
	CItem::Enable(bEnable);
	if(CUIManager::GetInst()->GetPlayerUI())
		CUIManager::GetInst()->GetPlayerUI()->SetShieldUI(bEnable);
}

void CTaana::Start()
{
	CItem::Start();
}

bool CTaana::Init()
{
	CItem::Init();
	m_Sprite->SetRelativeScale(16.f, 19.f, 0.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Animation2D = (CAnimation2D*)m_Sprite->GetAnimation2D();
	m_Animation2D->AddAnimationSequence2D("TAANAIdle", true);
	//m_Sprite->CreateAnimation2D<>()

	return true;
}

void CTaana::Update(float DeltaTime)
{
	CItem::Update(DeltaTime);

	CPlayer* Player = CGlobalValue::MainPlayer;
	Vector3 PlayerPos = Player->GetWorldPos();
	Vector3  Pos = GetWorldPos();
	Pos -= GetPivot() * GetWorldScale();
	PlayerPos -= Player->GetPivot() * Player->GetWorldScale();

	PlayerPos -= Pos;
	PlayerPos.z = 0.f;
	if (PlayerPos.Length() > 100.f)
	{
		SetWorldPos(Player->GetWorldPos());
	}
	else if (PlayerPos.Length() > 10.f)
	{
		AddWorldPos(PlayerPos * DeltaTime * 5.f);
	}
	if (0.f <= PlayerPos.x)
	{
		m_Sprite->SetHorizontalReverse2DEnable(false);
	}
	else
	{
		m_Sprite->SetHorizontalReverse2DEnable(true);
	}

	//AddRelativeRotationZ(90.f * DeltaTime);
}

void CTaana::PostUpdate(float DeltaTime)
{
	CItem::PostUpdate(DeltaTime);
}

void CTaana::Collision(float DeltaTime)
{
	CItem::Collision(DeltaTime);
}

void CTaana::Render(float DeltaTime)
{
	CItem::Render(DeltaTime);
}

CTaana* CTaana::Clone()
{
	return new CTaana(*this);
}

void CTaana::Animation2DNotify(const std::string& Name)
{
}

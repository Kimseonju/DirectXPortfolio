#include "BelialHand.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "SkelSmallDagger.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "Player.h"
#include "SkelSmallDagger.h"
#include "ProgressBarObject.h"
#include "BelialLaserBody.h"
#include "BelialLaserHead.h"
CBelialHand::CBelialHand() :
	m_Belial(nullptr),
	m_Attacking(false)
{
}

CBelialHand::CBelialHand(const CBelialHand& obj) :
	CGameObject(obj)
{
	m_Belial = nullptr;
	m_Attacking = false;
}

CBelialHand::~CBelialHand()
{
}

void CBelialHand::Start()
{
	CGameObject::Start();
}

bool CBelialHand::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);


	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->SetBaseColor(1.f, 1.f, 1.f, 0.f);
	m_Sprite->SetRelativeScale(57.f, 67.f, 1.f);
	m_Sprite->CreateAnimation2D<CAnimation2D>();
	m_Sprite->SetPivot(0.5f, 0.5f,0.f);
	m_Animation2D = (CAnimation2D*)m_Sprite->GetAnimation2D();

	m_Animation2D->AddAnimationSequence2D("BelialHand_Idle");
	m_Animation2D->AddAnimationSequence2D("BelialHand_Attack", false);
	m_Animation2D->ChangeAnimation("BelialHand_Idle");
	m_Animation2D->SetFrameEndFunction< CBelialHand>(this, &CBelialHand::AnimationFrameEnd);
	return true;
}

void CBelialHand::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

}

void CBelialHand::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	if (m_Animation2D->GetCurrentSequenceName() == "BelialHand_Attack")
	{
		m_Animation2D->SetSequencePlayRate("BelialHand_Attack", 0.5f);
		if (m_AttackMove)
		{

			CPlayer* Player = CGlobalValue::MainPlayer;
			Vector3 PlayerPos = Player->GetWorldPos();
			Vector3  Pos = GetWorldPos();
			PlayerPos -= Pos;
			PlayerPos.x = 0.f;
			AddWorldPos(PlayerPos *DeltaTime*5.f);
		}
	}
}

void CBelialHand::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBelialHand::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBelialHand* CBelialHand::Clone()
{
	return new CBelialHand(*this);
}

void CBelialHand::Animation2DNotify(const std::string& Name)
{
	if (Name == "BelialHandAttack")
	{
		Vector3 Pos = GetWorldPos();
		//손에서 레이저발사
		CBelialLaserHead* Head=m_pScene->SpawnObject<CBelialLaserHead>("BelialLaserHead");
		Head->SetWorldPos(Pos);
		bool HorizontalEnable = m_Sprite->GetHorizontalReverse2DEnable();
		if (HorizontalEnable)
		{
			Head->AddWorldPos(-15.f, 0.f, 0.f);
		}
		else
		{
			Head->AddWorldPos(15.f, 0.f, 0.f);
		}
		Head->SetHorizontalReverse2DEnable(HorizontalEnable);
		Head->LaserCollisionSetting();
		Vector3 BodyPos = Pos;
		for (int i = 1; i < 15; ++i)
		{
			std::string str = std::to_string(i);
			CBelialLaserBody* Body = m_pScene->SpawnObject<CBelialLaserBody>("BelialLaserBody"+str);
			Body->SetHorizontalReverse2DEnable(HorizontalEnable);
			
			if (HorizontalEnable)
			{
				BodyPos.x -= 32.f;
				Body->SetWorldPos(BodyPos);
			}
			else
			{
				BodyPos.x += 32.f;
				Body->SetWorldPos(BodyPos);
			}

		}
		m_AttackMove = false;
	}
}

void CBelialHand::SetBelial(CBelial* Belial)
{
	m_Belial = Belial;
}

bool CBelialHand::Attack()
{
	if (m_Animation2D->GetCurrentSequenceName() == "BelialHand_Idle")
	{
		m_Animation2D->ChangeAnimation("BelialHand_Attack");
		m_AttackMove = true;
		return true;
	}
	return false;
}

void CBelialHand::SetOpaacity(float Opacity)
{
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->SetBaseColor(1.f, 1.f, 1.f, Opacity);
}

void CBelialHand::SetHorizontalReverse2DEnable(bool Enable)
{
	if (m_Sprite)
	{
		m_Sprite->SetHorizontalReverse2DEnable(Enable);
	}
}

CMaterial* CBelialHand::GetMaterial(int Index)
{
	return m_Sprite->GetMaterial(Index);
}

void CBelialHand::StopAnimation()
{
	m_Animation2D->StopPlay();
}

void CBelialHand::AnimationFrameEnd(const std::string& Name)
{
	m_Animation2D->ChangeAnimation("BelialHand_Idle");
}

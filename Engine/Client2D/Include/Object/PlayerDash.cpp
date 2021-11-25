
#include "PlayerDash.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
CPlayerDash::CPlayerDash() :
	m_Fire(false),
	m_FireTime(0.f),
	m_FireTimeMax(0.2f),
	m_Dir(Object_Dir::End)
{
}

CPlayerDash::CPlayerDash(const CPlayerDash& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Fire = obj.m_Fire;
	m_FireTime = obj.m_FireTime;
	m_FireTimeMax = obj.m_FireTimeMax;
	m_Dir = obj.m_Dir;
}

CPlayerDash::~CPlayerDash()
{
}

void CPlayerDash::Start()
{
	CGameObject::Start();
}

bool CPlayerDash::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(19.f, 22.f, 0.f);
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->AddTexture("DashTexture", TEXT("Effect/Dash/Shadow/base_player_jump_shadow.png"));
	return true;
}

void CPlayerDash::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	if (m_Dir == Object_Dir::Left)
	{
		m_Sprite->SetHorizontalReverse2DEnable(true);
	}
	else if (m_Dir == Object_Dir::Right)
	{
		m_Sprite->SetHorizontalReverse2DEnable(false);
	}
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	SpriteMtrl->SetOpacity(SpriteMtrl->GetOpacity() - DeltaTime);
	if (SpriteMtrl->GetOpacity() < 0.f)
	{
		Active(false);
	}
}

void CPlayerDash::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CPlayerDash::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CPlayerDash::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CPlayerDash* CPlayerDash::Clone()
{
	return new CPlayerDash(*this);
}

void CPlayerDash::Animation2DNotify(const std::string& Name)
{
}

void CPlayerDash::Fire(float DeltaTime)
{
}
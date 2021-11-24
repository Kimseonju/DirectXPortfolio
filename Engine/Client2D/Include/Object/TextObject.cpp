
#include "TextObject.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "../GlobalValue.h"
#include "Player.h"
#include "../UI/TextWidget.h"
CTextObject::CTextObject():
	m_LifeTime(1.f)
{
}

CTextObject::CTextObject(const CTextObject& obj) :
	CGameObject(obj)
{
}

CTextObject::~CTextObject()
{
}

void CTextObject::Active(bool bActive)
{
	CGameObject::Active(bActive);
	m_Widget->Active(bActive);
	m_WidgetComponent->Active(bActive);
	m_RigidBodyComponent->Active(bActive);
}

void CTextObject::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Widget->Enable(bEnable);
	m_WidgetComponent->Enable(bEnable);
	m_RigidBodyComponent->Enable(bEnable);
}

void CTextObject::Start()
{
	CGameObject::Start();
}

bool CTextObject::Init()
{
	CGameObject::Init();

	m_RigidBodyComponent = CreateSceneComponent<CRigidBodyComponent>("RigidBodyComponent");
	SetRootComponent(m_RigidBodyComponent);
	m_RigidBodyComponent->SetGravityPower(100.f);
	m_WidgetComponent = CreateSceneComponent<CWidgetComponent>("Widget");
	m_WidgetComponent->SetWorldPos(0.f, 0.f, 0.f);
	m_Widget = m_WidgetComponent->CreateWidget<CTextWidget>("EnemyWorldInfoWidget");
	//m_EnemyInfoWidget->Enable(false);
	m_WidgetComponent->SetRelativePos(-90.f, -35.f, 0.f);
	//
	m_RootComponent->AddChild(m_WidgetComponent);
	m_RigidBodyComponent->SetGravityPower(200.f);
	//m_Sprite->SetRelativeRotationZ(30.f);

	return true;
}

void CTextObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_LifeTime -= DeltaTime*2.f;
	if (m_LifeTime < 0.f)
		Active(false);
	m_Widget->SetOpacity(m_LifeTime);
	AddRelativePos(m_RigidBodyComponent->GetMove());
}

void CTextObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CTextObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CTextObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CTextObject* CTextObject::Clone()
{
	return new CTextObject(*this);
}

void CTextObject::SetText(std::string Text)
{
	m_Widget->SetText(CA2T(Text.c_str()));
}

void CTextObject::Gold()
{
	m_RigidBodyComponent->SetForce2D(70.f, 50.f);
	m_RigidBodyComponent->SetGravity(true);
	m_Widget->SetColor(1.f, 1.f, 0.f);
}

void CTextObject::Damage(bool bCritical)
{
	m_RigidBodyComponent->SetForce2D(50.f, 50.f);
	m_RigidBodyComponent->SetGravity(true);
	if (bCritical)
	{
		m_Widget->SetColor(1.f, 0.f, 0.f);
	}
	else
	{

		m_Widget->SetColor(1.f, 1.f, 1.f);
	}
}



#include "ProgressBarObject.h"
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
CProgressBarObject::CProgressBarObject() 
{
}

CProgressBarObject::CProgressBarObject(const CProgressBarObject& obj) :
	CGameObject(obj)
{
}

CProgressBarObject::~CProgressBarObject()
{
}

void CProgressBarObject::Start()
{
	CGameObject::Start();
}

bool CProgressBarObject::Init()
{
	CGameObject::Init();

	m_SpriteBack = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_SpriteBar= CreateSceneComponent<CSpriteComponent>("SpriteBar");
	SetRootComponent(m_SpriteBack);

	m_SpriteBack->SetRelativeScale(20.f, 5.f, 1.f);
	m_SpriteBack->SetPivot(0.5f, 0.5f,0.f);
	m_SpriteBar->SetRelativeScale(20.f, 5.f, 1.f);
	m_SpriteBar->SetRelativePos(-10.f, -2.5f, 0.f);
	
	m_SizeBar = Vector2(20.f, 5.f);
	m_SpriteBar->AddRelativePos(0.f, -1.f, 0.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	CMaterial* material= m_SpriteBack->GetMaterial(0);
	material->AddTexture("Room", TEXT("object/door/openEffect.png"));
	material->SetBaseColor(0.f, 0.f, 0.f, 1.f);

	material = m_SpriteBar->GetMaterial(0);
	
	material->AddTexture("Room", TEXT("object/door/openEffect.png"));
	material->SetBaseColor(1.f, 0.f, 0.f, 1.f);


	m_SpriteBack->AddChild(m_SpriteBar);

	return true;
}

void CProgressBarObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CProgressBarObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CProgressBarObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CProgressBarObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CProgressBarObject* CProgressBarObject::Clone()
{
	return new CProgressBarObject(*this);
}

void CProgressBarObject::SetHPBar(float Percent)
{
	Vector2 Size = m_SizeBar;
	Size.x = Size.x * Percent;
	m_SpriteBar->SetWorldScale(Vector3(Size.x, Size.y, 0.f));

}

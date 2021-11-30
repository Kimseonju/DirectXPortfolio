
#include "KeyboardUIObject.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "../UI/EnemyWorldInfoWidget.h"
#include "../GlobalValue.h"
#include "Player.h"
CKeyboardUIObject::CKeyboardUIObject()
{
}

CKeyboardUIObject::CKeyboardUIObject(const CKeyboardUIObject& obj) :
	CGameObject(obj)
{
}

CKeyboardUIObject::~CKeyboardUIObject()
{
}

void CKeyboardUIObject::Enable(bool bEnable)
{
	CGameObject::Enable(bEnable);
	m_Sprite->Enable(bEnable);
}

void CKeyboardUIObject::Start()
{
	CGameObject::Start();
}

bool CKeyboardUIObject::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(13.f, 14.f, 1.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Sprite->AddRelativePos(0.f, -1.f, 0.f);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Default2);
	//m_Sprite->SetRelativeRotationZ(30.f);

	return true;
}

void CKeyboardUIObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CKeyboardUIObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CKeyboardUIObject::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CKeyboardUIObject::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CKeyboardUIObject* CKeyboardUIObject::Clone()
{
	return new CKeyboardUIObject(*this);
}

void CKeyboardUIObject::SetKey(const std::string& Key)
{
	CMaterial* Material = m_Sprite->GetMaterial(0);
	std::string Text = "UI/key/Keyboard_" + Key + ".png";

	Material->AddTexture("Keyboard_" + Key, CA2T(Text.c_str()));
}


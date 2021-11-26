#include "EndingCloud.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CEndingCloud::CEndingCloud()
{
}

CEndingCloud::CEndingCloud(const CEndingCloud& obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");

}

CEndingCloud::~CEndingCloud()
{
}

void CEndingCloud::Start()
{
	CGameObject::Start();
}

bool CEndingCloud::Init()
{
	CGameObject::Init();
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);


	SetRootComponent(m_Sprite);

	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);
	m_Sprite->SetWorldScale(320.f, 142.f, 0.f);
	m_Sprite->AddWorldPos(0.f, 71.f, 0.f);
	CMaterial* Material = m_Sprite->GetMaterial(0);
	Material->AddTexture("Town_BGL", TEXT("Map/Town_BGL.png"));
	return true;
}

void CEndingCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingCloud::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEndingCloud::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEndingCloud::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEndingCloud* CEndingCloud::Clone()
{
	return new CEndingCloud(*this);
}


#include "EndingCamera.h"
#include <Input.h>
#include "KeyboardUIObject.h"
#include "Player.h"
#include "../UI/UIManager.h"
CEndingCamera::CEndingCamera()
{
}

CEndingCamera::CEndingCamera(const CEndingCamera& obj)
{

}

CEndingCamera::~CEndingCamera()
{
}

void CEndingCamera::Start()
{
	CGameObject::Start();
}

bool CEndingCamera::Init()
{
	CGameObject::Init();
	m_Camera = CreateSceneComponent<CCamera>("Camera");
	m_Camera->SetWorldPos(-640.f, -320.f, 0.f);

	SetRootComponent(m_Camera);
	m_Camera->SetCameraZoom(4.f);
	return true;
}

void CEndingCamera::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CEndingCamera::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CEndingCamera::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CEndingCamera::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CEndingCamera* CEndingCamera::Clone()
{
	return new CEndingCamera(*this);
}


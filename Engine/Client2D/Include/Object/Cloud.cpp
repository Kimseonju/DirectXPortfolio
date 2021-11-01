
#include "Cloud.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include <Device.h>
#include <Scene/Scene.h>
#include <Scene/SceneResource.h>
CCloud::CCloud() :
	m_Speed(100)
{
}

CCloud::CCloud(const CCloud& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CCloud::~CCloud()
{
}

CSpriteComponent* CCloud::GetSprite()
{
	return m_Sprite;
}

void CCloud::AddTexture(const std::string& Name, const TCHAR* FileName)
{
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	SpriteMtrl->AddTexture(Name, FileName);
	CTexture* pTexture = nullptr;

	if (m_pScene)
	{
		pTexture = m_pScene->GetResource()->FindTexture(Name);
		m_Sprite->SetRelativeScale(pTexture->GetWidth()*4.f, pTexture->GetHeight() * 4.f, 1.f);
	}
}

void CCloud::Start()
{
	CGameObject::Start();
}

bool CCloud::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	Resolution RS = CDevice::GetInst()->GetResolution();
	SetRootComponent(m_Sprite);
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("FrontCloud", TEXT("TitleScene/FrontCloud.png"));

	return true;
}

void CCloud::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	Resolution RS = CDevice::GetInst()->GetResolution();
	Vector3 Pos = m_Sprite->GetRelativePos();
	if (Pos.x < -2300.f)
	{
		Pos.x += 2300.f + 2300.f;
	}
	Pos.x -= m_Speed * DeltaTime;
	m_Sprite->SetRelativePos(Pos);
}

void CCloud::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCloud::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CCloud::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CCloud* CCloud::Clone()
{
	return new CCloud(*this);
}

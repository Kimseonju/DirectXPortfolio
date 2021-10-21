
#include "BackGround_Tree.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include <Device.h>
#include <Resource/Material.h>
#include <Component/Camera.h>
#include <Scene/Scene.h>
#include <Scene/CameraManager.h>
#include <Scene/SceneResource.h>
CBackGround_Tree::CBackGround_Tree() :
	m_Pos(0.f, 0.f)
{
}

CBackGround_Tree::CBackGround_Tree(const CBackGround_Tree& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBackGround_Tree::~CBackGround_Tree()
{
}

void CBackGround_Tree::AddTexture(const std::string& Name, const TCHAR* FileName)
{
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	SpriteMtrl->AddTexture(Name, FileName);

	CTexture* Texture = nullptr;
	if (m_pScene)
	{
		Texture=m_pScene->GetResource()->FindTexture(Name);
	}
	if (Texture)
	{
		Vector3 Size;
		Resolution RS = CDevice::GetInst()->GetResolution();
		Size.x = (float)RS.Width;
		Size.y = (float)Texture->GetHeight() * 4.f;
		Size.z = 1.f;
		m_Sprite->SetRelativeScale(Size);
	}
}

void CBackGround_Tree::Start()
{
	CGameObject::Start();
}

bool CBackGround_Tree::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	SetRootComponent(m_Sprite);
	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	m_Sprite->SetPivot(0.f, 0.f, 0.f);
	//나중에수정 이쪽은
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_Particle);


	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("sky", TEXT("TitleScene/sky.png"));

	return true;
}

void CBackGround_Tree::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	CCamera* Camera=m_pScene->GetCameraManager()->GetCurrentCamera();
	Vector3 Pos=Camera->GetWorldPos();

}

void CBackGround_Tree::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBackGround_Tree::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBackGround_Tree::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBackGround_Tree* CBackGround_Tree::Clone()
{
	return new CBackGround_Tree(*this);
}

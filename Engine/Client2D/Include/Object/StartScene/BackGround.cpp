
#include "BackGround.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include <Device.h>
#include <Resource/Material.h>
CBackGround::CBackGround()
{
}

CBackGround::CBackGround(const CBackGround& obj) :
	CGameObject(obj)
{
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
}

CBackGround::~CBackGround()
{
}

void CBackGround::AddTexture(const std::string& Name, const TCHAR* FileName)
{
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	SpriteMtrl->AddTexture(Name, FileName);
}

void CBackGround::Start()
{
	CGameObject::Start();
}

bool CBackGround::Init()
{
	CGameObject::Init();

	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	Resolution RS = CDevice::GetInst()->GetResolution();

	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale((float)RS.Width, (float)RS.Height, 1.f);
	m_Sprite->SetRelativePos(0.f, 0.f, 0.f);
	m_Sprite->SetPivot(0.f, 0.f, 0.f);
	//나중에수정 이쪽은
	m_Sprite->SetRender2DType(Render_Type_2D::RT2D_MAP);


	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("sky", TEXT("TitleScene/sky.png"));

	return true;
}

void CBackGround::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CBackGround::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CBackGround::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CBackGround::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CBackGround* CBackGround::Clone()
{
	return new CBackGround(*this);
}

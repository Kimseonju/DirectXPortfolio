
#include "Viewport.h"
CViewport::CViewport() :
	m_Camera(nullptr)
{
}

CViewport::~CViewport()
{

}

void CViewport::Start()
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CViewport::Init()
{
	m_Camera = new CCamera;

	m_Camera->SetName("UICamera");
	m_Camera->m_pScene = m_Scene;

	m_Camera->Init();
	m_Camera->SetCameraType(Camera_Type::CamUI);

	m_Camera->Release();

	return true;
}

void CViewport::Update(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Update(DeltaTime);
	}
}

void CViewport::PostUpdate(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(DeltaTime);
	}
}

void CViewport::PrevRender(float DeltaTime)
{
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PrevRender(DeltaTime);
	}
}

void CViewport::Render()
{
	if (m_vecWindow.size() > 1)
	{
		std::sort(m_vecWindow.begin(), m_vecWindow.end(), CViewport::SortZOrder);
	}
	auto	iter = m_vecWindow.begin();
	auto	iterEnd = m_vecWindow.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Render();
	}
}

bool CViewport::SortZOrder(CSharedPtr<CWidgetWindow> Src, CSharedPtr<CWidgetWindow> Dest)
{
	int	SrcZ = Src->GetZOrder();
	int	DestZ = Dest->GetZOrder();

	return SrcZ < DestZ;
}

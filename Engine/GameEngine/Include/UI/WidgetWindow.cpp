
#include "WidgetWindow.h"
#include "../Scene/Viewport.h"

CWidgetWindow::CWidgetWindow() :
	m_OwnerComponent(nullptr)
{
}

CWidgetWindow::CWidgetWindow(const CWidgetWindow& widget) :
	CWidget(widget)
{
}

CWidgetWindow::~CWidgetWindow()
{
}

void CWidgetWindow::SetZOrder(int ZOrder)
{
	CWidget::SetZOrder(ZOrder);

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->SetZOrder(ZOrder);
	}
}

void CWidgetWindow::Start()
{
	CWidget::Start();

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->Start();
	}
}

bool CWidgetWindow::Init()
{
	return true;
}

void CWidgetWindow::Update(float DeltaTime)
{
	if (!m_Start)
		Start();
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		if (!(*iter)->IsStart())
			(*iter)->Start();
		(*iter)->Update(DeltaTime);
	}
}

void CWidgetWindow::PostUpdate(float DeltaTime)
{
	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->PostUpdate(DeltaTime);
	}
}

void CWidgetWindow::PrevRender(float DeltaTime)
{
	CWidget::PrevRender(DeltaTime);
}

void CWidgetWindow::Render()
{
	// 정렬한다.
	if (!IsEnable())
		return;
	if (m_vecWidget.size() > 1)
	{
		std::sort(m_vecWidget.begin(), m_vecWidget.end(), CWidgetWindow::SortZOrder);
	}

	auto	iter = m_vecWidget.begin();
	auto	iterEnd = m_vecWidget.end();

	for (; iter != iterEnd; ++iter)
	{
		
		(*iter)->Render();
	}
}

CWidgetWindow* CWidgetWindow::Clone()
{
	return new CWidgetWindow(*this);
}

void CWidgetWindow::CallAnimNotify(const std::string& Name)
{
}

bool CWidgetWindow::SortZOrder(CSharedPtr<CWidget> Src,
	CSharedPtr<CWidget> Dest)
{
	int	SrcZ = Src->GetZOrder();
	int	DestZ = Dest->GetZOrder();

	return SrcZ < DestZ;
}
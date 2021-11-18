
#include "ShopInfoWidget.h"
#include "UI/Image.h"
#include "UI/Text.h"
CShopInfoWidget::CShopInfoWidget() :
	m_ItemName(nullptr)
{
}

CShopInfoWidget::CShopInfoWidget(const CShopInfoWidget& widget) :
	CWidgetWindow(widget)
{
}

CShopInfoWidget::~CShopInfoWidget()
{
}

bool CShopInfoWidget::Init()
{
	CWidgetWindow::Init();

	SetSize(410.f, 105.f);



	return true;
}

void CShopInfoWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CShopInfoWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CShopInfoWidget::Render()
{
	CWidgetWindow::Render();
}

CShopInfoWidget* CShopInfoWidget::Clone()
{
	return new CShopInfoWidget(*this);
}

void CShopInfoWidget::SetItemNameText(const TCHAR* Text)
{
	m_ItemName->SetText(Text);
}

void CShopInfoWidget::SetItemPrice(const TCHAR* Text)
{
	m_ItemPrice->SetText(Text);
}

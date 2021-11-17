
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



	m_ItemName = CreateWidget<CText>("ItemName");
	m_ItemName->SetSize(400.f, 105.f);
	m_ItemName->SetPos(0.f, 100.f);
	m_ItemName->SetFontSize(17.f);
	m_ItemName->SetAlignH(TEXT_ALIGN_H::Center);
	m_ItemName->SetAlignV(TEXT_ALIGN_V::Top);
	m_ItemName->SetText(TEXT("¼ô¼Òµå"));
	m_ItemName->SetFont("DungreedFont");




	m_ItemPrice = CreateWidget<CText>("ItemBuyCoin");
	m_ItemPrice->SetSize(150.f, 100.f);
	m_ItemPrice->SetPos(160.f, 0.f);
	m_ItemPrice->SetFontSize(15.f);
	m_ItemPrice->SetColor(1.f, 1.f, 0.f);
	m_ItemPrice->SetText(TEXT("8888"));
	m_ItemPrice->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ItemPrice->SetAlignH(TEXT_ALIGN_H::Right);
	m_ItemPrice->SetFont("DungreedFont");
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

#include "TextWidget.h"

CTextWidget::CTextWidget()
{
}

CTextWidget::CTextWidget(const CTextWidget& widget) :
	CWidgetWindow(widget)
{
}

CTextWidget::~CTextWidget()
{
}

bool CTextWidget::Init()
{
	CWidgetWindow::Init();

	m_Text = CreateWidget<CText>("OutputText");

	m_Text->SetPos(0.f, 0.f);
	m_Text->SetSize(70.f, 20.f);

	m_Text->SetAlignH(TEXT_ALIGN_H::Center);
	m_Text->SetFontSize(30.f);
	//m_Text->SetFont("DungreedFont");
	m_Text->SetCollision(false);
	return true;
}

void CTextWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CTextWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CTextWidget::Render()
{
	CWidgetWindow::Render();
}

CTextWidget* CTextWidget::Clone()
{
	return new CTextWidget(*this);
}

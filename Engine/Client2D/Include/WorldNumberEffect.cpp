#include "WorldNumberEffect.h"

CWorldNumberEffect::CWorldNumberEffect()
{
}

CWorldNumberEffect::CWorldNumberEffect(const CWorldNumberEffect& widget) :
	CWidgetWindow(widget)
{
}

CWorldNumberEffect::~CWorldNumberEffect()
{
}

bool CWorldNumberEffect::Init()
{
	CWidgetWindow::Init();
	SetCollision(false);
	m_Text = CreateWidget<CText>("Name");
	m_Text->SetText(TEXT(""));
	m_Text->SetPos(0.f, 25.f);
	m_Text->SetSize(200.f, 50.f);
	m_Text->SetFontSize(15.f);
	m_Text->SetShadowEnable(true);
	m_Text->SetShadowColor(1.f, 1.f, 0.f);
	m_Text->SetShadowAlphaEnable(true);
	m_Text->SetShadowOpacity(0.5f);
	return true;
}

void CWorldNumberEffect::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CWorldNumberEffect::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CWorldNumberEffect::Render()
{
	CWidgetWindow::Render();
}

CWorldNumberEffect* CWorldNumberEffect::Clone()
{
	return new CWorldNumberEffect(*this);
}

void CWorldNumberEffect::SetIntText(int number)
{
	std::string str=std::to_string(number);

}

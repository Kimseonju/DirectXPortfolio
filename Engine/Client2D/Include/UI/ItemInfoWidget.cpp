
#include "ItemInfoWidget.h"
#include "UI/Image.h"
#include "UI/Text.h"
CItemInfoWidget::CItemInfoWidget()
{
}

CItemInfoWidget::CItemInfoWidget(const CItemInfoWidget& widget) :
	CWidgetWindow(widget)
{
}

CItemInfoWidget::~CItemInfoWidget()
{
}

void CItemInfoWidget::Active(bool bActive)
{
	CWidgetWindow::Active(bActive);

	m_Base->Active(bActive);
	m_ItemImageBase->Active(bActive);
	m_ItemImage->Active(bActive);
	m_AttackDamageText->Active(bActive);
	m_AttackSpeedText->Active(bActive);
	m_ItemName->Active(bActive);
	m_AttackDamage->Active(bActive);
	m_AttackSpeed->Active(bActive);
	m_ItemRank->Active(bActive);
	m_ItemType->Active(bActive);
	m_ItemText->Active(bActive);
	m_Base->Active(bActive);
}

bool CItemInfoWidget::Init()
{
	CWidgetWindow::Init();

	SetSize(400.f, 270.f);
	m_Base = CreateWidget<CImage>("Base");
	m_Base->SetSize(400.f, 270.f);
	m_Base->SetColorTint(34.f/255.f, 32.f / 255.f, 52.f / 255.f, 0.9f);
	m_Base->SetPos(0.f, 0.f);

	m_ItemImageBase = CreateWidget<CImage>("ItemImageBase");
	m_ItemImageBase->SetSize(76.f, 76.f);
	m_ItemImageBase->SetTexture("ItemInfoBase", TEXT("UI/Inventory/info.png"));
	m_ItemImageBase->SetPos(10.f,130.f);

	Vector2 ItemImageBaseSize = m_ItemImageBase->GetSize();
	ItemImageBaseSize /= 2.f;
	m_ItemImage = CreateWidget<CImage>("ItemImage");
	m_ItemImage->SetSize(57.f, 57.f);
	m_ItemImage->SetColorTint(1.f, 1.f, 1.f, 1.f);
	m_ItemImage->SetPos(10.f+ ItemImageBaseSize.x, 130.f+ ItemImageBaseSize.y);
	m_ItemImage->SetZOrder(1);
	m_ItemImage->SetPivot(0.5f, 0.5f);

	m_ItemName = CreateWidget<CText>("ItemName");
	m_ItemName->SetSize(400.f, 265.f);
	m_ItemName->SetFontSize(35.f);
	m_ItemName->SetAlignH(TEXT_ALIGN_H::Center);
	m_ItemName->SetAlignV(TEXT_ALIGN_V::Top);
	m_ItemName->SetText(TEXT("숏소드"));
	m_ItemName->SetFont("DungreedFont");



	m_AttackDamageText = CreateWidget<CText>("AttackDamageText");
	m_AttackDamageText->SetSize(100.f, 100.f);
	m_AttackDamageText->SetPos(100.f, 130.f);
	m_AttackDamageText->SetFontSize(15.f);
	m_AttackDamageText->SetText(TEXT("공격력 :"));
	m_AttackDamageText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_AttackDamageText->SetFont("DungreedFont");

	m_AttackDamage = CreateWidget<CText>("AttackDamage");
	m_AttackDamage->SetSize(150.f, 100.f);
	m_AttackDamage->SetPos(160.f, 130.f);
	m_AttackDamage->SetFontSize(15.f);
	m_AttackDamage->SetColor(1.f, 1.f, 0.f);
	m_AttackDamage->SetText(TEXT("8~10"));
	m_AttackDamage->SetAlignV(TEXT_ALIGN_V::Middle);
	m_AttackDamage->SetFont("DungreedFont");



	m_AttackSpeedText = CreateWidget<CText>("AttackSpeedText");
	m_AttackSpeedText->SetPos(100.f, 108.f);
	m_AttackSpeedText->SetSize(200.f, 100.f);
	m_AttackSpeedText->SetFontSize(15.f);
	m_AttackSpeedText->SetText(TEXT("초당 공격 횟수 :"));
	m_AttackSpeedText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_AttackSpeedText->SetFont("DungreedFont");

	m_AttackSpeed = CreateWidget<CText>("AttackSpeed");
	m_AttackSpeed->SetPos(210.f, 108.f);
	m_AttackSpeed->SetSize(200.f, 100.f);
	m_AttackSpeed->SetColor(1.f, 1.f, 0.f);
	m_AttackSpeed->SetAlignV(TEXT_ALIGN_V::Middle);
	m_AttackSpeed->SetText(TEXT("3.03"));
	m_AttackSpeed->SetFontSize(15.f);
	m_AttackSpeed->SetFont("DungreedFont");


	m_ItemRank = CreateWidget<CText>("ItemInfo");
	m_ItemRank->SetPos(10.f, 65.f);
	m_ItemRank->SetSize(380.f, 100.f);
	m_ItemRank->SetColor(unsigned char(160), unsigned char(0), unsigned char(160));
	m_ItemRank->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ItemRank->SetFontSize(15.f);
	m_ItemRank->SetText(TEXT("일반 아이템"));
	m_ItemRank->SetFont("DungreedFont");

	m_ItemType = CreateWidget<CText>("ItemInfoType");
	m_ItemType->SetPos(10.f, 43.f);
	m_ItemType->SetSize(380.f, 100.f);
	m_ItemType->SetColor(unsigned char(160), unsigned char(0), unsigned char(160));
	m_ItemType->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ItemType->SetFontSize(15.f);
	m_ItemType->SetText(TEXT("한손 (주무기)"));
	m_ItemType->SetFont("DungreedFont");


	m_ItemText = CreateWidget<CText>("ItemText");
	m_ItemText->SetPos(10.f, 21.f);
	m_ItemText->SetSize(380.f, 100.f);
	m_ItemText->SetColor(unsigned char(120), unsigned char(240), unsigned char(215));
	m_ItemText->SetAlignV(TEXT_ALIGN_V::Middle);
	m_ItemText->SetFontSize(15.f);
	m_ItemText->SetText(TEXT("가볍고 휘두르기 편한"));
	m_ItemText->SetFont("DungreedFont");
	return true;
}

void CItemInfoWidget::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);
}

void CItemInfoWidget::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CItemInfoWidget::Render()
{
	CWidgetWindow::Render();
}

CItemInfoWidget* CItemInfoWidget::Clone()
{
	return new CItemInfoWidget(*this);
}

void CItemInfoWidget::SetItemNameText(const TCHAR* Text)
{
	m_ItemName->SetText(Text);
}

void CItemInfoWidget::SetAttackDamageText(int Min, int Max)
{
	std::wstring str;
	str = std::to_wstring(Min)+TEXT(" ~ ")+std::to_wstring(Max);
	
	m_AttackDamage->SetText(str.c_str());
}

void CItemInfoWidget::SetAttackSpeedText(float Speed)
{
	std::wstring str;
	str = std::to_wstring(Speed);

	m_AttackSpeed->SetText(str.c_str());
}

void CItemInfoWidget::SetItemRankText(const TCHAR* Text)
{
	m_ItemRank->SetText(Text);
}

void CItemInfoWidget::SetItemTypeText(const TCHAR* Text)
{
	m_ItemType->SetText(Text);
}

void CItemInfoWidget::SetItemText(const TCHAR* Text)
{
	m_ItemText->SetText(Text);
}

void CItemInfoWidget::SetImage(CTexture* Texture)
{
	m_ItemImage->SetTexture(Texture);
}


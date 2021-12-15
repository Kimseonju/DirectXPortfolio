#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "../GlobalValue.h"
class CItemInfoWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CSharedPtr<CImage> m_Base;
    CSharedPtr<CImage> m_ItemImageBase;
    CSharedPtr<CImage> m_ItemImage;
    CSharedPtr<CText> m_AttackDamageText;
    CSharedPtr<CText> m_AttackSpeedText;
    CSharedPtr<CText> m_ItemName;
    CSharedPtr<CText> m_AttackDamage;
    CSharedPtr<CText> m_AttackSpeed;
    CSharedPtr<CText> m_ItemRank;
    CSharedPtr<CText> m_ItemType;
    CSharedPtr<CText> m_ItemText;
    ITEM_TYPE m_Type;
protected:
    CItemInfoWidget();
    CItemInfoWidget(const CItemInfoWidget& widget);
    virtual ~CItemInfoWidget();

public:
    virtual void Active(bool bActive);
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CItemInfoWidget* Clone();
public:
    //아이템이름
    void SetItemNameText(const TCHAR* Text, ITEM_TYPE Type);
    //데미지 최소 ~ 최대 //악세사리에서는 데미지가 아닌 방어력
    void SetAttackDamageText(int Min, int Max, const TCHAR* Text = TEXT("공격력 :"));
    //공격속도//악세사리에서는  위력 n은 소수점
    void SetAttackSpeedText(float Speed, const TCHAR* Text=TEXT("초당 공격 횟수 :"), int n=2);
    //아이템등급
    void SetItemRankText(const TCHAR* Text);
    //아이템타입(한손검 두손검)
    void SetItemTypeText(const TCHAR* Text);
    //아이템설명
    void SetItemText(const TCHAR* Text);

    void SetImage(CTexture* Texture);
};


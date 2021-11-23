#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CItemInfoWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CImage* m_Base;
    CImage* m_ItemImageBase;
    CImage* m_ItemImage;
    CText* m_AttackDamageText;
    CText* m_AttackSpeedText;
    CText* m_ItemName;
    CText* m_AttackDamage;
    CText* m_AttackSpeed;
    CText* m_ItemRank;
    CText* m_ItemType;
    CText* m_ItemText;

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
    void SetItemNameText(const TCHAR* Text);
    //데미지 최소 ~ 최대
    void SetAttackDamageText(int Min, int Max);
    //공격속도
    void SetAttackSpeedText(float Speed);
    //아이템등급
    void SetItemRankText(const TCHAR* Text);
    //아이템타입(한손검 두손검)
    void SetItemTypeText(const TCHAR* Text);
    //아이템설명
    void SetItemText(const TCHAR* Text);

    void SetImage(CTexture* Texture);
};


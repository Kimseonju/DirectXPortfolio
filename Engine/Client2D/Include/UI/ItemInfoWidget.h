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
    //�������̸�
    void SetItemNameText(const TCHAR* Text);
    //������ �ּ� ~ �ִ�
    void SetAttackDamageText(int Min, int Max);
    //���ݼӵ�
    void SetAttackSpeedText(float Speed);
    //�����۵��
    void SetItemRankText(const TCHAR* Text);
    //������Ÿ��(�Ѽհ� �μհ�)
    void SetItemTypeText(const TCHAR* Text);
    //�����ۼ���
    void SetItemText(const TCHAR* Text);

    void SetImage(CTexture* Texture);
};


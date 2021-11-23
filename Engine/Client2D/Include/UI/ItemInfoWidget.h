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


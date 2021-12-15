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
    //�������̸�
    void SetItemNameText(const TCHAR* Text, ITEM_TYPE Type);
    //������ �ּ� ~ �ִ� //�Ǽ��縮������ �������� �ƴ� ����
    void SetAttackDamageText(int Min, int Max, const TCHAR* Text = TEXT("���ݷ� :"));
    //���ݼӵ�//�Ǽ��縮������  ���� n�� �Ҽ���
    void SetAttackSpeedText(float Speed, const TCHAR* Text=TEXT("�ʴ� ���� Ƚ�� :"), int n=2);
    //�����۵��
    void SetItemRankText(const TCHAR* Text);
    //������Ÿ��(�Ѽհ� �μհ�)
    void SetItemTypeText(const TCHAR* Text);
    //�����ۼ���
    void SetItemText(const TCHAR* Text);

    void SetImage(CTexture* Texture);
};


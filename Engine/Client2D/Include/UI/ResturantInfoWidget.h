#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CResturantInfoWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CSharedPtr<CImage> m_Base;
    CSharedPtr<CText> m_FoodName;
    CSharedPtr<CText> m_FoodDescription;
    CSharedPtr<CText> m_OneNumber;
    CSharedPtr<CText> m_OneDescription;
    CSharedPtr<CText> m_TwoNumber;
    CSharedPtr<CText> m_TwoDescription;
    CSharedPtr<CImage> m_GoldImage;
    CSharedPtr<CText> m_GoldPrice;
    CSharedPtr<CImage> m_SatietyImage;
    CSharedPtr<CText> m_SatietyNumber;


protected:
    CResturantInfoWidget();
    CResturantInfoWidget(const CResturantInfoWidget& widget);
    virtual ~CResturantInfoWidget();

public:
    virtual void Active(bool bActive);
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CResturantInfoWidget* Clone();
public:
    //�������̸�
    void SetFoodName(const TCHAR* Text);
    void SetFoodDescription(const TCHAR* Text);
    //ù��°ȿ��,����
    void SetOneNumber(int Number);
    void SetOneDescription(const TCHAR* Text);
    //�ι�°ȿ��,����
    void SetTwoNumber(int Number);
    void SetTwoDescription(const TCHAR* Text);
    //����
    void SetPrice(int Price);
    //�����ä�����³ѹ�
    void SetSatietyNumber(int Number);
};


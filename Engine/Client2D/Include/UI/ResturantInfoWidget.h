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
    //아이템이름
    void SetFoodName(const TCHAR* Text);
    void SetFoodDescription(const TCHAR* Text);
    //첫번째효과,설명
    void SetOneNumber(int Number);
    void SetOneDescription(const TCHAR* Text);
    //두번째효과,설명
    void SetTwoNumber(int Number);
    void SetTwoDescription(const TCHAR* Text);
    //가격
    void SetPrice(int Price);
    //배고픔채워지는넘버
    void SetSatietyNumber(int Number);
};


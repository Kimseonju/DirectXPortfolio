#pragma once
#include "UI/WidgetWindow.h"
#include "../GlobalValue.h"
#include <UI/Text.h>
#include <UI/Button.h>
#include <UI/Image.h>
class CAbilityWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CAbilityWidget();
    CAbilityWidget(const CAbilityWidget& widget);
    virtual ~CAbilityWidget();
    
private:
    CImage* m_AbilityBase;
    CText* m_AbilityName;
    CText* m_AbilityPoint;
    CText* m_AbilityStatus1;//�Ʒ�ĭ
    CText* m_AbilityStatusText1;//�Ʒ�ĭ
    CText* m_AbilityStatus2;//��ĭ
    CText* m_AbilityStatusText2;//��ĭ



    CText* m_PointFiveText;
    CText* m_PointTenText;
    CText* m_PointTwentyText;
    CImage* m_FivePointImage;
    CImage* m_TenPointImage;
    CImage* m_TwentyPointImage;

    CButton* m_PointPlusButton;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CAbilityWidget* Clone();

};


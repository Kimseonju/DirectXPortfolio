#pragma once

#include "UI/WidgetWindow.h"

class CRestaurantUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    class CImage* m_BackGround;
    class CImage* m_Label;
    class CImage* m_RestaurantTable;
    class CImage* m_AltarGaugeBase;
    class CImage* m_AltarGaugeIcon;
    class CImage* m_BaseTable;
    class CImage* m_FoodSelectBase;
protected:
    CRestaurantUI();
    virtual ~CRestaurantUI();
public:\
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CRestaurantUI* Clone();
    
};


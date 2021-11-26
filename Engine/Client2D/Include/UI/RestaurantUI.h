#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"

class CRestaurantUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage>    m_BackGround;
    CSharedPtr<CImage>    m_Label;
    CSharedPtr<CImage>    m_RestaurantTable;
    CSharedPtr<CImage>    m_AltarGaugeBase;
    CSharedPtr<CImage>    m_AltarGaugeIcon;
    CSharedPtr<CImage>    m_BaseTable;
    CSharedPtr<CImage>    m_FoodSelectBase;
protected:
    CRestaurantUI();
    virtual ~CRestaurantUI();
public:
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CRestaurantUI* Clone();
    
};


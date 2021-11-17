#pragma once
#include "UI/WidgetWindow.h"
#include "../GlobalValue.h"
class CShopButton;
class CImage;
class CShopUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CImage* m_BaseImage;
    std::vector<CShopButton*> m_ShopItem;
    CShopButton* m_ShopUIButton;
protected:
    CShopUI();
    virtual ~CShopUI();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CShopUI* Clone();
};


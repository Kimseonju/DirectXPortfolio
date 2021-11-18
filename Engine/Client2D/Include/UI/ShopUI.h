#pragma once
#include "UI/WidgetWindow.h"
#include "../GlobalValue.h"
#include <UI/Text.h>
#include <UI/Image.h>
#include "ShopButton.h"

struct ShopItemInfo
{
    CItem* Item;
    CImage* ItemImage;
    CShopButton* ShopButton;
    CText* ItemName;
    CText* ItemPrice;
    void Enable(bool bEnable)
    {
        ItemImage->Enable(bEnable);
        ShopButton->Enable(bEnable);
        ItemName->Enable(bEnable);
        ItemPrice->Enable(bEnable);

    }
    void Active(bool bActive)
    {
        ItemImage->Active(bActive);
        ShopButton->Active(bActive);
        ItemName->Active(bActive);
        ItemPrice->Active(bActive);
    }
};

class CShopUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CImage* m_BaseImage;
    std::vector<ShopItemInfo> m_ShopItemInfo;
protected:
    CShopUI();
    virtual ~CShopUI();

public:
    virtual void Enable(bool bEnable);
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CShopUI* Clone();
public:
    void ShopButtonClick();
};


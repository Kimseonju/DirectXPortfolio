#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CShopInfoWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CText* m_ItemName;
    CText* m_ItemPrice;

protected:
    CShopInfoWidget();
    CShopInfoWidget(const CShopInfoWidget& widget);
    virtual ~CShopInfoWidget();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CShopInfoWidget* Clone();
public:
    //�������̸�
    void SetItemNameText(const TCHAR* Text);
    //����
    void SetItemPrice(const TCHAR* Text);

};


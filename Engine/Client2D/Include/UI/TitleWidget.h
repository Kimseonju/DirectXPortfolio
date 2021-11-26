#pragma once

#include "UI/WidgetWindow.h"
#include <UI/Text.h>
#include <UI/Image.h>

class CTitleWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage> m_Cloud;
    CSharedPtr<CImage> m_BackCloud;

protected:
    CTitleWidget();
    CTitleWidget(const CTitleWidget& widget);
    virtual ~CTitleWidget();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CTitleWidget* Clone();

private:
    void StartButtonClick();
    void ExitButtonClick();
};


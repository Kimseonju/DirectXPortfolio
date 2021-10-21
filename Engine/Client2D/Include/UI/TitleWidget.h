#pragma once

#include "UI/WidgetWindow.h"

class CTitleWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    class CImage* m_Cloud;
    class CImage* m_BackCloud;

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


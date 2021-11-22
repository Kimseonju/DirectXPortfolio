#pragma once
#include "UI\WidgetWindow.h"
#include <UI/Text.h>
#include <UI/ProgressBar.h>
class CTextWidget :
    public CWidgetWindow
{

public:
    CTextWidget();
    CTextWidget(const CTextWidget& widget);
    ~CTextWidget();

private:
    CSharedPtr<CText> m_Text;

public:
    void SetText(const TCHAR* text)
    {
        m_Text->SetText(text);
    }
    void SetColor(float r, float g ,float b)
    {
        m_Text->SetColor(r, g, b);
    }
    void SetOpacity(float Alpha)
    {
        m_Text->SetAlphaEnable(true);
        m_Text->SetOpacity(Alpha);
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CTextWidget* Clone();
};


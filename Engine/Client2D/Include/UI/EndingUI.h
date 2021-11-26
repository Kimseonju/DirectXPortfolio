#pragma once

#include "UI/WidgetWindow.h"
#include <UI/Text.h>
#include <UI/Image.h>

class CEndingUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage> m_MapBase;
    CSharedPtr<CImage> m_Logo;
    CSharedPtr<CText> m_Text;
protected:
    CEndingUI();
    virtual ~CEndingUI();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CEndingUI* Clone();
};


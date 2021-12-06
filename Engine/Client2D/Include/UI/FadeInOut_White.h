#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "../GlobalValue.h"

class CFadeInOut_White :
    public CWidgetWindow
{
    friend class CViewport;

private:

    CSharedPtr<CImage>    m_FadeImage;
    float m_Alpha;
    bool m_FadeOut;
    bool m_FadeIn;
protected:
    CFadeInOut_White();
    virtual ~CFadeInOut_White();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CFadeInOut_White* Clone();

    void SetFadeIn();
    void SetFadeOut();
    bool IsFadeIn();
    bool IsFadeOut();
};


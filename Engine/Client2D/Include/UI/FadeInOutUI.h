#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CFadeInOutUI :
    public CWidgetWindow
{
    friend class CViewport;

private:

    CSharedPtr<CImage>    m_FadeImage;
    float m_Alpha;
protected:
    CFadeInOutUI();
    virtual ~CFadeInOutUI();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CFadeInOutUI* Clone();
public:
    void SetPadeIn();
    void SetPadeOut();
    bool IsFadeIn();
    bool IsFadeOut();
};


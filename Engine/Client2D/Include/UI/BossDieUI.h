#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CBossDieUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage>    m_Image;
    float m_Alpha;
public:
    CBossDieUI();
    CBossDieUI(const CBossDieUI& widget);
    virtual ~CBossDieUI();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void PrevRender(float DeltaTime);
    virtual void Render();
    virtual CBossDieUI* Clone();
};


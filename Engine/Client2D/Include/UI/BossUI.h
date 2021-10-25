#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CBossUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage>    m_BossProgressBarBase;
    CSharedPtr<CImage>    m_BossProgressBarBack;
    CSharedPtr<CImage>    m_BossPortrait;
    CSharedPtr<CProgressBar>    m_BossProgressBar;
public:
    CBossUI();
    CBossUI(const CBossUI& widget);
    virtual ~CBossUI();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CBossUI* Clone();

};


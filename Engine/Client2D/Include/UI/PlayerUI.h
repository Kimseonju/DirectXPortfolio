#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CPlayerUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    
    CSharedPtr<CProgressBar>    m_ProgressBar;

protected:
    CPlayerUI();
    CPlayerUI(const CPlayerUI& widget);
    virtual ~CPlayerUI();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerUI* Clone();

};


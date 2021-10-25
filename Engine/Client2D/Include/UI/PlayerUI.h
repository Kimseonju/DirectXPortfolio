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

private:
    
    CSharedPtr<CProgressBar>    m_ProgressBar;

    CSharedPtr<CImage>    m_WarningOnHit0;
    CSharedPtr<CImage>    m_WarningOnHit1;
    class CBossUI* m_BossUI;
    float m_HitTime;
protected:
    CPlayerUI();
    virtual ~CPlayerUI();
public:
    void Hit();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerUI* Clone();

};


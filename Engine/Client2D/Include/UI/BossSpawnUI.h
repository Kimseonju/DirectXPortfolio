#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CBossSpawnUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CSharedPtr<CImage>    m_BossUpDonwImage;
    CSharedPtr<CImage>    m_BossBar;
    CSharedPtr<CImage>    m_BossPortrait;
    CSharedPtr<CProgressBar>    m_BossProgressBar;
    bool m_Spawn;
    float m_Alpha;
public:
    CBossSpawnUI();
    CBossSpawnUI(const CBossSpawnUI& widget);
    virtual ~CBossSpawnUI();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CBossSpawnUI* Clone();
public:
    void Spawn();
};


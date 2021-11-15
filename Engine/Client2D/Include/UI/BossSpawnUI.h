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
    CSharedPtr<CImage>    m_BossUpImage;
    CSharedPtr<CImage>    m_BossDonwImage;
    CSharedPtr<CText>    m_BossName;
    CSharedPtr<CText>    m_BossNinkName;
    bool m_Spawn;
    float m_Alpha;
    float m_NickNameAlpha;
    bool m_Play;
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


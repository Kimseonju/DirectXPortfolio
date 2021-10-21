#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CMainHUDWidget :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CMainHUDWidget();
    CMainHUDWidget(const CMainHUDWidget& widget);
    virtual ~CMainHUDWidget();
    class CPlayer* m_Player;
private:
    CSharedPtr<CText>   m_Text;
    float   m_Time;
    int m_Index;

    CSharedPtr<CProgressBar>    m_ProgressBar;
    float   m_TestPercent;
public:
    void SetPlayer(class CPlayer* Player)
    {
        m_Player = Player;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMainHUDWidget* Clone();

private:
    void StartClick();
};


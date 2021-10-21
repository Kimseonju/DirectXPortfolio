#pragma once
#include "UI\WidgetWindow.h"
#include <UI/Text.h>
#include <UI/ProgressBar.h>
class CEnemyWorldInfoWidget :
    public CWidgetWindow
{

public:
    CEnemyWorldInfoWidget();
    CEnemyWorldInfoWidget(const CEnemyWorldInfoWidget& widget);
    ~CEnemyWorldInfoWidget();

private:
    CSharedPtr<CText>        m_NameText;
    CSharedPtr<CProgressBar> m_HPBar;

public:
    void SetHPBar(float Percent)
    {
        m_HPBar->SetPercent(Percent);
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CEnemyWorldInfoWidget* Clone();
};


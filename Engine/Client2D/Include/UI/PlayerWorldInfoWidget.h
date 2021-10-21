#pragma once

#include "UI\WidgetWindow.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CPlayerWorldInfoWidget :
    public CWidgetWindow
{
public:
    CPlayerWorldInfoWidget();
    CPlayerWorldInfoWidget(const CPlayerWorldInfoWidget& widget);
    virtual ~CPlayerWorldInfoWidget();

private:
    CSharedPtr<CText>   m_NameText;
    CSharedPtr<CProgressBar>    m_HPBar;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerWorldInfoWidget* Clone();
};


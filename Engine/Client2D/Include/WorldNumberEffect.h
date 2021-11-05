#pragma once
#include "UI\WidgetWindow.h"
#include <UI/Text.h>
#include <UI/ProgressBar.h>
class CWorldNumberEffect :
    public CWidgetWindow
{

public:
    CWorldNumberEffect();
    CWorldNumberEffect(const CWorldNumberEffect& widget);
    ~CWorldNumberEffect();

private:
    CSharedPtr<CText>        m_Text;


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CWorldNumberEffect* Clone();
public:

    void SetIntText(int number);
};


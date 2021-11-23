#pragma once
#include "UI\WidgetWindow.h"
#include <UI/Text.h>
#include <UI/Image.h>
class CPlayerWorldWidget :
    public CWidgetWindow
{

public:
    CPlayerWorldWidget();
    CPlayerWorldWidget(const CPlayerWorldWidget& widget);
    ~CPlayerWorldWidget();

private:
    CSharedPtr<CImage> m_ReloadBar;
    CSharedPtr<CImage> m_ReloadBase;
    CSharedPtr<CImage> m_ReloadEffect;

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerWorldWidget* Clone();
public:

    void SetPercentBar(float Percent);

    void AnimationFrameEnd(const std::string& Name);
    void EffectStart();
};


#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Image.h"

class CLoadingUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CLoadingUI();
    CLoadingUI(const CLoadingUI& widget);
    virtual ~CLoadingUI();

private:
    CSharedPtr<CProgressBar>    m_LoadingBar;
    CSharedPtr<CImage>    m_LoadingImage0;
    CSharedPtr<CImage>    m_LoadingImage1;
    CSharedPtr<CImage>    m_LoadingImage2;
    int m_ImageNum;
    float m_ImageCount;
    float   m_LoadingPercent;
public:
    void SetPercent(float Percent)
    {
        m_LoadingBar->SetPercent(Percent);
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CLoadingUI* Clone();
};


#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "../GlobalValue.h"

class CFadeInOutUI :
    public CWidgetWindow
{
    friend class CViewport;

private:

    CSharedPtr<CImage>    m_FadeImage;
    Stage_Dir m_StageDir;
    float m_Alpha;
    bool m_FadeOut;
    bool m_FadeIn;
    bool m_StageMove;
protected:
    CFadeInOutUI();
    virtual ~CFadeInOutUI();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CFadeInOutUI* Clone();
public:
    void StageMoveIn(Stage_Dir Dir);

    void SetPadeIn();
    void SetPadeOut();
    bool IsFadeIn();
    bool IsFadeOut();
};


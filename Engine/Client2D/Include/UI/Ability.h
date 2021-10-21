#pragma once
#include "UI/WidgetWindow.h"
#include "../GlobalValue.h"
class CImage;
class CText;
class CAbility :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CAbility();
    CAbility(const CAbility& widget);
    virtual ~CAbility();
    CWidgetWindow* m_Wrath; //분노
    CWidgetWindow* m_Swiftness; //신속
    CWidgetWindow* m_Patience; //인내
    CWidgetWindow* m_Arcane; //신비
    CWidgetWindow* m_Greed; //탐욕

    //훈련텍스트
    CImage* m_MouseButtonImage;
    CText* m_MouseButtonText;
    //초기화 텍스트
    CImage* m_ResetKeyImage;
    CImage* m_ResetKeyText;

    CImage* m_ExitKeyImage;
    CImage* m_ExitKeyText;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CAbility* Clone();

};


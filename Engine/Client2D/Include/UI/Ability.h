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
    CWidgetWindow* m_Wrath; //�г�
    CWidgetWindow* m_Swiftness; //�ż�
    CWidgetWindow* m_Patience; //�γ�
    CWidgetWindow* m_Arcane; //�ź�
    CWidgetWindow* m_Greed; //Ž��

    //�Ʒ��ؽ�Ʈ
    CImage* m_MouseButtonImage;
    CText* m_MouseButtonText;
    //�ʱ�ȭ �ؽ�Ʈ
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


#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CStatusUI :
    public CWidgetWindow
{
    friend class CViewport;

private:

    CSharedPtr<CImage>    m_BasicImage;
    CSharedPtr<CText>    m_BasicText;


    CSharedPtr<CImage>    m_DamageImage;
    CSharedPtr<CImage>    m_ArmorImage;
    CSharedPtr<CImage>    m_CriticalImage;
    CSharedPtr<CImage>    m_MoveSpeedImage;
    CSharedPtr<CImage>    m_AttackSpeedImage;
    CSharedPtr<CImage>    m_ReloadSpeedImage;

    CSharedPtr<CText>    m_DamageText;
    CSharedPtr<CText>    m_DamageMiddleText;
    CSharedPtr<CText>    m_DamageMaxText;
    CSharedPtr<CText>    m_ArmorText;
    CSharedPtr<CText>    m_CriticalText;
    CSharedPtr<CText>    m_MoveSpeedText;
    CSharedPtr<CText>    m_AttackSpeedText;
    CSharedPtr<CText>    m_ReloadSpeedText;
    
    class CBossUI* m_BossUI;
    class CWeaponUI* m_PlayerWeaponUI;
    float m_HitTime;

protected:
    CStatusUI();
    virtual ~CStatusUI();
public:
    virtual void Enable(bool bEnable);
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CStatusUI* Clone();
};


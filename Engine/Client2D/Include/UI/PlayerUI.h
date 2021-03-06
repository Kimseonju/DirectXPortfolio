#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"

class CPlayerUI :
    public CWidgetWindow
{
    friend class CViewport;

private:
    
    CSharedPtr<CProgressBar>    m_ProgressBar;
    CSharedPtr<CImage>    m_HPLifeWave;
    CSharedPtr<CText>     m_HPText;
    CSharedPtr<CText>     m_HPMiddleText;
    CSharedPtr<CText>     m_HPMaxText;
    CSharedPtr<CImage>    m_GoldImage;
    CSharedPtr<CText>     m_GoldText;
    CSharedPtr<CImage>    m_SatietyImage;
    CSharedPtr<CText>     m_SatietyText;
    CSharedPtr<CText>     m_SatietyTextMiddle;
    CSharedPtr<CText>     m_SatietyTextMax;
    CSharedPtr<CImage>    m_WarningOnHit0;
    CSharedPtr<CImage>    m_WarningOnHit1;
    CSharedPtr<CImage>    m_SkillBaseUI;
    CSharedPtr<CImage>    m_SkillImageUI;
    std::vector<CSharedPtr<CImage>> m_vecDashBack;
    std::vector<CSharedPtr<CImage>> m_vecDashCount;

    CSharedPtr<CImage>    m_ShieldBaseUI;
    CSharedPtr<CProgressBar>   m_ShieldProgressBar;


    class CBossUI* m_BossUI;
    class CWeaponUI* m_PlayerWeaponUI;
    float m_HitTime;
    bool m_bShield;
protected:
    CPlayerUI();
    virtual ~CPlayerUI();
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CPlayerUI* Clone();
public:
    void SetShieldUI(bool Enable);
    void Hit(bool bShield);
    void WeaponChange();
    void SetHPBar(float Percent);
};


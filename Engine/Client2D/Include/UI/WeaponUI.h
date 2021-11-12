#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include "UI/ProgressBar.h"
#include "../GlobalValue.h"

class CWeaponUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    class CInventory* m_InventoryUI;
    CSharedPtr<CImage>    m_WeaponUIBase1;
    CSharedPtr<CImage>    m_WeaponUIBase2;

    CSharedPtr<CImage>    m_WeaponImage1;
    CSharedPtr<CImage>    m_WeaponImage2;

    Select_Weapon m_SelectWeapon;
    Vector2 m_MoveWeapon1;
    Vector2 m_MoveWeapon2;

    Vector2 m_SelectPos;
    Vector2 m_WaltPos;


    bool m_FinishChange;
    float m_MoveRatio;
public:
    CWeaponUI();
    CWeaponUI(const CWeaponUI& widget);
    virtual ~CWeaponUI();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CWeaponUI* Clone();
public:
    void WeaponChange();
};


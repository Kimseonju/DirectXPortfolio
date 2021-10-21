#pragma once
#include "UI/WidgetWindow.h"
#include "../GlobalValue.h"
class CInventoryButton;
class CImage;
class CInventory :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CImage* m_InventoryBaseImage;
    CImage* m_AccBaseImage;
    CImage* m_WeaponSelect_Left;
    CImage* m_WeaponSelect_Right;

    Select_Weapon m_Current;
    std::vector<CInventoryButton*> m_Weapon;
    std::vector<CInventoryButton*> m_Accs;
    std::vector<CInventoryButton*> m_Items;
protected:
    CInventory();
    CInventory(const CInventory& widget);
    virtual ~CInventory();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CInventory* Clone();
public:
    class CItem* GetWeapon() const;
private:
    void StartButtonClick();
    void ExitButtonClick();
};


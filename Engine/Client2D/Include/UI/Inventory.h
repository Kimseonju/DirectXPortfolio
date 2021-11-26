#pragma once
#include "UI/WidgetWindow.h"
#include "../GlobalValue.h"
class CInventoryButton;
class CImage;
class CText;
class CInventory :
    public CWidgetWindow
{
    friend class CViewport;

protected:

    CSharedPtr<CImage>    m_InventoryBaseImage;
    CSharedPtr<CImage>    m_AccBaseImage;
    CSharedPtr<CImage>    m_WeaponSelect_Left;
    CSharedPtr<CImage>    m_WeaponSelect_Right;
    CSharedPtr<CText>    m_CoinText;
    CSharedPtr<CText>    m_Name1;
    CSharedPtr<CText>    m_WeaponMagazineMiddle2;
    Select_Weapon m_Current;
    std::vector<CInventoryButton*> m_Weapon;
    std::vector<CInventoryButton*> m_Accs;
    std::vector<CInventoryButton*> m_Items;
protected:
    CInventory();
    virtual ~CInventory();

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CInventory* Clone();
public:
    class CItem* GetWeapon() const;
    Select_Weapon GetCurrentNumber()
    {
        return m_Current;
    }
    CItem* GetInventoryWeapon(int Index)const;
    void WeaponChange();
    bool AddInventoryItem(CItem* Item);
private:
    void StartButtonClick();
    void ExitButtonClick();
};


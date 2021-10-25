#pragma once
#include <UI/MouseWidget.h>
#include "../GlobalValue.h"
#include "../Object/Item.h"
class CInventoryButton;
class CBasicMouse :
	public CMouseWidget
{
    friend class CEngine;

protected:
    CBasicMouse();
    virtual ~CBasicMouse();

protected:
    Mouse_State m_State;
    CItem* m_Item;
    bool    m_Down;
    bool    m_Push;
    bool    m_Up;
    bool    m_UpItem;
    CInventoryButton* m_ClickInventoryButton;
public:
    void SetState(Mouse_State State)
    {
        m_State = State;
    }
    Mouse_State GetState() const
    {
        return m_State;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMouseWidget* Clone();
public:
    void InventoryClick(CInventoryButton* Button);
    void InventoryMove(CInventoryButton* Button);
    
    void ClearItem();
};


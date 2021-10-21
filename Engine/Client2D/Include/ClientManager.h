#pragma once

#include "GameEngine.h"
#include "UI/BasicMouse.h"

class CClientManager
{
public:
    bool Init();

private:
    CSharedPtr<CBasicMouse>    m_Mouse;
    void CreateMouse();

    DECLARE_SINGLE(CClientManager)
};

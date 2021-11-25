#pragma once

#include "UI/WidgetWindow.h"

class CMiniMap :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CMiniMap();
    virtual ~CMiniMap();

    std::vector<std::vector<class CImage*>> m_vecImage;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMiniMap* Clone();
};


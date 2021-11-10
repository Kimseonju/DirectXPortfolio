#pragma once

#include "UI\WidgetWindow.h"
#include "UI/ProgressBar.h"
#include "UI/Image.h"

class CMapUI :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CMapUI();
    CMapUI(const CMapUI& widget);
    virtual ~CMapUI();

private:

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMapUI* Clone();
};


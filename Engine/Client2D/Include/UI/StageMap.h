#pragma once

#include "UI/WidgetWindow.h"

class CStageMap :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    std::vector<class CImage*> m_MapBase;
    std::vector<class CImage*> m_MapArrow;
    class CImage* m_MapBase1_0;
    class CImage* m_MapBase1_1;
    class CImage* m_BackCloud;
    class CStage* m_Stage;
    bool m_StageUpdate;
protected:
    CStageMap();
    virtual ~CStageMap();
public:
    void SetStage(class CStage* Stage)
    {
        m_Stage = Stage;
    }
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CStageMap* Clone();

    void CreateStage();
};


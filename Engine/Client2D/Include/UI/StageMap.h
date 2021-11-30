#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Text.h"

class CStageMap :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    std::vector<CSharedPtr<CImage>> m_MapBase;
    std::vector<CSharedPtr<CImage>> m_MapArrow;
    CSharedPtr<CImage>    m_MapBase1_0;
    CSharedPtr<CImage>    m_MapBase1_1;
    CSharedPtr<CImage>    m_BackCloud;
    CSharedPtr<CText>    m_WeaponMagazineMiddle2;

    CSharedPtr<CImage>    m_CurMapImage;
    class CStage* m_Stage;
    bool m_StageUpdate;
    float m_CurMapTimer;
    float m_CurMapTimerMax;
    bool m_CurMapEnable;
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

    void StageUpdate();
};


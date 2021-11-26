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
    CSharedPtr<CText>    m_PosX;
    CSharedPtr<CText>    m_PosY;
    CSharedPtr<CText>    m_Name1;
    CSharedPtr<CText>    m_WeaponMagazineMiddle2;

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

    void StageUpdate();
};


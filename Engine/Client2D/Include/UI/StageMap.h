#pragma once

#include "UI/WidgetWindow.h"
#include "UI/Image.h"
#include "UI/Text.h"
#include "GateButton.h"
struct MapInfoBase
{
    CSharedPtr<CImage> MapBase;
    CSharedPtr<CGateButton> GateButton;
    bool Move;
    MapInfoBase()
    {
        Move = false;
    }
};
class CStageMap :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    std::vector<std::vector<MapInfoBase>> m_MapInfoBase;

    std::vector<CSharedPtr<CImage>> m_MapBase;
    std::vector<CSharedPtr<CImage>> m_MapArrow;
    std::vector<CSharedPtr<CWidget>> m_MapIcon;
    CSharedPtr<CImage>    m_MapBase1_0;
    CSharedPtr<CImage>    m_MapBase1_1;
    CSharedPtr<CImage>    m_BackCloud;
    CSharedPtr<CText>    m_WeaponMagazineMiddle2;

    CSharedPtr<CImage>    m_CurMapImage;
    CSharedPtr<CImage>    m_GateMoveLine;

    std::vector<CSharedPtr<CGateButton>> m_vecGateButton;
    class CStage* m_Stage;
    bool m_StageUpdate;
    float m_CurMapTimer;
    float m_CurMapTimerMax;
    bool m_CurMapEnable;
    bool m_GateIn;
protected:
    CStageMap();
    virtual ~CStageMap();
public:
    void GateIn()
    {
        m_GateIn = true;
    }
    void SetStage(class CStage* Stage)
    {
        m_Stage = Stage;
    }
public:
    virtual void Enable(bool bEnable);
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CStageMap* Clone();
public:
    void StageMove();
    void MapUpdate();

    void MosueOnCallback();
    void ClickCallback();
    void MouseOutCallback();
};


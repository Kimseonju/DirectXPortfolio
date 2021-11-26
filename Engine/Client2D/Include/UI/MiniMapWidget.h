#pragma once

#include "UI/WidgetWindow.h"
#include <Resource/MiniMapCBuffer.h>

class CMiniMapWidget :
    public CWidget
{
    friend class CViewport;
    friend class CScene;
    friend class CWidgetWindow;

protected:
    CMiniMapWidget();
    virtual ~CMiniMapWidget();

    std::vector<MiniMapInfo>	m_vecMiniMapWidgetInfo;
    CSharedPtr<CSpriteMesh>     m_MiniMapMesh;
    std::vector<CSharedPtr<CMaterial>>   m_vecMaterialSlot;
    int m_TileCount;
    int m_ObjectCount;
    int m_EnemyCount;
    bool m_TileMapUpdate;
    class CStructuredBuffer* m_MapBuffer;
    CMiniMapCBuffer* m_CBuffer;
public:
    void TileUpdate()
    {
        m_TileMapUpdate = false;
    }
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMiniMapWidget* Clone();
public:
    void PushMiniMapInfoTile(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity);
    void PushMiniMapInfoObject(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity);
    void PushMiniMapInfoEnemy(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity);
    void ObjectClear();
    void Clear();
};


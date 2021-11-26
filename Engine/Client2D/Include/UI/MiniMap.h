#pragma once

#include "UI/WidgetWindow.h"
#include <Resource/MiniMapCBuffer.h>

class CMiniMap :
    public CWidgetWindow
{
    friend class CViewport;

protected:
    CMiniMap();
    virtual ~CMiniMap();
    class CMiniMapWidget* m_MiniMapWidget;
public:
    void TileUpdate();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render();
    virtual CMiniMap* Clone();
public:
    void PushMiniMapInfoTile(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity);
    void PushMiniMapInfoObject(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity);
    void PushMiniMapInfoEnemy(Vector2 Pos, Vector4 Color, Vector4 EmvColor, float Opacity);
    void ObjectClear();
    void Clear();
};


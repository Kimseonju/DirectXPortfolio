#pragma once
#include "Scene\SceneMode.h"
#include "../Editor.h"
class CEditorScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CEditorScene();
    virtual ~CEditorScene();

private:
    class CTileMapToolWindow* m_TileMapToolWindow;
    class CPrefabWindow* m_PrefabWindow;
    class CObjectWindow* m_ObjectWindow;
    int m_CloneObjectCount;
public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);

private:
    void MoveUp(float DeltaTime);
    void MoveDown(float DeltaTime);
    void MoveLeft(float DeltaTime);
    void MoveRight(float DeltaTime);
    void MouseLButton(float DeltaTime);

private:
    void EditTileType();
    void EditTileImage();
    void EditMap();
    void CreateAnimationSequence2D();
};


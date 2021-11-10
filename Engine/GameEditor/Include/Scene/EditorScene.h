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
    void MouseRButton(float DeltaTime);
    void Button1(float DeltaTime);
    void Button2(float DeltaTime);
    void Button3(float DeltaTime);
    void Button4(float DeltaTime);
private:
    void EditTileType();
    void EditTileImage();
    void EditTileObjectImage();
    void AddObjectMap();
    void DeleteObjectMap();
    void CreateAnimationSequence2D();
    void CreateParticle();
    void CreateCollisionProfile();
};


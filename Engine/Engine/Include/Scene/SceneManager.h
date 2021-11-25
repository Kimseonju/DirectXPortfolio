#pragma once
#include "../GameEngine.h"
#include "Scene.h"
class CScene;
class CSceneManager
{

private:
    CScene* m_pScene;
    CScene* m_pNextScene;
public:
    CScene* GetScene()  const
    {
        return m_pScene;
    }
    CScene* GetNextScene()  const
    {
        return m_pNextScene;
    }
    bool m_SceneChange;
public:
    bool Init();
    bool Update(float DeltaTime);
    bool PostUpdate(float DeltaTime);
    bool Collision(float DeltaTime);
    bool Render(float DeltaTime);
    void Clear();
    void CreateNextScene();
    class CScene* CreateScene();
    void SetNextScene(class CScene* Scene);

private:
    bool ChangeScene();
public:
    template <typename T>
    bool SetSceneMode(bool Current = true)
    {
        if (Current)
            return m_pScene->SetSceneMode<T>();

        return m_pNextScene->SetSceneMode<T>();
    }

    void SetChange(bool bChange)
    {
        if (m_pNextScene)
        {
            m_SceneChange = bChange;
        }
    }
    DECLARE_SINGLE(CSceneManager)
};


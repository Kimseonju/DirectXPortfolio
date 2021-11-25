#pragma once

#include "Scene/SceneMode.h"

class CStartScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CStartScene();
    virtual ~CStartScene();
private:

    CScene* m_NextScene;
public:
    virtual bool Init();
    virtual void Start();
private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();
public:

    CScene* GetNextScene()
    {
        return m_NextScene;
    }
};


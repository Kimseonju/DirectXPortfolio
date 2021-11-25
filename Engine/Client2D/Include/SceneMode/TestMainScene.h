#pragma once

#include "Scene/SceneMode.h"

class CTestMainScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CTestMainScene();
    virtual ~CTestMainScene();
private:

    int m_Minrooms;
    int m_Maxrooms;
    int m_Endrooms;
public:
    virtual bool Init();
    virtual void Start();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
public:

private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();
    void LoadStage();
    void RandomRoom()
    {

    }
};


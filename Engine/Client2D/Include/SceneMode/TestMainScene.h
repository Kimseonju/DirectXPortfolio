#pragma once

#include "Scene/SceneMode.h"

class CTestMainScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CTestMainScene();
    virtual ~CTestMainScene();
public:
    virtual bool Init();
    class CStage* m_Stage;
    int m_Minrooms;
    int m_Maxrooms;
    int m_Endrooms;
private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();

    void RandomRoom()
    {

    }
};


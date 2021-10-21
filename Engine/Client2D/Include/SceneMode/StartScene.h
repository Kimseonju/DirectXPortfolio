#pragma once

#include "Scene/SceneMode.h"

class CStartScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CStartScene();
    virtual ~CStartScene();

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();
};


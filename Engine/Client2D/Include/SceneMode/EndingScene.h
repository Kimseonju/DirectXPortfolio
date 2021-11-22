#pragma once

#include "Scene/SceneMode.h"

class CEndingScene :
    public CSceneMode
{
    friend class CScene;

protected:
    CEndingScene();
    virtual ~CEndingScene();

public:
    virtual bool Init();

private:
    void CreateMaterial();
    void CreateAnimationSequence2D();
    void CreateParticle();
};


#pragma once
#include "GraphicShader.h"
class CMiniMapShader :
    public CGraphicShader
{
    friend class CShaderManager;

protected:
    CMiniMapShader();
    virtual ~CMiniMapShader();

public:
    virtual bool Init();
};


#pragma once

#include "PrimitiveComponent.h"
#include "../Resource/SpriteMesh.h"
#include "../Resource/Animation2D.h"

class CSpriteComponent :
    public CPrimitiveComponent
{
    friend class CGameObject;

protected:
    CSpriteComponent();
    CSpriteComponent(const CSpriteComponent& com);
    virtual ~CSpriteComponent();

protected:
    CSharedPtr<CSpriteMesh>     m_pMesh;
    CSharedPtr<CAnimation2D>    m_Animation;
public:
    CAnimation2D* GetAnimation2D()  const;
    virtual class CMesh* GetMesh()  const;
    virtual void SetMesh(class CMesh* pMesh);
    virtual void SetMesh(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CSpriteComponent* Clone();
public:

    virtual void Save(FILE* pFile);
    virtual void Load(FILE* pFile);
public:
    void CallNotify(const std::string& Name);
public:
    template <typename T>
    void CreateAnimation2D()
    {
        //= 연산자로 레퍼런스카운트가 2가되서 Release해줌
        m_Animation = new T;
        m_Animation->Release();

        m_Animation->SetScene(m_pScene);
        m_Animation->SetOwner(this);

        m_Animation->Init();
        SetAnimation2DEnable(true);
    }
    void DeleteAnimation2D()
    {
        SAFE_DELETE(m_Animation);
        SetAnimation2DEnable(false);
    }
};


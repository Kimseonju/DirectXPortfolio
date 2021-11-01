#pragma once

#include "../Ref.h"

class CComponent :
    public CRef
{
    friend class CGameObject;

protected:
    CComponent();
    CComponent(const CComponent& com);
    virtual ~CComponent() = 0;

protected:
    class CScene* m_pScene;
    class CGameObject* m_pOwner;
public:
    void SetOwner(class CGameObject* Owner)
    {
        m_pOwner = Owner;
    }

    class CGameObject* GetOwner()   const
    {
        return m_pOwner;
    }

    class CScene* GetScene() const
    {
        return m_pScene;
    }
    virtual void Active(bool bActive);
    virtual bool IsActive() const;
public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void PrevRender(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CComponent* Clone() = 0;
};


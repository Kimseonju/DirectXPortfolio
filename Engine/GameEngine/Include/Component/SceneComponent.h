#pragma once

//어떻게 출력될것인지 씬에 가르쳐주는 컴포넌트
//Transform을 가지고있다.
#include "Component.h"

class CSceneComponent :
    public CComponent
{
    friend class CGameObject;

protected:
    CSceneComponent();
    CSceneComponent(const CSceneComponent& com);
    virtual ~CSceneComponent();

protected:
    class CTransform* m_pTransform;
    CSceneComponent* m_pParent;
    std::vector<CSharedPtr<CSceneComponent>>    m_vecChild;
    SceneComponent_Type m_SceneComponentType;
    Component_Class_Type m_ComponentClassType;
public:
    SceneComponent_Type GetSceneComponentType() const
    {
        return m_SceneComponentType;
    }

    Component_Class_Type GetComponentClassType() const
    {
        return m_ComponentClassType;
    }
    void GetSceneComponent(std::vector<CSceneComponent*>& vec)
    {
        auto iter = m_vecChild.begin();
        auto iterEnd = m_vecChild.end();

        for (; iter != iterEnd; ++iter)
        {
            (*iter)->GetSceneComponent(vec);
            vec.push_back(*iter);
        }
    }
public:
    virtual void Active(bool bActive);
    //SocketName은 3D할때 3D Animation에서 본(뼈대)이라는게있는데 그걸 쓸때 SocketName
    //2D는 안씀
    void AddChild(CSceneComponent* Child, const std::string& SocketName = "");
    void DeleteChild(CSceneComponent* Child);
    void GetAllComponentName(std::vector<HierarchyName>& vecName);
    void GetAllComponent(std::vector<CSceneComponent*>& vecComponent);
    void DetatchChild(CSceneComponent* Child);
    CSceneComponent* FindComponent(const std::string& Name);

public:
    virtual void Start();
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Collision(float DeltaTime);
    virtual void PrevRender(float DeltaTime);
    virtual void Render(float DeltaTime);
    virtual CSceneComponent* Clone();
public:
    virtual void Save(FILE* pFile);
    virtual void Load(FILE* pFile);
public:
    void SetAnimation2DEnable(bool Enable);
    void SetHorizontalReverse2DEnable(bool Enable);
    void SetVerticalReverse2DEnable(bool Enable);
    //부모오브젝트 설정할때 사용되는 함수 RootComponent전용
    bool AttachParent(CSceneComponent* Component);
    //부모오브젝트 설정할때 사용되는 함수 RootComponent전용
    bool DetachParent();
public:
    Vector3 GetVelocityScale()  const;
    Vector3 GetVelocityRot()    const;
    Vector3 GetVelocity()   const;
    Vector3 GetAxis(AXIS Axis)  const;
public:
    void SetInheritScale(bool Inherit);
    void SetInheritRotX(bool Inherit);
    void SetInheritRotY(bool Inherit);
    void SetInheritRotZ(bool Inherit);
    void SetInheritPosZ(bool Inherit);
    void SetUpdatePosZ(bool UpdatePosZ);
    void InheritScale();
    void InheritRot();
    void InheritPos();

public:
    bool GetInheritPosZ()	const;

public:
    Vector3 GetRelativeScale()  const;
    Vector3 GetRelativeRotation()    const;
    Vector3 GetRelativePos()    const;

public:
    void SetRelativeScale(const Vector3& Scale);
    void SetRelativeScale(float x, float y, float z);
    void SetRelativeRotation(const Vector3& Rot);
    void SetRelativeRotation(float x, float y, float z);
    void SetRelativeRotationX(float x);
    void SetRelativeRotationY(float y);
    void SetRelativeRotationZ(float z);
    void SetRelativePos(const Vector3& Pos);
    void SetRelativePos(float x, float y, float z);
    void AddRelativeScale(const Vector3& Scale);
    void AddRelativeScale(float x, float y, float z);
    void AddRelativeRotation(const Vector3& Rot);
    void AddRelativeRotation(float x, float y, float z);
    void AddRelativeRotationX(float x);
    void AddRelativeRotationY(float y);
    void AddRelativeRotationZ(float z);
    void AddRelativePos(const Vector3& Pos);
    void AddRelativePos(float x, float y, float z);

public:
    Vector3 GetWorldScale() const;
    Vector3 GetWorldRotation()  const;
    Vector3 GetWorldPos()   const;
    Vector3 GetPivot()  const;
    Vector3 GetMeshSize()   const;
    Matrix GetScaleMatrix() const;
    Matrix GetRotatinMatrix()   const;
    Matrix GetTranslationMatrix()   const;
    Matrix GetWorldMatrix() const;

public:
    void SetPivot(const Vector3& Pivot);
    void SetPivot(float x, float y, float z);
    void SetMeshSize(const Vector3& Size);
    void SetMeshSize(float x, float y, float z);

public:
    void SetWorldScale(const Vector3& Scale);
    void SetWorldScale(float x, float y, float z);
    void SetWorldRotation(const Vector3& Rot);
    void SetWorldRotation(float x, float y, float z);
    void SetWorldRotationX(float x);
    void SetWorldRotationY(float y);
    void SetWorldRotationZ(float z);
    void SetWorldPos(const Vector3& Pos);
    void SetWorldPos(float x, float y, float z);
    void AddWorldScale(const Vector3& Scale);
    void AddWorldScale(float x, float y, float z);
    void AddWorldRotation(const Vector3& Rot);
    void AddWorldRotation(float x, float y, float z);
    void AddWorldRotationX(float x);
    void AddWorldRotationY(float y);
    void AddWorldRotationZ(float z);
    void AddWorldPos(const Vector3& Pos);
    void AddWorldPos(float x, float y, float z);
public:
    void ClearTransformState();
};


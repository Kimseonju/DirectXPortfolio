
#include "SceneComponent.h"
#include "Transform.h"
#include "../NavigationManager.h"
#include "../Render/RenderManager.h"
#include "../GameObject.h"
CSceneComponent::CSceneComponent()
{
    m_pTransform = new CTransform;

    m_pTransform->m_pOwner = this;
    m_pTransform->Init();
    m_pParent = nullptr;

    m_SceneComponentType = SceneComponent_Type::Scene;
    m_ComponentClassType = Component_Class_Type::Scene;

    m_MoveSpeed = 300.f;
}

CSceneComponent::CSceneComponent(const CSceneComponent& com)    :
    CComponent(com)
{
    *this = com;
    //�����Ѻκ�
    m_RefCount = 1;
    m_pTransform = com.m_pTransform->Clone();

    m_pTransform->m_pParent = nullptr;
    m_pTransform->m_vecChild.clear();

    m_pTransform->m_pOwner = this;

    m_pParent = nullptr;

    m_vecChild.clear();
    m_pScene = com.m_pScene;

    size_t  Size = com.m_vecChild.size();
    
    for (size_t i = 0; i < Size; ++i)
    {
        CSceneComponent* CloneCom = com.m_vecChild[i]->Clone();
    
        CloneCom->m_pParent = this;
    
        m_vecChild.push_back(CloneCom);
    
        CloneCom->m_pTransform->m_pParent = m_pTransform;
    
        m_pTransform->m_vecChild.push_back(CloneCom->m_pTransform);
    }

}

CSceneComponent::~CSceneComponent()
{
    SAFE_DELETE(m_pTransform);
}

void CSceneComponent::Move(const Vector2& Target)
{
    Move(Vector3(Target.x, Target.y, 0.f));
}

void CSceneComponent::Move(const Vector3& Target)
{
    m_vecNavPath.clear();

    CNavigationManager::GetInst()->FindPath(GetWorldPos(), Target, this);
}

void CSceneComponent::NavigationCallback(const std::vector<Vector3>& vecPath)
{
    m_vecNavPath.clear();
    m_vecNavPath = vecPath;
}

void CSceneComponent::Active(bool bActive)
{
    CComponent::Active(bActive);

    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_vecChild[i]->Active(bActive);
    }
}

void CSceneComponent::AddChild(CSceneComponent* Child, const std::string& SocketName)
{
    Child->m_pParent = this;
    m_vecChild.push_back(Child);

    Child->m_pTransform->m_pParent = m_pTransform;

    m_pTransform->m_vecChild.push_back(Child->m_pTransform);

    Child->m_pTransform->InheritScale();
    Child->m_pTransform->InheritRot();
    Child->m_pTransform->InheritPos();
}

void CSceneComponent::DeleteChild(CSceneComponent* Child)
{
    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        if (m_vecChild[i] == Child)
        {
            auto    iter = m_vecChild.begin() + i;

            m_vecChild.erase(iter);

            auto    iterTr = m_pTransform->m_vecChild.begin() + i;

            m_pTransform->m_vecChild.erase(iterTr);

            break;
        }
    }
}

void CSceneComponent::GetAllComponentName(std::vector<HierarchyName>& vecName)
{
    HierarchyName   NameInfo;
    NameInfo.Name = m_Name;
    
    if (m_pParent)
        NameInfo.ParentName = m_pParent->m_Name;

    vecName.push_back(NameInfo);

    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_vecChild[i]->GetAllComponentName(vecName);
    }
}

void CSceneComponent::GetAllComponent(std::vector<CSceneComponent*>& vecComponent)
{
    vecComponent.push_back(this);

    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_vecChild[i]->GetAllComponent(vecComponent);
    }
}
void CSceneComponent::GetAllCloneComponent(CGameObject* Owner,std::vector<CSceneComponent*>& vecComponent)
{
    if (Owner->GetRootComponent())
    {
        vecComponent.push_back(this);
    }
    else
    {
        CSceneComponent* Component = this->Clone();
        Owner->GetRootComponent()->AddChild(Component);
        Component->SetOwner(Owner);
        vecComponent.push_back(Component);
    }
    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_vecChild[i]->GetAllCloneComponent(Owner ,vecComponent);
    }
}
void CSceneComponent::DetatchChild(CSceneComponent* Child)
{
    Child->m_pParent = nullptr;

    Child->m_pTransform->m_pParent = nullptr;

    Child->m_pTransform->SetRelativePos(Child->m_pTransform->GetWorldPos());
    Child->m_pTransform->SetRelativeRotation(Child->m_pTransform->GetWorldRotation());
    Child->m_pTransform->SetRelativeScale(Child->m_pTransform->GetWorldScale());
}

CSceneComponent* CSceneComponent::FindComponent(const std::string& Name)
{
    if (m_Name == Name)
        return this;

    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        CSceneComponent* pFind = m_vecChild[i]->FindComponent(Name);

        if (pFind)
            return pFind;
    }

    return nullptr;
}

void CSceneComponent::Start()
{
    m_pTransform->m_pScene = m_pScene;
    m_pTransform->Start();

    size_t  Size = m_vecChild.size();

    for (size_t i = 0; i < Size; ++i)
    {
        m_vecChild[i]->Start();
    }
}

bool CSceneComponent::Init()
{
    m_pTransform->m_pScene = m_pScene;

    return true;
}

void CSceneComponent::Update(float DeltaTime)
{
    CComponent::Update(DeltaTime);

    {
        if (!m_vecNavPath.empty())
        {
            Vector3 NextPos = m_vecNavPath.back();
            Vector3 Pos = GetWorldPos();

            if (CRenderManager::GetInst()->GetRenderSpace() == Render_Space::Render2D)
            {
                NextPos.z = 0.f;
                Pos.z = 0.f;
            }

            Vector3 Dir = NextPos - Pos;
            Dir.Normalize();

            AddRelativePos(Dir * DeltaTime * m_MoveSpeed);

            Pos = GetWorldPos();

            float   Dist = Pos.Distance(NextPos);

            if (Dist <= 5.f)
            {
                SetWorldPos(NextPos);
                m_vecNavPath.pop_back();
            }
        }
    }


    m_pTransform->Update(DeltaTime);

    auto    iter = m_vecChild.begin();
    auto    iterEnd = m_vecChild.end();
    auto    iterTr = m_pTransform->m_vecChild.begin();

    for (; iter != iterEnd; )
    {
        if (!(*iter)->IsActive())
        {
            DetatchChild(*iter);
            iter = m_vecChild.erase(iter);
            iterEnd = m_vecChild.end();

            iterTr = m_pTransform->m_vecChild.erase(iterTr);

            continue;
        }

        if ((*iter)->IsEnable())
            (*iter)->Update(DeltaTime);

        ++iter;
        ++iterTr;
    }
}

void CSceneComponent::PostUpdate(float DeltaTime)
{
    CComponent::PostUpdate(DeltaTime);
    m_pTransform->PostUpdate(DeltaTime);

    auto    iter = m_vecChild.begin();
    auto    iterEnd = m_vecChild.end();
    auto    iterTr = m_pTransform->m_vecChild.begin();

    for (; iter != iterEnd; )
    {
        if (!(*iter)->IsActive())
        {
            DetatchChild(*iter);
            iter = m_vecChild.erase(iter);
            iterEnd = m_vecChild.end();

            iterTr = m_pTransform->m_vecChild.erase(iterTr);

            continue;
        }

        if ((*iter)->IsEnable())
            (*iter)->PostUpdate(DeltaTime);

        ++iter;
        ++iterTr;
    }
}

void CSceneComponent::Collision(float DeltaTime)
{
    CComponent::Collision(DeltaTime);
}

void CSceneComponent::PrevRender(float DeltaTime)
{
    CComponent::PrevRender(DeltaTime);
    m_pTransform->PrevRender(DeltaTime);

    auto    iter = m_vecChild.begin();
    auto    iterEnd = m_vecChild.end();
    auto    iterTr = m_pTransform->m_vecChild.begin();

    for (; iter != iterEnd; )
    {
        if (!(*iter)->IsActive())
        {
            DetatchChild(*iter);
            iter = m_vecChild.erase(iter);
            iterEnd = m_vecChild.end();

            iterTr = m_pTransform->m_vecChild.erase(iterTr);

            continue;
        }

        if ((*iter)->IsEnable())
            (*iter)->PrevRender(DeltaTime);

        ++iter;
        ++iterTr;
    }
}

void CSceneComponent::Render(float DeltaTime)
{
    // ��� ������ �ڽ��� Transform ������ Shader�� �����ش�.
    m_pTransform->SetTransform();
}

CSceneComponent* CSceneComponent::Clone()
{
    return new CSceneComponent(*this);
}

void CSceneComponent::Save(FILE* pFile)
{
    fwrite(&m_SceneComponentType, sizeof(SceneComponent_Type), 1, pFile);
    Vector3	Pos, Rot, Scale, Pivot;
    Pos = GetRelativePos();
    Rot = GetRelativeRotation();
    Scale = GetRelativeScale();
    Pivot=GetPivot();
    fwrite(&Pos, sizeof(Vector3), 1, pFile);
    fwrite(&Rot, sizeof(Vector3), 1, pFile);
    fwrite(&Scale, sizeof(Vector3), 1, pFile);
    fwrite(&Pivot, sizeof(Vector3), 1, pFile);
}

void CSceneComponent::Load(FILE* pFile)
{
    SceneComponent_Type Type;

    fread(&Type, sizeof(SceneComponent_Type), 1, pFile);
    m_SceneComponentType = Type;
    Vector3	Pos, Rot, Scale, Pivot;

    fread(&Pos, sizeof(Vector3), 1, pFile);
    fread(&Rot, sizeof(Vector3), 1, pFile);
    fread(&Scale, sizeof(Vector3), 1, pFile);
    fread(&Pivot, sizeof(Vector3), 1, pFile);
    SetRelativePos(Pos);
    SetRelativeRotation(Rot);
    SetRelativeScale(Scale);
    SetPivot(Pivot);


}

bool CSceneComponent::GetHorizontalReverse2DEnable()
{
    return m_pTransform->GetHorizontalReverse2DEnable();
}

void CSceneComponent::SetAnimation2DEnable(bool Enable)
{
    m_pTransform->SetAnimation2DEnable(Enable);
}

void CSceneComponent::SetHorizontalReverse2DEnable(bool Enable)
{
    m_pTransform->SetHorizontalReverse2DEnable(Enable);
}

void CSceneComponent::SetVerticalReverse2DEnable(bool Enable)
{
    m_pTransform->SetVerticalReverse2DEnable(Enable);
}

bool CSceneComponent::AttachParent(CSceneComponent* Component)
{
    //RootComponent�� �ƴ�
    if (m_pParent)
        return false;
    m_pParent = Component;
    m_pTransform->m_pParent = Component->m_pTransform;

    m_pTransform->InheritScale();
    m_pTransform->InheritRot();
    m_pTransform->InheritPos();
    return true;
}
bool CSceneComponent::DetachParent()
{
    //RootComponent�� �ƴ�
    if (m_pOwner->GetRootComponent() != this)
    {
        return false;
    }

    if (m_pParent)
        return false;
    m_pParent = nullptr;
    m_pTransform->m_pParent = nullptr;

    m_pTransform->InheritScale();
    m_pTransform->InheritRot();
    m_pTransform->InheritPos();
    return true;
}
Vector3 CSceneComponent::GetVelocityScale() const
{
    return m_pTransform->GetVelocityScale();
}

Vector3 CSceneComponent::GetVelocityRot() const
{
    return m_pTransform->GetVelocityRot();
}

Vector3 CSceneComponent::GetVelocity() const
{
    return m_pTransform->GetVelocity();
}

Vector3 CSceneComponent::GetAxis(AXIS Axis) const
{
    return m_pTransform->GetAxis(Axis);
}


void CSceneComponent::SetInheritScale(bool Inherit)
{
    m_pTransform->SetInheritScale(Inherit);
}

void CSceneComponent::SetInheritRotX(bool Inherit)
{
    m_pTransform->SetInheritRotX(Inherit);
}

void CSceneComponent::SetInheritRotY(bool Inherit)
{
    m_pTransform->SetInheritRotY(Inherit);
}

void CSceneComponent::SetInheritRotZ(bool Inherit)
{
    m_pTransform->SetInheritRotZ(Inherit);
}

void CSceneComponent::SetInheritPosZ(bool Inherit)
{
    m_pTransform->SetInheritPosZ(Inherit);
}

void CSceneComponent::SetUpdatePosZ(bool UpdatePosZ)
{
    m_pTransform->SetUpdatePosZ(UpdatePosZ);
}

void CSceneComponent::InheritScale()
{
    m_pTransform->InheritScale();
}

void CSceneComponent::InheritRot()
{
    m_pTransform->InheritRot();
}

void CSceneComponent::InheritPos()
{
    m_pTransform->InheritPos();
}

bool CSceneComponent::GetInheritPosZ() const
{
    return m_pTransform->GetInheritPosZ();
}

Vector3 CSceneComponent::GetRelativeScale() const
{
    return m_pTransform->GetRelativeScale();
}

Vector3 CSceneComponent::GetRelativeRotation() const
{
    return m_pTransform->GetRelativeRotation();
}

Vector3 CSceneComponent::GetRelativePos() const
{
    return m_pTransform->GetRelativePos();
}

void CSceneComponent::SetRelativeScale(const Vector3& Scale)
{
    m_pTransform->SetRelativeScale(Scale);
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
    m_pTransform->SetRelativeScale(x, y, z);
}

void CSceneComponent::SetRelativeRotation(const Vector3& Rot)
{
    m_pTransform->SetRelativeRotation(Rot);
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
    m_pTransform->SetRelativeRotation(x, y, z);
}

void CSceneComponent::SetRelativeRotationX(float x)
{
    m_pTransform->SetRelativeRotationX(x);
}

void CSceneComponent::SetRelativeRotationY(float y)
{
    m_pTransform->SetRelativeRotationY(y);
}

void CSceneComponent::SetRelativeRotationZ(float z)
{
    m_pTransform->SetRelativeRotationZ(z);
}

void CSceneComponent::SetRelativePos(const Vector3& Pos)
{
    m_pTransform->SetRelativePos(Pos);
}

void CSceneComponent::SetRelativePos(float x, float y, float z)
{
    m_pTransform->SetRelativePos(x, y, z);
}

void CSceneComponent::AddRelativeScale(const Vector3& Scale)
{
    m_pTransform->AddRelativeScale(Scale);
}

void CSceneComponent::AddRelativeScale(float x, float y, float z)
{
    m_pTransform->AddRelativeScale(x, y, z);
}

void CSceneComponent::AddRelativeRotation(const Vector3& Rot)
{
    m_pTransform->AddRelativeRotation(Rot);
}

void CSceneComponent::AddRelativeRotation(float x, float y, float z)
{
    m_pTransform->AddRelativeRotation(x, y, z);
}

void CSceneComponent::AddRelativeRotationX(float x)
{
    m_pTransform->AddRelativeRotationX(x);
}

void CSceneComponent::AddRelativeRotationY(float y)
{
    m_pTransform->AddRelativeRotationY(y);
}

void CSceneComponent::AddRelativeRotationZ(float z)
{
    m_pTransform->AddRelativeRotationZ(z);
}

void CSceneComponent::AddRelativePos(const Vector3& Pos)
{
    m_pTransform->AddRelativePos(Pos);
}

void CSceneComponent::AddRelativePos(float x, float y, float z)
{
    m_pTransform->AddRelativePos(x, y, z);
}

Vector3 CSceneComponent::GetWorldScale() const
{
    return m_pTransform->GetWorldScale();
}

Vector3 CSceneComponent::GetWorldRotation() const
{
    return m_pTransform->GetWorldRotation();
}

Vector3 CSceneComponent::GetWorldPos() const
{
    return m_pTransform->GetWorldPos();
}

Vector3 CSceneComponent::GetPivot() const
{
    return m_pTransform->GetPivot();
}

Vector3 CSceneComponent::GetMeshSize() const
{
    return m_pTransform->GetMeshSize();
}

Matrix CSceneComponent::GetScaleMatrix() const
{
    return m_pTransform->GetScaleMatrix();
}

Matrix CSceneComponent::GetRotatinMatrix() const
{
    return m_pTransform->GetRotatinMatrix();
}

Matrix CSceneComponent::GetTranslationMatrix() const
{
    return m_pTransform->GetTranslationMatrix();
}

Matrix CSceneComponent::GetWorldMatrix() const
{
    return m_pTransform->GetWorldMatrix();
}

void CSceneComponent::SetPivot(const Vector3& Pivot)
{
    m_pTransform->SetPivot(Pivot);
}

void CSceneComponent::SetPivot(float x, float y, float z)
{
    m_pTransform->SetPivot(x, y, z);
}

void CSceneComponent::SetMeshSize(const Vector3& Size)
{
    m_pTransform->SetMeshSize(Size);
}

void CSceneComponent::SetMeshSize(float x, float y, float z)
{
    m_pTransform->SetMeshSize(x, y, z);
}

void CSceneComponent::SetWorldScale(const Vector3& Scale)
{
    m_pTransform->SetWorldScale(Scale);
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
    m_pTransform->SetWorldScale(x, y, z);
}

void CSceneComponent::SetWorldRotation(const Vector3& Rot)
{
    m_pTransform->SetWorldRotation(Rot);
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
    m_pTransform->SetWorldRotation(x, y, z);
}

void CSceneComponent::SetWorldRotationX(float x)
{
    m_pTransform->SetWorldRotationX(x);
}

void CSceneComponent::SetWorldRotationY(float y)
{
    m_pTransform->SetWorldRotationY(y);
}

void CSceneComponent::SetWorldRotationZ(float z)
{
    m_pTransform->SetWorldRotationZ(z);
}

void CSceneComponent::SetWorldPos(const Vector3& Pos)
{
    m_pTransform->SetWorldPos(Pos);
}

void CSceneComponent::SetWorldPos(float x, float y, float z)
{
    m_pTransform->SetWorldPos(x, y, z);
}

void CSceneComponent::AddWorldScale(const Vector3& Scale)
{
    m_pTransform->AddWorldScale(Scale);
}

void CSceneComponent::AddWorldScale(float x, float y, float z)
{
    m_pTransform->AddWorldScale(x, y, z);
}

void CSceneComponent::AddWorldRotation(const Vector3& Rot)
{
    m_pTransform->AddWorldRotation(Rot);
}

void CSceneComponent::AddWorldRotation(float x, float y, float z)
{
    m_pTransform->AddWorldRotation(x, y, z);
}

void CSceneComponent::AddWorldRotationX(float x)
{
    m_pTransform->AddWorldRotationX(x);
}

void CSceneComponent::AddWorldRotationY(float y)
{
    m_pTransform->AddWorldRotationY(y);
}

void CSceneComponent::AddWorldRotationZ(float z)
{
    m_pTransform->AddWorldRotationZ(z);
}

void CSceneComponent::AddWorldPos(const Vector3& Pos)
{
    m_pTransform->AddWorldPos(Pos);
}

void CSceneComponent::AddWorldPos(float x, float y, float z)
{
    m_pTransform->AddWorldPos(x, y, z);
}

void CSceneComponent::ClearTransformState()
{
    m_pTransform->ClearState();
}

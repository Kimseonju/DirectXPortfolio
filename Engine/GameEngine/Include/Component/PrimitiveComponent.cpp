
#include "PrimitiveComponent.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "Transform.h"

CPrimitiveComponent::CPrimitiveComponent()
{
    m_SceneComponentType = SceneComponent_Type::Primitive;
    m_PrimitiveType = PrimitiveComponent_Type::Primitive3D;
    m_ComponentClassType = Component_Class_Type::Primitive;

    SetRender2DType(RT2D_None);
    m_3DType = RT3D_None;

    m_pTransform->SetDefaultZ(0.3f);

    m_DistortionEnable = false;
}

CPrimitiveComponent::CPrimitiveComponent(const CPrimitiveComponent& com)    :
    CSceneComponent(com)
{
    m_PrimitiveType = com.m_PrimitiveType;
    m_2DType = com.m_2DType;
    SetRender2DType(m_2DType);
    m_3DType = com.m_3DType;
    m_vecMaterialSlot = com.m_vecMaterialSlot;
    m_DistortionEnable = com.m_DistortionEnable;
}

CPrimitiveComponent::~CPrimitiveComponent()
{
}

void CPrimitiveComponent::SetRender2DType(Render_Type_2D Type)
{
    m_2DType = Type;
    switch (m_2DType)
    {
    case RT2D_None:
        m_pTransform->SetDefaultZ(0.1f);
        break;
    case RT2D_MAP:
        m_pTransform->SetDefaultZ(0.2f);
        break;
    case RT2D_Back1:
        m_pTransform->SetDefaultZ(0.3f);
        break;
    case RT2D_Back2:
        m_pTransform->SetDefaultZ(0.4f);
        break;
    case RT2D_Default:
        m_pTransform->SetDefaultZ(0.5f);
        break;
    case RT2D_Default2:
        m_pTransform->SetDefaultZ(0.6f);
        break;
    case RT2D_Particle:
        m_pTransform->SetDefaultZ(0.9f);
        break;
    default:
        break;
    }
}

void CPrimitiveComponent::SetMaterial(int SlotIndex, CMaterial* pMaterial)
{
    m_vecMaterialSlot[SlotIndex] = pMaterial;
}

void CPrimitiveComponent::SetMaterial(int SlotIndex, const std::string& Name)
{
    m_vecMaterialSlot[SlotIndex] = m_pScene->GetResource()->FindMaterial(Name)->Clone();
}

void CPrimitiveComponent::AddMaterial(CMaterial* pMaterial)
{
    m_vecMaterialSlot.push_back(pMaterial);
}

void CPrimitiveComponent::AddMaterial(const std::string& Name)
{
    CMaterial* pMaterial = m_pScene->GetResource()->FindMaterial(Name);
    m_vecMaterialSlot.push_back(pMaterial);
}

CMesh* CPrimitiveComponent::GetMesh() const
{
    return nullptr;
}

void CPrimitiveComponent::SetMesh(CMesh* pMesh)
{
}

void CPrimitiveComponent::SetMesh(const std::string& Name)
{
}

void CPrimitiveComponent::Start()
{
    CSceneComponent::Start();
}

bool CPrimitiveComponent::Init()
{
    if (!CSceneComponent::Init())
        return false;

    return true;
}

void CPrimitiveComponent::Update(float DeltaTime)
{
    CSceneComponent::Update(DeltaTime);
}

void CPrimitiveComponent::PostUpdate(float DeltaTime)
{
    CSceneComponent::PostUpdate(DeltaTime);
}

void CPrimitiveComponent::Collision(float DeltaTime)
{
    CSceneComponent::Collision(DeltaTime);
}

void CPrimitiveComponent::PrevRender(float DeltaTime)
{
    CSceneComponent::PrevRender(DeltaTime);

    CRenderManager::GetInst()->AddPrimitiveComponent(this);
}

void CPrimitiveComponent::Render(float DeltaTime)
{
    CSceneComponent::Render(DeltaTime);
}

CPrimitiveComponent* CPrimitiveComponent::Clone()
{
    return new CPrimitiveComponent(*this);
}

void CPrimitiveComponent::Save(FILE* pFile)
{
    CSceneComponent::Save(pFile);

    fwrite(&m_PrimitiveType, sizeof(PrimitiveComponent_Type), 1, pFile);

    fwrite(&m_2DType, sizeof(Render_Type_2D), 1, pFile);
    fwrite(&m_3DType, sizeof(Render_Type_3D), 1, pFile);
    size_t Size=m_vecMaterialSlot.size();
    fwrite(&Size, sizeof(size_t), 1, pFile);
    for (size_t i = 0; i < Size; i++)
    {
        m_vecMaterialSlot[i]->Save(pFile);
    }
    fwrite(&m_DistortionEnable, sizeof(bool), 1, pFile);
}

void CPrimitiveComponent::Load(FILE* pFile)
{
    CSceneComponent::Load(pFile);
    PrimitiveComponent_Type Type;
    fread(&Type, sizeof(PrimitiveComponent_Type), 1, pFile);
    m_PrimitiveType = Type;
    Render_Type_2D _2DType= Render_Type_2D::RT2D_None;
    Render_Type_3D _3DType= Render_Type_3D::RT3D_End;


    fread(&_2DType, sizeof(Render_Type_2D), 1, pFile);
    fread(&_3DType, sizeof(Render_Type_3D), 1, pFile);

    size_t Size;
    fread(&Size, sizeof(size_t), 1, pFile);
    for (size_t i = 0; i < Size; i++)
    {
        m_vecMaterialSlot[i]->Load(pFile);
    }
    bool DistortionEnable;
    fread(&DistortionEnable, sizeof(bool), 1, pFile);
    m_DistortionEnable = DistortionEnable;
}

#include "GameObject.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Component/Transform.h"
#include "Component/SpriteComponent.h"

#include "Component/Camera.h"
#include "Component/Collider.h"
#include "Component/ColliderBox2D.h"
#include "Component/ColliderCircle.h"
#include "Component/ColliderLine2D.h"
#include "Component/ColliderPixel.h"
#include "Component/Component.h"
#include "Component/DistortionComponent.h"
#include "Component/ObjectComponent.h"
#include "Component/PaperBurnComponent.h"
#include "Component/ParticleSystemComponent.h"
#include "Component/PrimitiveComponent.h"
#include "Component/RigidBodyComponent.h"
#include "Component/SceneComponent.h"
#include "Component/SpringArm.h"
#include "Component/SpringArm2D.h"
#include "Component/SpriteComponent.h"
#include "Component/Transform.h"
#include "Component/WidgetComponent.h"
CGameObject::CGameObject() :
	m_Start(false),
	m_pScene(nullptr),
	m_LifeTime(0.f),
	m_LifeTimeEnable(false),
	m_Owner(nullptr),
	m_CreateEnemyEffect(false),
	m_CreateEnemyOrder(0)
{
	m_SceneComponentList.resize(0);
	m_RootComponent = CreateSceneComponent<CSceneComponent>("DefaultRoot");
	m_ClassType = Client_Class_Type::End;
	m_ObjectType = Client_Object_Type::End;
	m_EnemyType = Client_Enemy_Type::End;
	//m_SceneComponentList.push_back(m_RootComponent);
}

CGameObject::CGameObject(const CGameObject& obj)
{
	*this = obj;
	m_ClassType = obj.m_ClassType;
	m_ObjectType = obj.m_ObjectType;
	m_EnemyType = obj.m_EnemyType;

	m_RefCount = 1;
}

CGameObject::~CGameObject()
{
	auto    iter = m_SceneComponentList.begin();
	auto    iterEnd = m_SceneComponentList.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_RELEASE((*iter));
	}

	m_SceneComponentList.clear();
}

void CGameObject::Active(bool bActive)
{
	CRef::Active(bActive);

	if (m_RootComponent)
		m_RootComponent->Active(bActive);
}

void CGameObject::SetRootComponent(CSceneComponent* Root)
{
	auto	iter = m_SceneComponentList.begin();
	auto	iterEnd = m_SceneComponentList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == m_RootComponent)
		{
			SAFE_RELEASE((*iter));
			m_SceneComponentList.erase(iter);
			break;
		}
	}

	m_RootComponent = Root;
}

void CGameObject::SetRootCloneComponent(CSceneComponent* Root, bool Enable)
{
	{
		auto	iter = m_SceneComponentList.begin();
		auto	iterEnd = m_SceneComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			SAFE_RELEASE((*iter));
			break;
		}
		m_SceneComponentList.clear();
	}

	std::vector<CSceneComponent*>VecComponent;
	Root->GetAllComponent(VecComponent);
	for (size_t i = 0; i < VecComponent.size(); i++)
	{
		m_SceneComponentList.push_back(VecComponent[i]);
		VecComponent[i]->Enable(Enable);
		this->Enable(Enable);
		VecComponent[i]->SetOwner(this);
	}

	m_RootComponent = Root;
	Root->SetOwner(this);
}
CSceneComponent* CGameObject::FindSceneComponent(const std::string& Name)
{
	if (m_RootComponent == nullptr)
		return nullptr;

	return m_RootComponent->FindComponent(Name);
}

void CGameObject::GetAllSceneComponentName(std::vector<HierarchyName>& vecName)
{
	if (!m_RootComponent)
		return;

	m_RootComponent->GetAllComponentName(vecName);
}

void CGameObject::GetAllSceneComponent(std::vector<CSceneComponent*>& vecComponent)
{
	if (!m_RootComponent)
		return;

	m_RootComponent->GetAllComponent(vecComponent);
}

CGameObject* CGameObject::FindObjectChild(const std::string& Name)
{
	size_t	Size = m_vecObject.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecObject[i]->GetName() == Name)
			return m_vecObject[i];
	}
	return nullptr;
}

CObjectComponent* CGameObject::FindObjectComponent(const std::string& Name)
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		if (m_vecObjectComponent[i]->GetName() == Name)
			return m_vecObjectComponent[i];
	}

	return nullptr;
}

void CGameObject::GetAllObjectComponentName(std::vector<std::string>& vecName)
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		vecName.push_back(m_vecObjectComponent[i]->GetName());
	}
}

void CGameObject::GetAllObjectComponent(std::vector<CObjectComponent*>& vecComponent)
{
	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		vecComponent.push_back(m_vecObjectComponent[i]);
	}
}

void CGameObject::Start()
{
	m_Start = true;

	m_RootComponent->Start();
}

bool CGameObject::Init()
{
	// 기본 RootComponent 하나를 무조건 만들어준다.
	//m_RootComponent = CreateSceneComponent<CSceneComponent>("DefaultRoot");
	//m_RootComponent->Release();

	return true;
}

void CGameObject::Update(float DeltaTime)
{
	if (m_LifeTimeEnable)
	{
		m_LifeTime -= DeltaTime;

		if (m_LifeTime <= 0.f)
		{
			Active(false);
		}
			
	}

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Update(DeltaTime);
	}
	m_RootComponent->Update(DeltaTime);
}

void CGameObject::PostUpdate(float DeltaTime)
{
	m_RootComponent->PostUpdate(DeltaTime);

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PostUpdate(DeltaTime);
	}
}

void CGameObject::Collision(float DeltaTime)
{
	m_RootComponent->Collision(DeltaTime);

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Collision(DeltaTime);
	}
}

void CGameObject::PrevRender(float DeltaTime)
{
	m_RootComponent->PrevRender(DeltaTime);

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->PrevRender(DeltaTime);
	}
}

void CGameObject::Render(float DeltaTime)
{
	m_RootComponent->Render(DeltaTime);

	size_t	Size = m_vecObjectComponent.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecObjectComponent[i]->Render(DeltaTime);
	}
}

CGameObject* CGameObject::Clone()
{
	return new CGameObject(*this);
}

void CGameObject::Animation2DNotify(const std::string& Name)
{
}

void CGameObject::ClearTransformState()
{
	auto    iter = m_SceneComponentList.begin();
	auto    iterEnd = m_SceneComponentList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->ClearTransformState();
	}
}

void CGameObject::Move(const Vector2& Target)
{
	m_RootComponent->Move(Target);
}

void CGameObject::Move(const Vector3& Target)
{
	m_RootComponent->Move(Target);
}

Vector3 CGameObject::GetVelocityScale() const
{
	return m_RootComponent.Get()->GetVelocityScale();
}

Vector3 CGameObject::GetVelocityRot() const
{
	return m_RootComponent.Get()->GetVelocityRot();
}

Vector3 CGameObject::GetVelocity() const
{
	return m_RootComponent.Get()->GetVelocity();
}

Vector3 CGameObject::GetAxis(AXIS Axis) const
{
	return m_RootComponent.Get()->GetAxis(Axis);
}

void CGameObject::SetInheritScale(bool Inherit)
{
	m_RootComponent->SetInheritScale(Inherit);
}

void CGameObject::SetInheritRotX(bool Inherit)
{
	m_RootComponent->SetInheritRotX(Inherit);
}

void CGameObject::SetInheritRotY(bool Inherit)
{
	m_RootComponent->SetInheritRotY(Inherit);
}

void CGameObject::SetInheritRotZ(bool Inherit)
{
	m_RootComponent->SetInheritRotZ(Inherit);
}

void CGameObject::SetInheritPosZ(bool Inherit)
{
	m_RootComponent->SetInheritPosZ(Inherit);
}

void CGameObject::SetUpdatePosZ(bool UpdatePosZ)
{
	m_RootComponent->SetUpdatePosZ(UpdatePosZ);
}

void CGameObject::InheritScale()
{
	m_RootComponent->InheritScale();
}

void CGameObject::InheritRot()
{
	m_RootComponent->InheritRot();
}

void CGameObject::InheritPos()
{
	m_RootComponent->InheritPos();
}

bool CGameObject::GetInheritPosZ() const
{
	return m_RootComponent->GetInheritPosZ();
}

Vector3 CGameObject::GetRelativeScale() const
{
	return m_RootComponent.Get()->GetRelativeScale();
}

Vector3 CGameObject::GetRelativeRotation() const
{
	return m_RootComponent.Get()->GetRelativeRotation();
}

Vector3 CGameObject::GetRelativePos() const
{
	return m_RootComponent.Get()->GetRelativePos();
}

void CGameObject::SetRelativeScale(const Vector3& Scale)
{
	m_RootComponent->SetRelativeScale(Scale);
}

void CGameObject::SetRelativeScale(float x, float y, float z)
{
	m_RootComponent->SetRelativeScale(x, y, z);
}

void CGameObject::SetRelativeRotation(const Vector3& Rot)
{
	m_RootComponent->SetRelativeRotation(Rot);
}

void CGameObject::SetRelativeRotation(float x, float y, float z)
{
	m_RootComponent->SetRelativeRotation(x, y, z);
}

void CGameObject::SetRelativeRotationX(float x)
{
	m_RootComponent->SetRelativeRotationX(x);
}

void CGameObject::SetRelativeRotationY(float y)
{
	m_RootComponent->SetRelativeRotationY(y);
}

void CGameObject::SetRelativeRotationZ(float z)
{
	m_RootComponent->SetRelativeRotationZ(z);
}

void CGameObject::SetRelativePos(const Vector3& Pos)
{
	m_RootComponent->SetRelativePos(Pos);
}

void CGameObject::SetRelativePos(float x, float y, float z)
{
	m_RootComponent->SetRelativePos(x, y, z);
}

void CGameObject::AddRelativeScale(const Vector3& Scale)
{
	m_RootComponent->AddRelativeScale(Scale);
}

void CGameObject::AddRelativeScale(float x, float y, float z)
{
	m_RootComponent->AddRelativeScale(x, y, z);
}

void CGameObject::AddRelativeRotation(const Vector3& Rot)
{
	m_RootComponent->AddRelativeRotation(Rot);
}

void CGameObject::AddRelativeRotation(float x, float y, float z)
{
	m_RootComponent->AddRelativeRotation(x, y, z);
}

void CGameObject::AddRelativeRotationX(float x)
{
	m_RootComponent->AddRelativeRotationX(x);
}

void CGameObject::AddRelativeRotationY(float y)
{
	m_RootComponent->AddRelativeRotationY(y);
}

void CGameObject::AddRelativeRotationZ(float z)
{
	m_RootComponent->AddRelativeRotationZ(z);
}

void CGameObject::AddRelativePos(const Vector3& Pos)
{
	m_RootComponent->AddRelativePos(Pos);
}

void CGameObject::AddRelativePos(float x, float y, float z)
{
	m_RootComponent->AddRelativePos(x, y, z);
}

Vector3 CGameObject::GetWorldScale() const
{
	return m_RootComponent.Get()->GetWorldScale();
}

Vector3 CGameObject::GetWorldRotation() const
{
	return m_RootComponent.Get()->GetWorldRotation();
}

Vector3 CGameObject::GetWorldPos() const
{
	return m_RootComponent.Get()->GetWorldPos();
}

Vector3 CGameObject::GetPivot() const
{
	return m_RootComponent.Get()->GetPivot();
}

Vector3 CGameObject::GetMeshSize() const
{
	return m_RootComponent.Get()->GetMeshSize();
}

Matrix CGameObject::GetScaleMatrix() const
{
	return m_RootComponent.Get()->GetScaleMatrix();
}

Matrix CGameObject::GetRotatinMatrix() const
{
	return m_RootComponent.Get()->GetRotatinMatrix();
}

Matrix CGameObject::GetTranslationMatrix() const
{
	return m_RootComponent.Get()->GetTranslationMatrix();
}

Matrix CGameObject::GetWorldMatrix() const
{
	return m_RootComponent.Get()->GetWorldMatrix();
}

void CGameObject::SetPivot(const Vector3& Pivot)
{
	m_RootComponent->SetPivot(Pivot);
}

void CGameObject::SetPivot(float x, float y, float z)
{
	m_RootComponent->SetPivot(x, y, z);
}

void CGameObject::SetMeshSize(const Vector3& Size)
{
	m_RootComponent->SetMeshSize(Size);
}

void CGameObject::SetMeshSize(float x, float y, float z)
{
	m_RootComponent->SetMeshSize(x, y, z);
}

void CGameObject::SetWorldScale(const Vector3& Scale)
{
	m_RootComponent->SetWorldScale(Scale);
}

void CGameObject::SetWorldScale(float x, float y, float z)
{
	m_RootComponent->SetWorldScale(x, y, z);
}

void CGameObject::SetWorldRotation(const Vector3& Rot)
{
	m_RootComponent->SetWorldRotation(Rot);
}

void CGameObject::SetWorldRotation(float x, float y, float z)
{
	m_RootComponent->SetWorldRotation(x, y, z);
}

void CGameObject::SetWorldRotationX(float x)
{
	m_RootComponent->SetWorldRotationX(x);
}

void CGameObject::SetWorldRotationY(float y)
{
	m_RootComponent->SetWorldRotationY(y);
}

void CGameObject::SetWorldRotationZ(float z)
{
	m_RootComponent->SetWorldRotationZ(z);
}

void CGameObject::SetWorldPos(const Vector3& Pos)
{
	m_RootComponent->SetWorldPos(Pos);
}

void CGameObject::SetWorldPos(float x, float y, float z)
{
	m_RootComponent->SetWorldPos(x, y, z);
}

void CGameObject::AddWorldScale(const Vector3& Scale)
{
	m_RootComponent->AddWorldScale(Scale);
}

void CGameObject::AddWorldScale(float x, float y, float z)
{
	m_RootComponent->AddWorldScale(x, y, z);
}

void CGameObject::AddWorldRotation(const Vector3& Rot)
{
	m_RootComponent->AddWorldRotation(Rot);
}

void CGameObject::AddWorldRotation(float x, float y, float z)
{
	m_RootComponent->AddWorldRotation(x, y, z);
}

void CGameObject::AddWorldRotationX(float x)
{
	m_RootComponent->AddWorldRotationX(x);
}

void CGameObject::AddWorldRotationY(float y)
{
	m_RootComponent->AddWorldRotationY(y);
}

void CGameObject::AddWorldRotationZ(float z)
{
	m_RootComponent->AddWorldRotationZ(z);
}

void CGameObject::AddWorldPos(const Vector3& Pos)
{
	m_RootComponent->AddWorldPos(Pos);
}

void CGameObject::AddWorldPos(float x, float y, float z)
{
	m_RootComponent->AddWorldPos(x, y, z);
}

void CGameObject::AddCamera(CCamera* Camera)
{
	m_pScene->GetCameraManager()->AddCamera(Camera);
}

void CGameObject::SaveFullPath(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "wb");

	if (!pFile)
		return;
	Save(pFile);
	fclose(pFile);
}

void CGameObject::LoadFullPath(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "rb");

	if (!pFile)
		return;
	Load(pFile);
	fclose(pFile);
}

void CGameObject::Save(FILE* pFile)
{
	int Length = (int)strlen(GetName().c_str());
	fwrite(&Length, sizeof(int), 1, pFile);
	fwrite(GetName().c_str(), sizeof(char), Length, pFile);

	fwrite(&m_ClassType, sizeof(Client_Class_Type), 1, pFile);
	fwrite(&m_ObjectType, sizeof(Client_Object_Type), 1, pFile);
	fwrite(&m_EnemyType, sizeof(Client_Enemy_Type), 1, pFile);
	fwrite(&m_DoorDir, sizeof(Door_Dir), 1, pFile);
	if (m_ClassType == Client_Class_Type::Enemy)
	{
		int CreateEnemyEffect = m_CreateEnemyEffect ? 1 : 0;
		fwrite(&CreateEnemyEffect, sizeof(int), 1, pFile);
		fwrite(&m_CreateEnemyOrder, sizeof(int), 1, pFile);
	}
	Component_Class_Type  Type = m_RootComponent->GetComponentClassType();
	fwrite(&Type, sizeof(Component_Class_Type), 1, pFile);

	m_RootComponent->Save(pFile);

	{
		Length = (int)m_SceneComponentList.size();
		fwrite(&Length, sizeof(int), 1, pFile);
		auto iter = m_SceneComponentList.begin();
		auto iterEnd = m_SceneComponentList.end();

		for (; iter != iterEnd; ++iter)
		{
			if (m_RootComponent != (*iter))
			{
				Component_Class_Type  Type = (*iter)->GetComponentClassType();
				fwrite(&Type, sizeof(Component_Class_Type), 1, pFile);
				(*iter)->Save(pFile);
		}
	}
}

	//{
	//	auto iter = m_vecObjectComponent.begin();
	//	auto iterEnd = m_vecObjectComponent.end();
	//
	//	for (; iter != iterEnd; ++iter)
	//	{
	//		(*iter)->Save(pFile);
	//	}
	//}

}

void CGameObject::Load(FILE* pFile)
{
	int Length = -1;
	char	Name[256] = {};
	fread(&Length, sizeof(int), 1, pFile);
	fread(Name, sizeof(char), Length, pFile);
	SetName(Name);


	fread(&m_ClassType, sizeof(Client_Class_Type), 1, pFile);
	fread(&m_ObjectType, sizeof(Client_Object_Type), 1, pFile);
	fread(&m_EnemyType, sizeof(Client_Enemy_Type), 1, pFile);
	fread(&m_DoorDir, sizeof(Door_Dir), 1, pFile);

	if (m_ClassType == Client_Class_Type::Enemy)
	{
		int CreateEnemyEffect = m_CreateEnemyEffect ? 1 : 0;
		fread(&CreateEnemyEffect, sizeof(int), 1, pFile);
		fread(&m_CreateEnemyOrder, sizeof(int), 1, pFile);
		if (CreateEnemyEffect == 1)
			m_CreateEnemyEffect = true;
		else
			m_CreateEnemyEffect = false;
	}
	Component_Class_Type  Type;
	fread(&Type, sizeof(Component_Class_Type), 1, pFile);
	CSceneComponent* Component = nullptr;
	switch (Type)
	{
	case Component_Class_Type::Scene:
		Component = CreateSceneComponent<CSceneComponent>("Scene");
		break;
	case Component_Class_Type::Sprite:
		Component = CreateSceneComponent<CSpriteComponent>("Sprite");
		break;
	case Component_Class_Type::ColliderBox2D:
		Component = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
		break;
	case Component_Class_Type::ColliderCircle:
		Component = CreateSceneComponent<CColliderCircle>("ColliderCircle");
		break;
	case Component_Class_Type::ColliderPixel:
		Component = CreateSceneComponent<CColliderPixel>("ColliderPixel");
		break;
	case Component_Class_Type::Camera:
		Component = CreateSceneComponent<CCamera>("Camera");
		break;
	case Component_Class_Type::SpringArm:
		Component = CreateSceneComponent<CSpringArm>("SpringArm");
		break;
	case Component_Class_Type::SpringArm2D:
		Component = CreateSceneComponent<CSpringArm2D>("SpringArm2D");
		break;
	case Component_Class_Type::Primitive:
		Component = CreateSceneComponent<CPrimitiveComponent>("Primitive");
		break;
	case Component_Class_Type::ParticleSystem:
		break;
	case Component_Class_Type::Mesh:
		break;
	case Component_Class_Type::Collider:
		break;
	case Component_Class_Type::Particle:
		break;
	case Component_Class_Type::Widget:
		break;
	case Component_Class_Type::TileMap:
		break;
	case Component_Class_Type::End:
		break;
	}
	SetRootComponent(Component);
	m_RootComponent->Load(pFile);

	{
		fread(&Length, sizeof(int), 1, pFile);

		for (int i = 0; i < Length - 1; ++i)
		{
			fread(&Type, sizeof(Component_Class_Type), 1, pFile);
			switch (Type)
			{
			case Component_Class_Type::Scene:
				Component = CreateSceneComponent<CSceneComponent>("Scene");
				break;
			case Component_Class_Type::Sprite:
				Component = CreateSceneComponent<CSpriteComponent>("Sprite");
				break;
			case Component_Class_Type::ColliderBox2D:
				Component = CreateSceneComponent<CColliderBox2D>("ColliderBox2D");
				break;
			case Component_Class_Type::ColliderCircle:
				Component = CreateSceneComponent<CColliderCircle>("ColliderCircle");
				break;
			case Component_Class_Type::ColliderPixel:
				Component = CreateSceneComponent<CColliderPixel>("ColliderPixel");
				break;
			case Component_Class_Type::Camera:
				Component = CreateSceneComponent<CCamera>("Camera");
				break;
			case Component_Class_Type::SpringArm:
				Component = CreateSceneComponent<CSpringArm>("SpringArm");
				break;
			case Component_Class_Type::SpringArm2D:
				Component = CreateSceneComponent<CSpringArm2D>("SpringArm2D");
				break;
			case Component_Class_Type::Primitive:
				Component = CreateSceneComponent<CPrimitiveComponent>("Primitive");
				break;
			case Component_Class_Type::ParticleSystem:
				break;
			case Component_Class_Type::Mesh:
				break;
			case Component_Class_Type::Collider:
				break;
			case Component_Class_Type::Particle:
				break;
			case Component_Class_Type::Widget:
				break;
			case Component_Class_Type::TileMap:
				break;
			case Component_Class_Type::End:
				break;
			}

			Component->Load(pFile);
			m_RootComponent->AddChild(Component);
		}


	}
}

void CGameObject::ClientSave(FILE* pFile)
{
	fwrite(&m_ClassType, sizeof(Client_Class_Type), 1, pFile);
	fwrite(&m_ObjectType, sizeof(Client_Object_Type), 1, pFile);
	fwrite(&m_EnemyType, sizeof(Client_Enemy_Type), 1, pFile);
	fwrite(&m_DoorDir, sizeof(Door_Dir), 1, pFile);
	if (m_ClassType == Client_Class_Type::Enemy)
	{
		int CreateEnemyEffect = m_CreateEnemyEffect ? 1 : 0;
		fwrite(&CreateEnemyEffect, sizeof(int), 1, pFile);
		fwrite(&m_CreateEnemyOrder, sizeof(int), 1, pFile);
	}
	Vector3	Pos, Rot, Scale, Pivot;
	Pos = GetWorldPos();
	Rot = GetWorldRotation();
	Scale = GetWorldScale();
	Pivot = GetPivot();
	fwrite(&Pos, sizeof(Vector3), 1, pFile);
	fwrite(&Rot, sizeof(Vector3), 1, pFile);
	fwrite(&Scale, sizeof(Vector3), 1, pFile);
	fwrite(&Pivot, sizeof(Vector3), 1, pFile);
}

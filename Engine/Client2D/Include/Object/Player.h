#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/Camera.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
#include "../GlobalValue.h"
#include "../PlayerStatus.h"
class CPlayer :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();

protected:

	std::vector<CGameObject*> m_vDashTexture;
	CPlayerStatus m_Status;
	CSharedPtr<CWidgetComponent> m_PlayerInfoWidgetComponent;
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSpringArm2D> m_Arm;
	CSharedPtr<CCamera> m_Camera;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CRigidBodyComponent> m_Body;
	class CAnimation2D* m_Animation2D;
	class CInventory* m_Inventory;
	class CWeapon* m_Weapon;
	class CWeaponArm* m_WeaponArm;
	bool m_OneAttack;
	float m_Angle;
	Object_Dir m_Dir;
protected:
public:
	CPlayerStatus& GetStatus()
	{
		return m_Status;
	}
	Object_Dir GetDir() const
	{
		return m_Dir;
	}
	float GetAngle() const
	{
		return m_Angle;
	}
	Vector3 GetForce() const
	{
		return m_Body->GetForce();
	}
public:
	void SetInventory(CInventory* Inventory);
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayer* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void LeftMove(float DeltaTime);
	void RightMove(float DeltaTime);
	void DownMove(float DeltaTime);
	void JumpMove(float DeltaTime);
	void Attack(float DeltaTime);
	void Dash(float DeltaTime);
	void InventoryOnOff(float DeltaTime);
public:
	void AnimationFrameEnd(const std::string& Name);
	void CollisionBegin(const HitResult& result, CCollider* Collider);
};

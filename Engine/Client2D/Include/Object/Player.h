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
#include <EngineFSM.h>
#include "../Animation2D/Animation2D_FSM.h"

enum class ePlayerState
{
	Idle,
	Move,
	Jump
};

class CPlayer :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayer();
	CPlayer(const CPlayer& obj);
	virtual ~CPlayer();

private:

	std::vector<CGameObject*> m_vDashTexture;
	CPlayerStatus m_Status;
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSpringArm2D> m_Arm;
	CSharedPtr<CCamera> m_Camera;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CColliderBox2D> m_Collider2DHorizon;
	CSharedPtr<CColliderBox2D> m_Collider2DVertical;
	CSharedPtr<CRigidBodyComponent> m_Body;
	CSharedPtr<CAnimation2D_FSM> m_Animation2D;

	CSharedPtr<CWidgetComponent> m_WidgetComponent;
	class CPlayerWorldWidget* m_PlayerWidget;

	class CWeaponArm* m_WeaponArm;

	CEngineFSM<CPlayer>m_BodyFSM;

	class CWeapon*  m_Weapon;


	bool m_OneAttack;
	float m_Angle;
	Object_Dir m_Dir;

	ePlayerState m_State;
	ePlayerState m_PrevState;
	bool m_WallCol;
	int m_Coin;
	bool m_StageMove;
	float m_DustCount;
	float m_MoveSound;
protected:
public:
	void StageMove()
	{
		m_StageMove = true;
	}
	int GetCoin()
	{
		return m_Coin;
	}

	void AddCoin(int Coin)
	{
		m_Coin += Coin;
	}
	bool SubCoin(int Coin)
	{
		if (m_Coin < Coin)
		{
			return false;
		}
		m_Coin -= Coin;
		return true;
	}

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
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayer* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	void SetGravity(bool bGravity);
	void SetStatus(const std::string& Name);
public:
	void LeftMove(float DeltaTime);
	void RightMove(float DeltaTime);
	void DownMove(float DeltaTime);
	void JumpMove(float DeltaTime);
	void Attack(float DeltaTime);
	void Dash(float DeltaTime);
	void InventoryOnOff(float DeltaTime);
	void MapOnOff(float DeltaTime);
	void WeaponChange(float DeltaTime);
	void InputInteractionInputKey(float DeltaTime);
	void ShopUIOnOff(float DeltaTime);
	void StatusUIOnOff(float DeltaTime);
public:
//status 가져오기
	int GetDamage();
	int GetDamageMax();
	int GetArmor();
	int GetCritical();
	float GetMoveSpeed();
	float GetAttackSpeed();
	float GetReloadSpeed();
	int GetAttackDamage(bool Critical);
public:
	void EnemyHit(int Damage);
public:
	void AnimationFrameEnd(const std::string& Name);
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionHorizonBegin(const HitResult& result, CCollider* Collider);
	void CollisionHorizonMiddle(const HitResult& result, CCollider* Collider);
	void CollisionHorizonEnd(const HitResult& result, CCollider* Collider);
	void CollisionVerticalBegin(const HitResult& result, CCollider* Collider);
	void CollisionVerticalMiddle(const HitResult& result, CCollider* Collider);
	void CollisionVerticalEnd(const HitResult& result, CCollider* Collider);
	//충돌
	void ColDirHorizon(float Angle, CCollider* Col);
	void ColDirVertical(float Angle, CCollider* Col);
	void ColTilePassDirVertical(float Angle, CCollider* Col);
public:
	//FSM
	void BodyIdleStart();
	void BodyIdleStay();
	void BodyMoveStart();
	void BodyMoveStay();
	void BodyJumpStart();
	void BodyJumpStay();

};

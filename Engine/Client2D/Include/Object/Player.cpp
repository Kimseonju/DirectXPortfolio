
#include "Player.h"
#include "Input.h"
#include "Bullet.h"
#include "Scene/Scene.h"
#include "Resource/Material.h"
#include "Engine.h"
#include "Weapon.h"
#include "WeaponArm.h"
#include "ShortSword.h"
#include "../GlobalValue.h"
#include "Revolver.h"
#include "../UI/PlayerWorldInfoWidget.h"
#include "MetalBoomerang.h"
#include "PlayerDash.h"
#include "../UI/BasicMouse.h"
#include "../UI/UIManager.h"
CPlayer::CPlayer() :
	m_OneAttack(false),
	m_Weapon(nullptr),
	m_WeaponArm(nullptr),
	m_Angle(0.f),
	m_Dir(Object_Dir::Left),
	m_WallCol(false)
{
}

CPlayer::CPlayer(const CPlayer& obj) :
	CGameObject(obj)
{

	m_Body = (CRigidBodyComponent*)FindSceneComponent("Body");
	m_Collider2D = (CColliderBox2D*)FindSceneComponent("Collider2D");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Arm = (CSpringArm2D*)FindSceneComponent("Arm");
	m_Camera = (CCamera*)FindSceneComponent("Camera");

	m_OneAttack = obj.m_OneAttack;
	m_WeaponArm = obj.m_WeaponArm->Clone();
	m_Weapon = obj.m_Weapon->Clone();
	m_OneAttack = obj.m_OneAttack;
	//임시 삭제용

	m_PlayerInfoWidgetComponent = (CWidgetComponent*)FindSceneComponent("PlayerInfoWidget");
}

CPlayer::~CPlayer()
{
}

void CPlayer::Start()
{
	CGameObject::Start();
}

bool CPlayer::Init()
{
	CGameObject::Init();
	m_Status.Init();
	


	m_Body = CreateSceneComponent<CRigidBodyComponent>("Body");
	m_Collider2D = CreateSceneComponent<CColliderBox2D>("Collider2D");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");

	m_Arm = CreateSceneComponent<CSpringArm2D>("Arm");
	m_Camera = CreateSceneComponent<CCamera>("Camera");
	m_PlayerInfoWidgetComponent = CreateSceneComponent<CWidgetComponent>("PlayerInfoWidget");
	m_Camera->SetCameraZoom(2.f);
	SetRootComponent(m_Sprite);

	m_Sprite->SetRelativeScale(15.f, 20.f, 1.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Collider2D->SetCollisionProfile("Player");
	m_Collider2D->AddCollisionCallbackFunction<CPlayer>(Collision_State::Begin, this,
		&CPlayer::CollisionBegin);
	m_Collider2D->AddCollisionCallbackFunction<CPlayer>(Collision_State::Middle, this,
		&CPlayer::CollisionMiddle);
	m_Collider2D->AddCollisionCallbackFunction<CPlayer>(Collision_State::End, this,
		&CPlayer::CollisionEnd);
	m_Collider2D->SetExtent(5.f, 5.f);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_Body);

	m_Arm->SetOffset(-640.f, -360.f, 0.f);
	m_Arm->SetInheritPosZ(false);

	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);

	//SpriteMtrl->SetBaseColor(1.f, 0.f, 0.f, 1.f);
	//SpriteMtrl->AddTexture("PlayerTex", TEXT("teemo.png"));

	m_Sprite->CreateAnimation2D<CAnimation2D_FSM>();

	m_Animation2D = (CAnimation2D_FSM*)m_Sprite->GetAnimation2D();
	m_Animation2D->SetIdleAnimation2D("PlayerIdle");
	m_Animation2D->SetMoveAnimation2D("PlayerRun");
	m_Animation2D->SetJumpAnimation2D("PlayerJump");

	CInput::GetInst()->AddKeyCallback<CPlayer>("Left", KT_Push, this, &CPlayer::LeftMove);
	CInput::GetInst()->AddKeyCallback<CPlayer>("Right", KT_Push, this, &CPlayer::RightMove);
	CInput::GetInst()->AddKeyCallback<CPlayer>("Jump", KT_Push, this, &CPlayer::JumpMove);
	CInput::GetInst()->AddKeyCallback<CPlayer>("Attack", KT_Down, this, &CPlayer::Attack);
	CInput::GetInst()->AddKeyCallback<CPlayer>("InventoryOnOff", KT_Down, this, &CPlayer::InventoryOnOff);
	CInput::GetInst()->AddKeyCallback<CPlayer>("Dash", KT_Down, this, &CPlayer::Dash);
	CInput::GetInst()->AddKeyCallback<CPlayer>("MapOnOff", KT_Down, this, &CPlayer::MapOnOff);
	CInput::GetInst()->AddKeyCallback<CPlayer>("MouseWhell", KT_Down, this, &CPlayer::WeaponChange);
	//마우스회전용
	
	m_WeaponArm = m_pScene->SpawnObject<CWeaponArm>("basicWeaponArm");
	m_WeaponArm->SetRelativePos(20.f,0.f,0.f);
	PushObjectChild(m_WeaponArm);
	
	//m_Weapon = m_pScene->SpawnObject<CShortSword>("basicWeapon");
	//m_Weapon = m_pScene->SpawnObject<CRevolver>("Revolver");
	//m_Weapon = m_pScene->SpawnObject<CMetalBoomerang>("MetalBoomerang");
	//m_Weapon->SetRelativePos(10.f, 0.f, 0.f); 
	


	m_PlayerInfoWidgetComponent->CreateWidget<CPlayerWorldInfoWidget>("PlayerInfo");

	m_PlayerInfoWidgetComponent->SetRelativePos(-100.f, 50.f, 0.f);
	m_PlayerInfoWidgetComponent->SetRelativeScale(200.f, 120.f, 1.f);
	m_Sprite->AddChild(m_PlayerInfoWidgetComponent);


	m_BodyFSM.CreateState("Idle", this, &CPlayer::BodyIdleStay, &CPlayer::BodyIdleStart);
	m_BodyFSM.CreateState("Move", this, &CPlayer::BodyMoveStay, &CPlayer::BodyMoveStart);
	m_BodyFSM.CreateState("Jump", this, &CPlayer::BodyJumpStay, &CPlayer::BodyJumpStart);
	m_BodyFSM.ChangeState("Idle");
	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_Status.Update(DeltaTime);
	m_BodyFSM.Update();
	m_WallCol = false;
	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Vector3 Pos = m_WeaponArm->GetWorldPos();
	Vector2 Pos2 = Vector2(Pos.x, Pos.y);
	//플레이어가 왼쪽
	if (GetWorldPos().x > MousePos.x)
	{
		m_Dir = Object_Dir::Left;
		m_Sprite->SetHorizontalReverse2DEnable(true);
	}
	if (GetWorldPos().x < MousePos.x)
	{
		m_Dir = Object_Dir::Right;
		m_Sprite->SetHorizontalReverse2DEnable(false); 
	}

	m_WeaponArm->SetDir(m_Dir);
	CWeapon* Item= (CWeapon*)CUIManager::GetInst()->GetInventory()->GetWeapon();
	if (Item)
	{
		if (m_Weapon != Item)
		{
			if (m_Weapon)
			{
				m_Status.DetachWeapon(m_Weapon->GetStatus());
				m_Weapon->Enable(false);
			}
			m_Weapon = Item;
			m_Weapon->Enable(true);
			m_Status.AttachWeapon(m_Weapon->GetStatus());
			m_WeaponArm->PushObjectChild(m_Weapon);
			m_Weapon->SetCurrentAttackDelay(1.f);
		}
	}
	else
	{
		if (m_Weapon)
		{
			m_Status.DetachWeapon(m_Weapon->GetStatus());
			m_Weapon->Enable(false);
			m_Weapon = nullptr;
		}
	}
	
	

	if(m_Body->IsDashEffect())
	{
		CPlayerDash* obj = m_pScene->SpawnObject<CPlayerDash>("CPlayerDash");
		obj->SetWorldPos(GetWorldPos());
		obj->SetDir(m_Dir);
		m_Body->SetDashEffect(false);
	}

}

void CPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	CGameObject::Render(DeltaTime); 
	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Vector3 Pos = m_WeaponArm->GetWorldPos();
	Vector2 Pos2 = Vector2(Pos.x, Pos.y);
	float angle = Pos2.GetAngle(MousePos);

	if (m_Weapon)
	{

		m_Weapon->SetDir(m_Dir);
		if (m_Weapon->GetWeaponType() == Weapon_Type::Melee)
		{
			//임시로
			//선형보간 적용하여 움직임구현하기		
			//게임상엔 없네??ㅇ
			float LerpAngle = CGlobalValue::Lerp2DMax(0.f, 90.f, m_Weapon->GetCurrentAttackDelay() * 10.f);
			if (m_OneAttack)
			{
				m_WeaponArm->SetRelativeRotationZ(angle + 90.f);
				m_Weapon->SetRelativeRotationZ(angle + 90.f);
			}
			else
			{
				m_WeaponArm->SetRelativeRotationZ(angle - 90.f);
				m_Weapon->SetRelativeRotationZ(angle - 90.f);

			}
		}
		else if (m_Weapon->GetWeaponType() == Weapon_Type::Range)
		{
			m_Weapon->SetRelativeRotationZ(angle + m_Weapon->GetRebound());
		}
	}
	m_Angle = angle;
}

void CPlayer::Collision(float DeltaTime)
{
	CGameObject::Collision(DeltaTime);
}

void CPlayer::Render(float DeltaTime)
{
	
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Animation2DNotify(const std::string& Name)
{
	
}

void CPlayer::LeftMove(float DeltaTime)
{
	Vector3 vec(-1.f, 0.f, 0.f);
	m_Body->SetDir(vec);
}

void CPlayer::RightMove(float DeltaTime)
{
	Vector3 vec(1.f, 0.f, 0.f);
	m_Body->SetDir(vec);
}

void CPlayer::DownMove(float DeltaTime)
{
}

void CPlayer::JumpMove(float DeltaTime)
{
	m_Body->Jump();
}

void CPlayer::Attack(float DeltaTime)
{
	if (CGlobalValue::MainMouse->GetState() == Mouse_State::World)
	{
		if (m_Weapon)
		{
			Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
			Vector3 Pos = m_Weapon->GetWorldPos();
			Vector2 Pos2 = Vector2(Pos.x, Pos.y);

			float angle = Pos2.GetAngle(MousePos);
			if (m_Weapon->Attack(angle))
			{
				m_OneAttack = !m_OneAttack;
				m_Camera->AddCameraShake(3.f, 3.f, 0.3f);
			}
		}
	}
}

void CPlayer::Dash(float DeltaTime)
{
	if (m_Status.GetDash() == 0)
	{
		return;
	}
	m_Status.Dash();
	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Vector3 Pos = GetWorldPos();
	Vector2 Pos2 = Vector2(Pos.x, Pos.y);

	float angle = Pos2.GetAngle(MousePos);
	m_Body->Dash(angle);

}

void CPlayer::InventoryOnOff(float DeltaTime)
{
	if (CUIManager::GetInst()->GetInventory()->IsEnable())
	{
		CUIManager::GetInst()->GetInventory()->Enable(false);
		CGlobalValue::MainMouse->SetState(Mouse_State::World);
	}
	else
	{
		CUIManager::GetInst()->GetInventory()->Enable(true);
		CGlobalValue::MainMouse->SetState(Mouse_State::UI);
	}
}
void CPlayer::MapOnOff(float DeltaTime)
{
	if (CUIManager::GetInst()->GetStageMap()->IsEnable())
	{
		CUIManager::GetInst()->GetStageMap()->Enable(false);
		CGlobalValue::MainMouse->SetState(Mouse_State::World);
	}
	else
	{
		CUIManager::GetInst()->GetStageMap()->Enable(true);
		CGlobalValue::MainMouse->SetState(Mouse_State::UI);
	}
}
void CPlayer::WeaponChange(float DeltaTime)
{
	CUIManager::GetInst()->GetPlayerUI()->WeaponChange();
}
void CPlayer::AnimationFrameEnd(const std::string& Name)
{
}

void CPlayer::CollisionBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass )
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirStart(Angle, result.DestCollider);
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		m_Body->StopDash();
		ColDirStart(Angle, result.DestCollider);
	}

	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::EnemyAttack)
	{

		CUIManager::GetInst()->GetPlayerUI()->Hit();
	}
}

void CPlayer::CollisionMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColDirMiddle(Angle, result.DestCollider);
		m_WallCol = true; 
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		m_Body->StopDash();
		ColDirStart(Angle, result.DestCollider);
		m_WallCol = true;
	}
}

void CPlayer::CollisionEnd(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass ||
		result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		if (!m_WallCol)
		{
			m_Body->SetGravity(true);
			m_Body->SetJump(true);
		}
	}
}

void CPlayer::ColDirStart(float Angle,CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale()/2.f;
	Vector3 PlayerPos = m_Collider2D->GetWorldPos();
	Vector3 PlayerScale = m_Collider2D->GetRelativeScale()/2.f;

	Vector3 ColCheckPos = PlayerPos - ColPos;

	//ColCheckPos의 y값이 음수라면 ColPos가 위쪽에있다는뜻인데..
	// 
	//왼쪽
	

	if (120.f < Angle && Angle < 230.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x += x;
		PlayerPos.x = XMove.x;
		SetWorldPos(PlayerPos);
	}
	//아래
	else if (230.f < Angle && Angle < 310.f)
	{
		m_Body->StopForceY();
		m_Body->StopForceX();
		m_Body->SetGravity(false);
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y += y;
		PlayerPos.y = XMove.y;
		SetWorldPos(PlayerPos);
 		m_Body->SetGravity(false);
		m_Body->SetJump(false);
	}
	//오른쪽방향
	else if (310.f < Angle || Angle < 30.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x -= x;
		PlayerPos.x = XMove.x;
		SetWorldPos(PlayerPos);

	}
	//위
	else if (30.f < Angle && Angle < 120.f)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y -= y;
		PlayerPos.y = XMove.y;
		SetWorldPos(PlayerPos);
	}

	//if (ColCheckPos.y < 0.f)
	//{
	//	m_Body->StopForceY();
	//
	//}
	//else //아니라면 아래쪽에 있다는 뜻
	//{
	//	m_Body->StopForceY();
	//	m_Body->SetGravity(false);
	//}
	////ColCheckPos가 짝수라면 ColPos는 왼쪽에 있음
	//if (ColCheckPos.x > 0.f)
	//{
	//	m_Body->StopForceX();
	//	float x = (PlayerScale.x + ColScale.x);
	//	Vector3 XMove = ColPos;
	//	XMove.x += x;
	//	SetWorldPos(XMove);
	//}
	//else //아니라면 오른쪽에 있다는 뜻
	//{
	//	m_Body->StopForceX();
	//	float x = (PlayerScale.x + ColScale.x);
	//	Vector3 XMove = ColPos;
	//	XMove.x -= x;
	//	SetWorldPos(XMove);
	//}
}

void CPlayer::ColDirMiddle(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = m_Collider2D->GetWorldPos();
	Vector3 PlayerScale = m_Collider2D->GetRelativeScale() / 2.f;

	Vector3 ColCheckPos = PlayerPos - ColPos;

	//ColCheckPos의 y값이 음수라면 ColPos가 위쪽에있다는뜻인데..
	// 
	//왼쪽


	if (120.f < Angle && Angle < 230.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x += x;
		PlayerPos.x = XMove.x;
		SetWorldPos(PlayerPos);
	}
	//아래
	else if (230.f < Angle && Angle < 310.f)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y += y;
		PlayerPos.y = XMove.y;
		SetWorldPos(PlayerPos);
 		m_Body->SetGravity(false);
	}
	//오른쪽방향
	else if (310.f < Angle || Angle < 30.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x -= x;
		PlayerPos.x = XMove.x;
		SetWorldPos(PlayerPos);

	}
	//위
	else if (30.f < Angle && Angle < 120.f)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y -= y;
		PlayerPos.y = XMove.y;
		SetWorldPos(PlayerPos);
	}
}

void CPlayer::ColDirEnd(CCollider* Col)
{
}

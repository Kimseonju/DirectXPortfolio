
#include "Player.h"
#include "Input.h"
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
#include "PlayerInteractionCollision.h"
#include "../ObjectStatusManager.h"
#include "../UI/PlayerWorldWidget.h"
CPlayer::CPlayer() :
	m_OneAttack(false),
	m_Weapon(nullptr),
	m_WeaponArm(nullptr),
	m_Angle(0.f),
	m_Dir(Object_Dir::Left),
	m_WallCol(false),
	m_Coin(100000),
	m_DustCount(0.f)
{
	SetStatus("Player");
}

CPlayer::CPlayer(const CPlayer& obj) :
	CGameObject(obj)
{

	m_Body = (CRigidBodyComponent*)FindSceneComponent("Body");
	m_Collider2DHorizon = (CColliderBox2D*)FindSceneComponent("Collider2DHorizon");
	m_Collider2DVertical = (CColliderBox2D*)FindSceneComponent("Collider2DVertical");
	m_Sprite = (CSpriteComponent*)FindSceneComponent("Sprite");
	m_Arm = (CSpringArm2D*)FindSceneComponent("Arm");
	m_Camera = (CCamera*)FindSceneComponent("Camera");

	m_OneAttack = obj.m_OneAttack;
	m_WeaponArm = obj.m_WeaponArm->Clone();
	m_Weapon = obj.m_Weapon->Clone();
	m_OneAttack = obj.m_OneAttack;
	//임시 삭제용
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
	m_Collider2DHorizon = CreateSceneComponent<CColliderBox2D>("Collider2DHorizon");
	m_Collider2DVertical = CreateSceneComponent<CColliderBox2D>("Collider2DVertical");
	m_Sprite = CreateSceneComponent<CSpriteComponent>("Sprite");
	m_Arm = CreateSceneComponent<CSpringArm2D>("Arm");
	m_Camera = CreateSceneComponent<CCamera>("Camera");

	m_WidgetComponent = CreateSceneComponent<CWidgetComponent>("PlayerWidgetComponent");
	m_WidgetComponent->SetWorldPos(0.f, 0.f, 0.f);
	m_PlayerWidget = m_WidgetComponent->CreateWidget<CPlayerWorldWidget>("PlayerWidget");
	m_WidgetComponent->SetRelativePos(-90.f, -30.f, 0.f);

	SetRootComponent(m_Sprite);
	m_Sprite->AddChild(m_WidgetComponent);
	m_Sprite->AddChild(m_Collider2D);
	m_Sprite->AddChild(m_Collider2DHorizon);
	m_Sprite->AddChild(m_Collider2DVertical);
	m_Sprite->AddChild(m_Body);
	m_Sprite->AddChild(m_Arm);
	m_Arm->AddChild(m_Camera);

	m_Sprite->SetRelativeScale(15.f, 20.f, 1.f);
	//m_Sprite->SetRelativeRotationZ(30.f);
	m_Sprite->SetPivot(0.5f, 0.5f, 0.f);

	m_Camera->SetCameraZoom(4.f);

	m_Collider2D->SetCollisionProfile("Player");
	m_Collider2DHorizon->SetCollisionProfile("TileCheckCollsion");
	m_Collider2DVertical->SetCollisionProfile("TileCheckCollsion");

	m_Collider2D->AddCollisionCallbackFunction<CPlayer>(Collision_State::Begin, this,
		&CPlayer::CollisionBegin);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CPlayer>(Collision_State::Begin, this,
		&CPlayer::CollisionHorizonBegin);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CPlayer>(Collision_State::Middle, this,
		&CPlayer::CollisionHorizonMiddle);
	m_Collider2DHorizon->AddCollisionCallbackFunction<CPlayer>(Collision_State::End, this,
		&CPlayer::CollisionHorizonEnd);

	m_Collider2DVertical->AddCollisionCallbackFunction<CPlayer>(Collision_State::Begin, this,
		&CPlayer::CollisionVerticalBegin);
	m_Collider2DVertical->AddCollisionCallbackFunction<CPlayer>(Collision_State::Middle, this,
		&CPlayer::CollisionVerticalMiddle);
	m_Collider2DVertical->AddCollisionCallbackFunction<CPlayer>(Collision_State::End, this, 
		&CPlayer::CollisionVerticalEnd);
	m_Collider2D->SetExtent(6.f, 10.f);
	m_Collider2DHorizon->SetExtent(6.f, 0.3f);
	m_Collider2DVertical->SetExtent(0.3f, 10.f);

	m_Arm->SetOffset(-640.f, -360.f, 0.f);
	m_Arm->SetInheritPosZ(false);


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
	CInput::GetInst()->AddKeyCallback<CPlayer>("InteractionInputKey", KT_Up, this, &CPlayer::InputInteractionInputKey);
	CInput::GetInst()->AddKeyCallback<CPlayer>("ShopUI", KT_Up, this, &CPlayer::ShopUIOnOff);
	CInput::GetInst()->AddKeyCallback<CPlayer>("StatusUI", KT_Up, this, &CPlayer::StatusUIOnOff);
	//마우스회전용
	
	m_WeaponArm = m_pScene->SpawnObject<CWeaponArm>("basicWeaponArm");
	m_WeaponArm->SetRelativePos(20.f,0.f,0.f);
	PushObjectChild(m_WeaponArm);
	
	//m_Weapon = m_pScene->SpawnObject<CShortSword>("basicWeapon");
	//m_Weapon = m_pScene->SpawnObject<CRevolver>("Revolver");
	//m_Weapon = m_pScene->SpawnObject<CMetalBoomerang>("MetalBoomerang");
	//m_Weapon->SetRelativePos(10.f, 0.f, 0.f); 
	


	m_BodyFSM.CreateState("Idle", this, &CPlayer::BodyIdleStay, &CPlayer::BodyIdleStart);
	m_BodyFSM.CreateState("Move", this, &CPlayer::BodyMoveStay, &CPlayer::BodyMoveStart);
	m_BodyFSM.CreateState("Jump", this, &CPlayer::BodyJumpStay, &CPlayer::BodyJumpStart);
	m_BodyFSM.ChangeState("Idle");
	SetGravity(true);
	return true;
}

void CPlayer::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
	m_WallCol = false;
	m_StageMove = false;
	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Vector3 Pos = m_WeaponArm->GetWorldPos();
	Vector2 Pos2 = Vector2(Pos.x, Pos.y);
	Vector3 Posss = GetWorldPos();
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
	if (m_Weapon)
	{

		if (m_Weapon->GetReloadPercent() > 0.f)
		{
			m_PlayerWidget->SetPercentBar(m_Weapon->GetReloadPercent());
		}
		if (m_Weapon->IsReloadEffect())
		{
			m_Weapon->SetReloadEffect(false);
			m_PlayerWidget->EffectStart();

		}
	}
	

	if(m_Body->IsDashEffect())
	{
		CPlayerDash* obj = m_pScene->SpawnObject<CPlayerDash>("PlayerDash");
		obj->SetWorldPos(GetWorldPos());
		obj->SetDir(m_Dir);
		m_Body->SetDashEffect(false);
	}
	if (m_State == ePlayerState::Move)
	{
		m_DustCount += DeltaTime;
	}
	else
	{
		m_DustCount = 0.f;
	}
	CMaterial* Material = m_Sprite->GetMaterial(0);
	if (m_Status.GetGracePeriod())
	{
		Material->SetBaseColor(1.f, 1.f, 1.f, 0.8f);
	}
	else
	{
		Material->SetBaseColor(1.f, 1.f, 1.f, 1.f);
	}
	AddRelativePos(m_Body->GetMove());       
}

void CPlayer::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
	m_Status.Update(DeltaTime);
	m_BodyFSM.Update();
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

void CPlayer::PrevRender(float DeltaTime)
{
	CGameObject::PrevRender(DeltaTime);
	CUIManager::GetInst()->GetMiniMapUI()->PushMiniMapInfoObject(Vector2(GetWorldPos().x, GetWorldPos().y), Vector2(4.f,4.f), Vector4(0.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.f), Vector4(1.f, 1.f, 1.f, 1.f), 1.f);
}

void CPlayer::Render(float DeltaTime)
{
	CGameObject::Render(DeltaTime);
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Animation2DNotify(const std::string& Name)
{
	
}

void CPlayer::SetGravity(bool bGravity)
{
	m_Body->SetGravity(bGravity);
}

void CPlayer::SetStatus(const std::string& Name)
{
	CBasicStatus* Status = CObjectStatusManager::GetInst()->FindStatus(Name);
	if (Status)
	{
		m_Status.SetHP(Status->GetHP());
		m_Status.SetHPMax(Status->GetHPMax());
		m_Status.SetDash(Status->GetDash());
		m_Status.SetDashMax(Status->GetDashMax());
		m_Status.SetAttackSpeed(Status->GetAttackSpeed());
		m_Status.SetReloadSpeed(Status->GetReloadSpeed());
		m_Status.SetMoveSpeed(Status->GetMoveSpeed());
		m_Status.SetDamage(Status->GetDamage());
		m_Status.SetDamageMax(Status->GetDamageMax());
		m_Status.SetArmor(Status->GetArmor());
		m_Status.SetCritical(Status->GetCritical());
		m_Status.SetEvasion(Status->GetEvasion());
		m_Status.SetMagazine(Status->GetMagazine());
		m_Status.SetMagazineMax(Status->GetMagazineMax());
		m_Status.SetPrice(Status->GetPrice());
	}
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
				m_Camera->AddCameraShake(1.f, 1.f, 0.3f);
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
	if (m_Weapon)
	{
		if (m_Weapon->GetReloadPercent() > 0.f)
		{
			return;
		}
	}
	CUIManager::GetInst()->GetPlayerUI()->WeaponChange();
}
void CPlayer::InputInteractionInputKey(float DeltaTime)
{
	CPlayerInteractionCollision* CollisionObj = m_pScene->SpawnObject<CPlayerInteractionCollision>("PlayerInteractionCollision");
	CollisionObj->SetWorldPos(GetWorldPos());


}
void CPlayer::ShopUIOnOff(float DeltaTime)
{
	if (CUIManager::GetInst()->GetShopUI()->IsEnable())
	{
		CUIManager::GetInst()->GetShopUI()->Enable(false);
		CGlobalValue::MainMouse->SetState(Mouse_State::World);
	}
	else
	{
		CUIManager::GetInst()->GetShopUI()->Enable(true);
		CGlobalValue::MainMouse->SetState(Mouse_State::UI);
	}
}
void CPlayer::StatusUIOnOff(float DeltaTime)
{
	if (CUIManager::GetInst()->GetStatusUI()->IsEnable())
	{
		CUIManager::GetInst()->GetStatusUI()->Enable(false);
		CGlobalValue::MainMouse->SetState(Mouse_State::World);
	}
	else
	{
		CUIManager::GetInst()->GetStatusUI()->Enable(true);
		CGlobalValue::MainMouse->SetState(Mouse_State::UI);
	}
}
int CPlayer::GetDamage()
{
	if (m_Weapon)
	{
		return m_Weapon->GetDamage()+ m_Status.GetDamage();
	}
	return 0;
}
int CPlayer::GetDamageMax()
{
	if (m_Weapon)
	{
		return m_Weapon->GetDamageMax() + m_Status.GetDamageMax();
	}
	return 0;
}
int CPlayer::GetArmor()
{
	return m_Status.GetArmor();
}
int CPlayer::GetCritical()
{
	return m_Status.GetCritical();
}
float CPlayer::GetMoveSpeed()
{
	return m_Status.GetMoveSpeed();
}
float CPlayer::GetAttackSpeed()
{
	if (m_Weapon)
	{
		return m_Weapon->GetAttackSpeed();
	}
	return 0.f;
}
float CPlayer::GetReloadSpeed()
{
	if (m_Weapon)
	{
		return m_Weapon->GetReloadSpeed();
	}
	return 0.f;
}

int CPlayer::GetAttackDamage(bool Critical)
{
	int Damage = m_Status.GetDamage();
	int DamageMax = m_Status.GetDamageMax();
	if (m_Weapon)
	{
		Damage += m_Weapon->GetDamage();

		DamageMax += m_Weapon->GetDamageMax();
	}
	int CriticalCheck = GetRandom(0, 100);
	if (m_Status.GetCritical() < CriticalCheck)
	{
		return GetRandom(Damage, DamageMax);
	}
	else
	{
		return GetRandom(Damage, DamageMax);
	}
}
void CPlayer::EnemyHit(int Damage)
{
	if (!m_Status.GetGracePeriod())
	{
		m_Status.SubHP(Damage);
		CUIManager::GetInst()->GetPlayerUI()->Hit();
	}
}
void CPlayer::AnimationFrameEnd(const std::string& Name)
{
}

void CPlayer::CollisionBegin(const HitResult& result, CCollider* Collider)
{
}

void CPlayer::CollisionHorizonBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		if (m_StageMove)
			return;
		Vector3 Velocity = GetVelocity();
		if (Velocity.y > 0.f)
			return;
		if (m_Body->IsDash())
		{
			return;
		}
	}
	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		if (m_StageMove)
			return;
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		if (m_Body->IsDash())
		{
			Vector3 Velocity = GetVelocity();
			PlayerPos.x -= Velocity.x;
			PlayerPos.y -= Velocity.y;
		}
		float Angle = PlayerPos.GetAngle(ColPos);
		m_Body->StopDash();
		ColDirHorizon(Angle, result.DestCollider);
	}

	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Door)
	{

		SetWorldPos(GetWorldPos() - GetVelocity());
	}
}

void CPlayer::CollisionHorizonMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		if (m_StageMove)
			return;
		Vector3 Velocity = GetVelocity();
		if (Velocity.y > 0.f)
			return;
		if (m_Body->IsDash())
		{
			return;
		}
	}
	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		if (m_StageMove)
			return;
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		if (m_Body->IsDash())
		{
			Vector3 Velocity = GetVelocity();
			PlayerPos.x -= Velocity.x;
			PlayerPos.y -= Velocity.y;
		}
		float Angle = PlayerPos.GetAngle(ColPos);
		m_Body->StopDash();
		ColDirHorizon(Angle, result.DestCollider);
	}

	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Door)
	{

		SetWorldPos(GetWorldPos() - GetVelocity());
	}
}

void CPlayer::CollisionHorizonEnd(const HitResult& result, CCollider* Collider)
{

}

void CPlayer::CollisionVerticalBegin(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		if (m_StageMove)
			return;
		Vector3 Velocity = GetVelocity();
		if (Velocity.y > 0.f)
			return;
		if (m_Body->IsDash())
		{
			return;
		}
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		float Angle = PlayerPos.GetAngle(ColPos);
		ColTilePassDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		if (m_StageMove)
			return;
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		if (m_Body->IsDash())
		{
			Vector3 Velocity = GetVelocity();
			PlayerPos.x -= Velocity.x;
			PlayerPos.y -= Velocity.y;
		}
		float Angle = PlayerPos.GetAngle(ColPos);
		m_Body->StopDash();
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Door)
	{
		
		SetWorldPos(GetWorldPos() - GetVelocity());
	}
}

void CPlayer::CollisionVerticalMiddle(const HitResult& result, CCollider* Collider)
{
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_pass)
	{
		if (m_StageMove)
			return;
		Vector3 Velocity = GetVelocity();
		if (Velocity.y > 0.f)
			return;
		if (m_Body->IsDash())
		{
			return;
		}
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		if (m_Body->IsDash())
		{
			Vector3 Velocity = GetVelocity();
			PlayerPos.x -= Velocity.x;
			PlayerPos.y -= Velocity.y;
		}
		float Angle = PlayerPos.GetAngle(ColPos);
		ColTilePassDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}
	if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Tile_Nopass)
	{
		if (m_StageMove)
			return;
		Vector2 PlayerPos = Vector2(GetWorldPos().x, GetWorldPos().y);
		Vector2 ColPos = Vector2(result.DestCollider->GetWorldPos().x, result.DestCollider->GetWorldPos().y);
		if (m_Body->IsDash())
		{
			Vector3 Velocity = GetVelocity();
			PlayerPos.x -= Velocity.x;
			PlayerPos.y -= Velocity.y;
		}
		float Angle = PlayerPos.GetAngle(ColPos);
		m_Body->StopDash();
		ColDirVertical(Angle, result.DestCollider);
		m_WallCol = true;
	}

	else if (result.DestCollider->GetProfile()->Channel == Collision_Channel::Door)
	{

		SetWorldPos(GetWorldPos() - GetVelocity());
	}
}

void CPlayer::CollisionVerticalEnd(const HitResult& result, CCollider* Collider)
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


void CPlayer::ColDirHorizon(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2DHorizon->GetRelativeScale() / 2.f;

	//왼쪽
	if (90.f <= Angle && Angle < 270.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x += x;
		PlayerPos.x = XMove.x;
		SetWorldPos(PlayerPos);

	}
	//오른쪽방향
	else if (270.f <= Angle || Angle < 90.f)
	{
		m_Body->StopForceX();
		float x = (PlayerScale.x + ColScale.x);
		Vector3 XMove = ColPos;
		XMove.x -= x;
		PlayerPos.x = XMove.x;
		SetWorldPos(PlayerPos);

	}

}

void CPlayer::ColDirVertical(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2DVertical->GetRelativeScale() / 2.f;

	//왼쪽

	//아래
	if (180.f <= Angle && Angle < 360.f)
	{
		m_Body->StopForceY();
		m_Body->StopForceX();
		m_Body->SetGravity(false);
		m_Body->SetJump(false);
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y += y;
		PlayerPos.y = XMove.y;
	}
	//위
	else if (0.f <= Angle || Angle < 180.f || 360.f<=Angle)
	{
		m_Body->StopForceY();
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y -= y;
		PlayerPos.y = XMove.y;
	}

	SetWorldPos(PlayerPos);
}

void CPlayer::ColTilePassDirVertical(float Angle, CCollider* Col)
{
	Vector3 ColPos = Col->GetWorldPos();
	Vector3 ColScale = Col->GetRelativeScale() / 2.f;
	Vector3 PlayerPos = GetWorldPos();
	Vector3 PlayerScale = m_Collider2DVertical->GetRelativeScale() / 2.f;

	//왼쪽

	//아래
	if (180.f <= Angle && Angle < 360.f)
	{
		m_Body->StopForceY();
		m_Body->StopForceX();
		m_Body->SetGravity(false);
		m_Body->SetJump(false);
		float y = (PlayerScale.y + ColScale.y);
		Vector3 XMove = ColPos;
		XMove.y += y;
		PlayerPos.y = XMove.y;
	}
	SetWorldPos(PlayerPos);

}



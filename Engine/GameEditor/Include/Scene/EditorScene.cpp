
#include "pch.h"
#include "EditorScene.h"
#include "Input.h"
#include "Scene/Scene.h"
#include "Scene/CameraManager.h"
#include "Component/Camera.h"
#include "../TileMapWindow.h"
#include "IMGUIManager.h"
#include "Component/TileMapComponent.h"
#include <Scene/Scene.h>
#include <Resource/ResourceManager.h>
#include "Scene/SceneResource.h"
#include "Resource/ResourceManager.h"
#include "../GlobalValue.h"
#include "../ObjectWindow.h"
#include "../PrefabWindow.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "../TileMapToolWindow.h"
#include <Component/Camera.h>
#include <Scene/CameraManager.h>
CEditorScene::CEditorScene() :
	m_CloneObjectCount(0)
{
}

CEditorScene::~CEditorScene()
{
}

bool CEditorScene::Init()
{
	CreateAnimationSequence2D();
    CInput::GetInst()->CreateKey("MoveUp", 'W');
    CInput::GetInst()->CreateKey("MoveDown", 'S');
    CInput::GetInst()->CreateKey("MoveLeft", 'A');
    CInput::GetInst()->CreateKey("MoveRight", 'D');
    CInput::GetInst()->CreateKey("MouseLButton", VK_LBUTTON);
	CInput::GetInst()->CreateKey("MouseRButton", VK_RBUTTON);

    CInput::GetInst()->AddKeyCallback<CEditorScene>("MoveUp", KT_Push, this, &CEditorScene::MoveUp);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("MoveDown", KT_Push, this, &CEditorScene::MoveDown);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("MoveLeft", KT_Push, this, &CEditorScene::MoveLeft);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("MoveRight", KT_Push, this, &CEditorScene::MoveRight);
    CInput::GetInst()->AddKeyCallback<CEditorScene>("MouseLButton", KT_Up, this, &CEditorScene::MouseLButton);
	CInput::GetInst()->AddKeyCallback<CEditorScene>("MouseRButton", KT_Push, this, &CEditorScene::MouseRButton);

    m_TileMapToolWindow = (CTileMapToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("TileMapToolWindow");
	m_ObjectWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	m_PrefabWindow = (CPrefabWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("PrefabWindow");
	m_TileMapToolWindow->SetScene(m_pScene);
    return true;
}

void CEditorScene::Update(float DeltaTime)
{
    CSceneMode::Update(DeltaTime);
}

void CEditorScene::PostUpdate(float DeltaTime)
{
    CSceneMode::PostUpdate(DeltaTime);
}

void CEditorScene::MoveUp(float DeltaTime)
{
    CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

    Camera->AddRelativePos(Camera->GetAxis(AXIS_Y) * 300.f * DeltaTime);
}

void CEditorScene::MoveDown(float DeltaTime)
{
    CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

    Camera->AddRelativePos(Camera->GetAxis(AXIS_Y) * -300.f * DeltaTime);
}

void CEditorScene::MoveLeft(float DeltaTime)
{
    CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

    Camera->AddRelativePos(Camera->GetAxis(AXIS_X) * -300.f * DeltaTime);
}

void CEditorScene::MoveRight(float DeltaTime)
{
    CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();

    Camera->AddRelativePos(Camera->GetAxis(AXIS_X) * 300.f * DeltaTime);
}

void CEditorScene::MouseLButton(float DeltaTime)
{
	
	switch (CGlobalValue::MouseState)
	{
	case Mouse_State::Normal:
	{
		break;
	}
	case Mouse_State::Tile:
	{
		if (!m_TileMapToolWindow->IsTileMap())
			return;

		Tile_Modify_Type    ModifyType = m_TileMapToolWindow->GetTileModifyType();
		switch (ModifyType)
		{
		case Tile_Modify_Type::Type:
			EditTileType();
			break;
		case Tile_Modify_Type::Image:
			EditTileImage();
			break;
		}
		break;
	}

	case Mouse_State::World:
	{
		AddObjectMap();
		break;
	}
	}
}

void CEditorScene::MouseRButton(float DeltaTime)
{

	switch (CGlobalValue::MouseState)
	{
	case Mouse_State::Normal:
	{
		break;
	}
	case Mouse_State::Tile:
	{
		
	}

	case Mouse_State::World:
	{
		DeleteObjectMap();
		break;
	}
	}
}

void CEditorScene::EditTileType()
{
    Tile_Type   Type = m_TileMapToolWindow->GetTileType();

    Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();

    CTileMapComponent* TileMap = m_TileMapToolWindow->GetTileMap();

    // 마우스 위치를 이용해서 현재 마우스가 위치한 곳의 타일을 얻어온다.
    CTile* Tile = TileMap->GetTile(MousePos);

    if (Tile)
        Tile->SetTileType(Type);

}

void CEditorScene::EditTileImage()
{
	Vector2 Frame= m_TileMapToolWindow->GetImageFrame();

	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	CCamera* Camera = m_pScene->GetCameraManager()->GetCurrentCamera();
	CTileMapComponent* TileMap = m_TileMapToolWindow->GetTileMap();

	if (Frame.x == -1 || Frame.y == -1)
	{
		TileMap->TileRemoveRender(Vector3(MousePos.x, MousePos.y, 0.f));

		CTile* Tile = TileMap->GetTile(MousePos);

		if (Tile)
			Tile->SetTileType(Tile_Type::Wall);
	}

	else
	{
		TileMap->SetTileFrame(MousePos, Frame.x, Frame.y);
	}
}

void CEditorScene::AddObjectMap()
{
	CGameObject* Obj=m_PrefabWindow->GetSelectObject();
	if (!Obj)
		return;

	CScene* Scene = CSceneManager::GetInst()->GetScene();
	std::string str = Obj->GetName();
	str += std::to_string(m_CloneObjectCount);
	CGameObject* Obj2 = Scene->SpawnObject<CGameObject>(str);
	CSceneComponent* Component = Obj->GetRootComponent()->Clone();
	Obj2->SetRootCloneComponent(Component);
	

	Vector2 MousePos = CInput::GetInst()->GetMouse2DWorldPos();
	Obj2->SetWorldPos(MousePos.x, MousePos.y, 0.f);
	Obj2->SetWorldScale(100.f, 100.f, 0.f);
	m_CloneObjectCount++;
	m_ObjectWindow->AddObject(Obj2);

}

void CEditorScene::DeleteObjectMap()
{
	m_ObjectWindow->DeleteColliderMouseObject();
}


void CEditorScene::CreateAnimationSequence2D()
{
	/*
	Player
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("PlayerIdle",
		"PlayerIdle", TEXT("Characters/Basic/player_idle.png"));

	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("PlayerIdle",
			Vector2(i * 15.f, 0.f), Vector2((i + 1) * 15.f, 20.f));
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerRun");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("PlayerRun",
		"PlayerRun", TEXT("Characters/Basic/player_run.png"));

	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("PlayerRun",
			Vector2(i * 17.f, 0), Vector2((i + 1) * 17.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerJump");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("PlayerJump",
		"PlayerJump", TEXT("Characters/Basic/player_jump.png"));

	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("PlayerJump",
			Vector2(i * 17.f, 0), Vector2((i + 1) * 17.f, 21.f));
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerDie");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("PlayerDie",
		"PlayerDie", TEXT("Characters/Basic/player_die.png"));

	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("PlayerDie",
			Vector2(i * 23.f, 0), Vector2((i + 1) * 23.f, 14.f));
	}

	/*ShortSwordEfect*/
	m_pScene->GetResource()->CreateAnimationSequence2D("ShortSwordEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("ShortSwordEffect",
		"ShortSwordEffect", TEXT("Weapon/Melee/SwingFX.png"));

	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("ShortSwordEffect",
			Vector2(i * 28.f, 0), Vector2((i + 1) * 28.f, 40));
	}


	/*
	Revolver
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("RevolverEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("RevolverEffect",
		"RevolverEffect", TEXT("Weapon/Range/effect/ShootEffect.png"));

	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("RevolverEffect",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 15.f));
	}

	/*
	MetalBoomerang
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("MetalBoomerangEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("MetalBoomerangEffect",
		"MetalBoomerangEffect", TEXT("Weapon/Range/effect/GatlingGunEffect.png"));

	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("MetalBoomerangEffect",
			Vector2(i * 22.f, 0), Vector2((i + 1) * 22.f, 22.f));
	}

	/*
	ObjectDieEffect
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("ObjectDieEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("ObjectDieEffect",
		"ObjectDieEffect", TEXT("Effect/Die/Die.png"));

	for (int i = 0; i < 11; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("ObjectDieEffect",
			Vector2(i * 50.f, 0), Vector2((i + 1) * 50.f, 50.f));
	}


	/*
	Door
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorOpen");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("DoorOpen",
		"Door", TEXT("Effect/object/door/door.png"));

	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("DoorOpen",
			Vector2(i * 66.f, 0), Vector2((i + 1) * 66.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("DoorIdle",
		"Door", TEXT("Effect/object/door/door.png"));

	for (int i = 7; i < 17; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("DoorIdle",
			Vector2(i * 66.f, 0), Vector2((i + 1) * 66.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorClose");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("DoorClose",
		"Door", TEXT("Effect/object/door/door.png"));
	for (int i = 17; i < 23; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("DoorClose",
			Vector2(i * 66.f, 0), Vector2((i + 1) * 66.f, 20.f));
	}

	//가로 23


	/*
	Enemy
	*/
	/*
	Skel Small
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyIdle",
		"SmallEnemyIdle", TEXT("Enemy/SKel/Small/idle.png"));

	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyIdle",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 19.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyIdleShot");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyIdleShot",
		"SmallEnemyIdleShot", TEXT("Enemy/SKel/Small/idle_shot.png"));

	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyIdleShot",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 19.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyMove");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyMove",
		"SmallEnemyMove", TEXT("Enemy/SKel/Small/move.png"));

	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyMove",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyMoveShot");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyMoveShot",
		"SmallEnemyMoveShot", TEXT("Enemy/SKel/Small/move_shot.png"));

	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyMoveShot",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyDaggerAttack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyDaggerAttack",
		"SmallEnemyDaggerAttack", TEXT("Enemy/SKel/Small/dagger.png"));
	for (int i = 0; i < 12; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyDaggerAttack",
			Vector2(i * 26.f, 0), Vector2((i + 1) * 26.f, 30.f));
	}
	m_pScene->GetResource()->AddAnimationSequence2DNotify("SmallEnemyDaggerAttack", "Attack", 7);

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyDaggerIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyDaggerIdle",
		"SmallEnemyDaggerIdle", TEXT("Enemy/SKel/Small/dagger.png"));
	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyDaggerIdle",
			Vector2(i * 26.f, 0), Vector2((i + 1) * 26.f, 30.f));
	}

	/*

	Boss. Belial


	*/
	/*Head*/
	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHead_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BelialHead_Idle",
		"BelialHead_Idle", TEXT("boss/Belial/Head/idle.png"));
	for (int i = 0; i < 10; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BelialHead_Idle",
			Vector2(i * 70.f, 0.f), Vector2((i + 1) * 70.f, 96.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHead_Attack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BelialHead_Attack",
		"BelialHead_Attack", TEXT("boss/Belial/Head/attack.png"));
	for (int i = 0; i < 10; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BelialHead_Attack",
			Vector2(i * 70.f, 0), Vector2((i + 1) * 70.f, 128.f));
	}


	/*Hand*/
	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHand_Idle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BelialHand_Idle",
		"BelialHand_Idle", TEXT("boss/Belial/Hand/idle.png"));
	for (int i = 0; i < 10; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BelialHand_Idle",
			Vector2(i * 57.f, 0.f), Vector2((i + 1) * 57.f, 67.f));
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHand_Attack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BelialHand_Attack",
		"BelialHand_Attack", TEXT("boss/Belial/Hand/attack.png"));
	for (int i = 0; i < 18; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BelialHand_Attack",
			Vector2(i * 65.f, 0), Vector2((i + 1) * 65.f, 71.f));
	}
	//Notify설정할부분
	//m_pScene->GetResource()->AddAnimationSequence2DNotify("PlayerAttack", "Attack", 8);

	/*Back*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_Circle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_Circle",
		"Belial_Circle", TEXT("boss/Belial/Back/circle.png"));
	for (int i = 0; i < 10; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_Circle",
			Vector2(i * 50.f, 0.f), Vector2((i + 1) * 50.f, 50.f));
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_CircleParticle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_CircleParticle",
		"Belial_CircleParticle", TEXT("boss/Belial/Back/particle.png"));
	for (int i = 0; i < 18; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_CircleParticle",
			Vector2(i * 65.f, 0), Vector2((i + 1) * 65.f, 71.f));
	}

	/*Laser*/

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_LaserBody");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_LaserBody",
		"Belial_LaserBody", TEXT("boss/Belial/Laser/body.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_LaserBody",
			Vector2(i * 32.f, 0.f), Vector2((i + 1) * 32.f, 50.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_LaserHand");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_LaserHand",
		"Belial_LaserHand", TEXT("boss/Belial/Laser/hand.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_LaserHand",
			Vector2(i * 27.f, 0), Vector2((i + 1) * 27.f, 44.f));
	}

	/*Weapon*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_WeaponCharge");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_WeaponCharge",
		"Belial_WeaponCharge", TEXT("boss/Belial/Sword/charge.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_WeaponCharge",
			Vector2(0.f, i * 21.f), Vector2(65.f, (i + 1) * 21.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_WeaponHit");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_WeaponHit",
		"Belial_WeaponHit", TEXT("boss/Belial/Sword/hit.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_WeaponHit",
			Vector2(i * 22.f, 0), Vector2((i + 1) * 22.f, 51.f));
	}





	/*
	UI
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("LifeWave");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("LifeWave",
		"LifeWave", TEXT("UI/LifeWave.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("LifeWave",
			Vector2(i * 4.f, 0), Vector2((i + 1) * 4.f, 10.f));
	}


}

void CEditorScene::CreateParticle()
{
	CMaterial* SnowMaterial = m_pScene->GetResource()->FindMaterial("Snow");

	m_pScene->GetResource()->CreateParticle("TestParticle");
	m_pScene->GetResource()->SetParticleMaterial("TestParticle", SnowMaterial);
	m_pScene->GetResource()->SetParticleMaxParticleCount("TestParticle", 1000);
	m_pScene->GetResource()->SetParticleStartColor("TestParticle", 0.68627f, 0.8745f, 0.89411f, 0.8f);
	m_pScene->GetResource()->SetParticleEndColor("TestParticle", 0.68627f, 0.8745f, 0.89411f, 0.f);
	m_pScene->GetResource()->SetParticleStartScale("TestParticle", 100.f, 100.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("TestParticle", 20.f, 20.f, 1.f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("TestParticle", 2.f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("TestParticle", 4.f);
	m_pScene->GetResource()->SetParticleRange("TestParticle", 100.f, 0.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("TestParticle", 100.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("TestParticle", 200.f);
	m_pScene->GetResource()->SetParticleMoveEnable("TestParticle", true);
	m_pScene->GetResource()->SetParticle2D("TestParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("TestParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("TestParticle", 0.f, 0.f, 90.f);

	CMaterial* FlameMaterial = m_pScene->GetResource()->FindMaterial("Flame");

	m_pScene->GetResource()->CreateParticle("FlameParticle");
	m_pScene->GetResource()->SetParticleMaterial("FlameParticle", FlameMaterial);
	m_pScene->GetResource()->SetParticleMaxParticleCount("FlameParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("FlameParticle", 0.94901f, 0.490019f, 0.04705f, 0.8f);
	m_pScene->GetResource()->SetParticleEndColor("FlameParticle", 0.94901f, 0.490019f, 0.04705f, 0.f);
	m_pScene->GetResource()->SetParticleStartScale("FlameParticle", 20.f, 20.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("FlameParticle", 10.f, 10.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 10.5f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 10.8f);
	m_pScene->GetResource()->SetParticleRange("FlameParticle", 0.f, 0.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("FlameParticle", 600.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("FlameParticle", 800.f);
	m_pScene->GetResource()->SetParticleMoveEnable("FlameParticle", true);
	m_pScene->GetResource()->SetParticle2D("FlameParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("FlameParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("FlameParticle", 0.f, 0.f, 90.f);


	CMaterial* StageMapMaterial = m_pScene->GetResource()->FindMaterial("StageMapMaterial");

	m_pScene->GetResource()->CreateParticle("StageMapParticle");
	m_pScene->GetResource()->SetParticleUpdateShader("StageMapParticle", "ParticleRandomScaleUpdateShader");
	m_pScene->GetResource()->SetParticleMaterial("StageMapParticle", StageMapMaterial);
	m_pScene->GetResource()->SetParticleMaxParticleCount("StageMapParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("StageMapParticle", 0.94901f, 0.490019f, 0.04705f, 0.8f);
	m_pScene->GetResource()->SetParticleEndColor("StageMapParticle", 0.94901f, 0.490019f, 0.04705f, 0.f);
	m_pScene->GetResource()->SetParticleStartScale("StageMapParticle", 20.f, 20.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("StageMapParticle", 10.f, 10.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("StageMapParticle", 2.f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("StageMapParticle", 2.f);
	m_pScene->GetResource()->SetParticleRange("StageMapParticle", 5000.f, 5000.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("StageMapParticle", 50.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("StageMapParticle", 50.f);
	m_pScene->GetResource()->SetParticleMoveEnable("StageMapParticle", true);
	m_pScene->GetResource()->SetParticle2D("StageMapParticle", true);
	//m_pScene->GetResource()->SetParticleMoveDir("StageMapParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("StageMapParticle", 0.f, 0.f, 360.f);

	CMaterial* StageMapMateria1l = m_pScene->GetResource()->FindMaterial("DoorParticle");

	m_pScene->GetResource()->CreateParticle("DoorParticle");
	m_pScene->GetResource()->SetParticleUpdateShader("DoorParticle", "ParticleDirUpdateShader");
	m_pScene->GetResource()->SetParticleMaterial("DoorParticle", StageMapMateria1l);
	m_pScene->GetResource()->SetParticleMaxParticleCount("DoorParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("DoorParticle", 0.94901f, 0.490019f, 0.04705f, 0.8f);
	m_pScene->GetResource()->SetParticleEndColor("DoorParticle", 0.94901f, 0.490019f, 0.04705f, 0.f);
	m_pScene->GetResource()->SetParticleStartScale("DoorParticle", 40.f, 40.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("DoorParticle", 40.f, 40.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("DoorParticle", 10.5f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("DoorParticle", 10.8f);
	m_pScene->GetResource()->SetParticleRange("DoorParticle", 200.f, 200.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("DoorParticle", 100.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("DoorParticle", 100.f);
	m_pScene->GetResource()->SetParticleMoveEnable("DoorParticle", true);
	m_pScene->GetResource()->SetParticle2D("DoorParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("DoorParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("DoorParticle", 0.f, 0.f, 90.f);
}

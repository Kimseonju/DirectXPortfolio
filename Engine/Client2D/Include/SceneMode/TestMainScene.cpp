
#include "TestMainScene.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "../UI/TitleWidget.h"
#include "Scene/Viewport.h"
#include "../Object/StartScene/BackGround.h"
#include "../Object/Cloud.h"
#include "../Object/StartScene/Bird.h"
#include "../Object/BackGround_Tree.h"
#include <Device.h>

#include "../Object/Player2D.h"
#include "../Object/Player.h"
#include "../Object/Teemo.h"
#include "../Object/PixelCollisionTest.h"
#include "../Object/TestParticle.h"
#include "Render/RenderManager.h"
#include "../UI/MainHUDWidget.h"
#include "Scene/Viewport.h"
#include "../Object/CollisionObject.h"
#include "../Object/SmallSkel.h"
#include "../GlobalValue.h"
#include "../Object/Stage1MapEffect.h"
#include "../Object/DoorEffect.h"
#include "../Object/ShortSword.h"

#include "../Stage/Stage.h"
#include "../UI/StageMap.h"
#include "../UI/PlayerUI.h"
#include "../UI/Inventory.h"
#include "../UI/ItemInfoWidget.h"
#include "../UI/AbilityWidget.h"
#include "../Object/Belial.h"
#include "../Object/TestTileMap.h"
#include "../Stage/Door.h"
#include "../UI/UIManager.h"
#include "../Object/BossDieParticle.h"
#include "../Stage/StageManager.h"
#include "../Object/ProgressBarObject.h"
#include "../Object/BasicTresure.h"
#include "../Object/TorchLight.h"
#include "../Object/ShopNPC.h"
#include "../ObjectStatusManager.h"
CTestMainScene::CTestMainScene() :
	m_Minrooms(-1),
	m_Maxrooms(-1),
	m_Endrooms(-1)
{
}

CTestMainScene::~CTestMainScene()
{
	CUIManager::GetInst()->DestroyInst();
	CStageManager::GetInst()->DestroyInst();
	CObjectStatusManager::GetInst()->DestroyInst();
}

bool CTestMainScene::Init()
{
	CreateMaterial();
	CreateAnimationSequence2D();
	CreateParticle();
	CObjectStatusManager::GetInst()->LoadStatus("Player", TEXT("Player.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("Revolver", TEXT("Revolver.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("ShortSword", TEXT("ShortSword.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("MetalBoomerang", TEXT("MetalBoomerang.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("SmallSkelBow", TEXT("SmallSkelBow.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("SkelSmallDagger", TEXT("SkelSmallDagger.csv"));



	CObjectStatusManager::GetInst()->LoadStatus("SmallSkel_Sword", TEXT("SmallSkel_Sword.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("SmallSkel_Bow", TEXT("SmallSkel_Bow.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("Giant_Red", TEXT("Giant_Red.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("Ghost", TEXT("Ghost.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("Belial", TEXT("Belial.csv"));
	CObjectStatusManager::GetInst()->LoadStatus("Banshee", TEXT("Banshee.csv"));
	//CTestTileMap* TestTileMap = m_pScene->SpawnObject<CTestTileMap>("TestTileMap");

	//구름
	//CBackGround* BackGround = m_pScene->SpawnObject<CBackGround>("BackGround");
	//BackGround->AddTexture("Town_BGL", TEXT("Map/Town_BGL.png"));
	Resolution RS = CDevice::GetInst()->GetResolution();

	//CBackGround_Tree* BackGround_Tree = m_pScene->SpawnObject<CBackGround_Tree>("BackGround_Tree1");
	//BackGround_Tree->AddTexture("TownBG_Day", TEXT("Map/TownBG_Day.png"));
	//
	//BackGround_Tree = m_pScene->SpawnObject<CBackGround_Tree>("BackGround_Tree2");
	//BackGround_Tree->AddTexture("TownBG_Day", TEXT("Map/TownBG_Day.png"));
	//BackGround_Tree->SetRelativePos(RS.Width, 0.f, 0.f);

	CPlayer* pPlayer = m_pScene->SpawnObject<CPlayer>("Player");
	CGlobalValue::MainPlayer = pPlayer;
	//CRenderManager::GetInst()->SetWorldRenderState("WireFrame");
	CStageManager::GetInst()->SetScene(m_pScene);
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapL.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLD2.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLR.txt"));

	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLRD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLRU.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLRUD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLU.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapLUD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapR.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapRD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapRD2.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapRU.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapRUD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapU.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BasicMapUD.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("EndMapL.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("BossMap_LR.txt"));
	//CStageManager::GetInst()->AllLoadStage(TEXT("ShopMapLR.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("ShopMapLRT.txt"));
	//CStageManager::GetInst()->AllLoadStage(TEXT("StartMapR_.txt"));
	//CStageManager::GetInst()->AllLoadStage(TEXT("StartMapR_Enemy.txt"));
	//CStageManager::GetInst()->AllLoadStage(TEXT("StartMapR_EnemyT.txt"));
	CStageManager::GetInst()->AllLoadStage(TEXT("StartMapR_EnemyTT.txt"));
	//CStageManager::GetInst()->AllLoadStage(TEXT("BossMap_R_TestTTTT.txt"));
	
	CStageManager::GetInst()->Init();
	CStageManager::GetInst()->Start();

	CUIManager::GetInst()->Init(m_pScene);


	//CProgressBarObject* pEnemy = m_pScene->SpawnObject<CProgressBarObject>("TestEnemy");
	//pEnemy->SetWorldPos(0.f, 100.f, 0.f);

	CBasicTresure* Tresure = m_pScene->SpawnObject<CBasicTresure>("Tresure");
	CTorchLight* TorchLight = m_pScene->SpawnObject<CTorchLight>("TorchLight");
	//CShopNPC* ShopNPC = m_pScene->SpawnObject<CShopNPC>("ShopNPC");
	//벨리알테스트용
	//CBelial* pEnemy = m_pScene->SpawnObject<CBelial>("TestEnemy");
	//pEnemy->SetRelativePos(-300.f, 0.f, 0.f);

	//CCollisionObject* pCollisionObject = m_pScene->SpawnObject<CCollisionObject>("Collision1");
	
	//CTeemo* pTeemo = m_pScene->SpawnObject<CTeemo>("Teemo");
	//
	//pTeemo->SetRelativePos(500.f, 500.f, 0.f);
	
	//CPixelCollisionTest* pPixelCollisionTest = m_pScene->SpawnObject<CPixelCollisionTest>("PixelCollisionTest");
	CStage1MapEffect* Stage1MapEffect = m_pScene->SpawnObject<CStage1MapEffect>("Stage1MapEffect");
	Stage1MapEffect->SetWorldPos(400.f, 200.f,0.f);
	//CTestParticle* pParticle = m_pScene->SpawnObject<CTestParticle>("PixelCollisionTest");

	//CGameObject* BossDieParticle = m_pScene->SpawnObject<CBossDieParticle>("BossDieParticle");
	//BossDieParticle->SetWorldPos(200.f, 200.f,0.f);
	//CMainHUDWidget* Widget = m_pScene->GetViewport()->AddWindow<CMainHUDWidget>("MainHUD");
	//Widget->SetPlayer(pPlayer);

	//CStageMap* Widget1 = m_pScene->GetViewport()->AddWindow<CStageMap>("StageMap");
	//Widget1->SetStage(m_Stage);
	//CItemInfoWidget* Widget3 = m_pScene->GetViewport()->AddWindow<CItemInfoWidget>("ItemInfoWidget");
	//CAbilityWidget* Widget4 = m_pScene->GetViewport()->AddWindow<CAbilityWidget>("CAbilityWidget");
	//Widget4->SetPos(500.f, 300.f);
	//Widget1->SetStage(m_Stage);
	return true;
}

void CTestMainScene::Update(float DeltaTime)
{
	CStageManager::GetInst()->Update(DeltaTime);
}

void CTestMainScene::PostUpdate(float DeltaTime)
{
}

void CTestMainScene::CreateMaterial()
{
	m_pScene->GetResource()->CreateMaterial("PlayerChild");
	m_pScene->GetResource()->AddMaterialTexture("PlayerChild", "PlayerChild",
		TEXT("Teemo.jpg"));

	m_pScene->GetResource()->CreateMaterial("Snow");
	m_pScene->GetResource()->AddMaterialTexture("Snow", "Snow",
		TEXT("Particle/Bubbles50px.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Snow", true);
	//m_pScene->GetResource()->SetMaterialOpacity("DefaultMaterial", 0.3f);

	m_pScene->GetResource()->CreateMaterial("Flame");
	m_pScene->GetResource()->AddMaterialTexture("Flame", "Flame",
		TEXT("Particle/particle_00.png"));
	m_pScene->GetResource()->SetMaterialTransparency("Flame", true);


	m_pScene->GetResource()->CreateMaterial("StageMapMaterial");
	m_pScene->GetResource()->AddMaterialTexture("StageMapMaterial", "StageMapMaterial",
		TEXT("Map/StageMapEffect.png"));
	m_pScene->GetResource()->SetMaterialTransparency("StageMapMaterial", true);


	m_pScene->GetResource()->CreateMaterial("DoorParticle");
	m_pScene->GetResource()->AddMaterialTexture("DoorParticle", "DoorParticle",
		TEXT("Map/MapEffect.png"));
	m_pScene->GetResource()->SetMaterialTransparency("DoorParticle", true);
	

	m_pScene->GetResource()->CreateMaterial("BossDieParticle");
	m_pScene->GetResource()->AddMaterialTexture("BossDieParticle", "BossDieParticle",
		TEXT("Boss/Effect/Finish.png"));
	m_pScene->GetResource()->SetMaterialTransparency("BossDieParticle", true);



	m_pScene->GetResource()->CreateMaterial("BossBackParticle");
	m_pScene->GetResource()->AddMaterialTexture("BossBackParticle", "BossBackParticle",
		TEXT("boss/Belial/Back/particle.png"));
	m_pScene->GetResource()->SetMaterialTransparency("BossBackParticle", true);
	//임시
	m_pScene->GetResource()->CreateMaterial("MainMap");
	m_pScene->GetResource()->AddMaterialTexture("MainMap", "MainMap",
		TEXT("Diablos_Lair_Floor_TRS/Diablos_Lair_Floor.png"));
	m_pScene->GetResource()->SetMaterialTransparency("MainMap", true);
	m_pScene->GetResource()->SetMaterialShader("MainMap", "TileMapShader");
}

void CTestMainScene::CreateAnimationSequence2D()
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

	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerDustEffeect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("PlayerDustEffeect",
		"PlayerDustEffeect", TEXT("Effect/Dash/DustEffect.png"));

	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("PlayerDustEffeect",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 13.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("ReloadEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("ReloadEffect",
		"ReloadEffect", TEXT("Weapon/Range/effect/Reload.png"));

	for (int i = 0; i < 4; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("ReloadEffect",
			Vector2(i * 28.f, 0), Vector2((i + 1) * 28.f, 9.f));


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
	m_pScene->GetResource()->CreateAnimationSequence2D("RevolverBullet");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("RevolverBullet",
		"RevolverBullet", TEXT("Weapon/Range/Bullet.png"));

	for (int i = 0; i < 4; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("RevolverBullet",
			Vector2(i * 35.f, 0), Vector2((i + 1) * 35.f, 7.f));
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

	m_pScene->GetResource()->CreateAnimationSequence2D("MetalBoomerangBullet");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("MetalBoomerangBullet",
		"MetalBoomerangBullet", TEXT("Weapon/Range/Boomerang_Moving.png"));

	for (int i = 0; i < 2; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("MetalBoomerangBullet",
			Vector2(i * 37.f, 0), Vector2((i + 1) * 37.f, 37.f));
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

	m_pScene->GetResource()->AddAnimationSequence2DNotify("ObjectDieEffect", "CreateEffect", 5);

	/*
	Door
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorClose");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("DoorClose",
		"Door", TEXT("object/door/door.png"));

	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("DoorClose",
			Vector2(i * 66.f, 0), Vector2((i + 1) * 66.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("DoorIdle",
		"Door", TEXT("object/door/door.png"));

	for (int i = 7; i < 17; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("DoorIdle",
			Vector2(i * 66.f, 0), Vector2((i + 1) * 66.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorOpen");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("DoorOpen",
		"Door", TEXT("object/door/door.png"));
	for (int i = 17; i < 23; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("DoorOpen",
			Vector2(i * 66.f, 0), Vector2((i + 1) * 66.f, 20.f));
	}


	//MainMapDoor
	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorClose");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("MainDoorClose",
		"MainDoor", TEXT("Dungeon/Door.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("MainDoorClose",
			Vector2(i * 70.f, 0), Vector2((i + 1) * 70.f, 70.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorCloseIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("MainDoorCloseIdle",
		"MainDoor", TEXT("Dungeon/Door.png"));
	for (int i = 6; i < 10; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("MainDoorCloseIdle",
			Vector2(i * 70.f, 0), Vector2((i + 1) * 70.f, 70.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorOpen");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("MainDoorOpen",
		"MainDoor", TEXT("Dungeon/Door.png"));
	for (int i = 6; i >=0 ; --i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("MainDoorOpen",
			Vector2(i * 70.f, 0), Vector2((i + 1) * 70.f, 70.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorOpenIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("MainDoorOpenIdle",
		"MainDoor", TEXT("Dungeon/Door.png"));
	for (int i = 0; i <1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("MainDoorOpenIdle",
			Vector2(i * 70.f, 0), Vector2((i + 1) * 70.f, 70.f));
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



	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyBowIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyBowIdle",
		"SmallEnemyBow", TEXT("Enemy/SKel/Small/bow.png"));
	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyBowIdle",
			Vector2(i * 17.f, 0), Vector2((i + 1) * 17.f, 13.f));
	}
	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyBowAttack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SmallEnemyBowAttack",
		"SmallEnemyBow", TEXT("Enemy/SKel/Small/bow.png"));
	for (int i = 1; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("SmallEnemyBowAttack",
			Vector2(i * 17.f, 0), Vector2((i + 1) * 17.f, 13.f));
	}

	m_pScene->GetResource()->AddAnimationSequence2DNotify("SmallEnemyBowAttack", "Attack", 2);



	/*
	Ghost
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("GhostMove");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("GhostMove",
		"GhostMove", TEXT("Enemy/Ghost/move.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("GhostMove",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 20.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("GhostAttack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("GhostAttack",
		"GhostAttack", TEXT("Enemy/Ghost/attack.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("GhostAttack",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 20.f));
	}

	m_pScene->GetResource()->AddAnimationSequence2DNotify("GhostAttack", "Attack", 2);
	/*
	Banshee
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BansheeIdle",
		"BansheeIdle", TEXT("Enemy/Banshee/idle.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BansheeIdle",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 22.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeAttack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BansheeAttack",
		"BansheeAttack", TEXT("Enemy/Banshee/attack.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BansheeAttack",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 22.f));
	}

	m_pScene->GetResource()->AddAnimationSequence2DNotify("BansheeAttack", "Attack", 5);

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeBullet");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BansheeBullet",
		"BansheeBullet", TEXT("Enemy/Bullet/note.png"));
	for (int i = 0; i < 4; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BansheeBullet",
			Vector2(i * 13.f, 0), Vector2((i + 1) * 13.f, 16.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeBulletFX");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("BansheeBulletFX",
		"BansheeBulletFX", TEXT("Enemy/Bullet/note_FX.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("BansheeBulletFX",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 27.f));
	}


	/*
	Giant_Red
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedIdle");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Giant_RedIdle",
		"Giant_RedIdle", TEXT("Enemy/Bat/Giant_Red/idle.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Giant_RedIdle",
			Vector2(i * 59.f, 0), Vector2((i + 1) * 59.f, 36.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedAttack");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Giant_RedAttack",
		"Giant_RedAttack", TEXT("Enemy/Bat/Giant_Red/attack.png"));
	for (int i = 0; i < 10; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Giant_RedAttack",
			Vector2(i * 59.f, 0), Vector2((i + 1) * 59.f, 41.f));
	}

	m_pScene->GetResource()->AddAnimationSequence2DNotify("Giant_RedAttack", "Attack", 4);


	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedBullet");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Giant_RedBullet",
		"Giant_RedBullet", TEXT("Enemy/Bullet/giantBullet.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Giant_RedBullet",
			Vector2(i * 14.f, 0), Vector2((i + 1) * 14.f, 14.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedBulletFX");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Giant_RedBulletFX",
		"Giant_RedBulletFX", TEXT("Enemy/Bullet/giantBullet_FX.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Giant_RedBulletFX",
			Vector2(i * 26.f, 0), Vector2((i + 1) * 26.f, 26.f));
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

	m_pScene->GetResource()->AddAnimationSequence2DNotify("BelialHand_Attack", "BelialHandAttack", 7);
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

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_LaserHead");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_LaserHead",
		"Belial_LaserHead", TEXT("boss/Belial/Laser/head.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_LaserHead",
			Vector2(i * 27.f, 0), Vector2((i + 1) * 27.f, 44.f));
	}

	/*Weapon*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_WeaponCharge");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_WeaponCharge",
		"Belial_WeaponCharge", TEXT("boss/Belial/Sword/charge.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_WeaponCharge",
			Vector2(0.f, i*21.f), Vector2(65.f, (i+1) * 21.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_WeaponHit");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_WeaponHit",
		"Belial_WeaponHit", TEXT("boss/Belial/Sword/hit.png"));
	for (int i = 0; i < 5; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_WeaponHit",
			Vector2(i * 22.f, 0), Vector2((i + 1) * 22.f, 51.f));
	}
	//Bullet
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_Bullet");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_Bullet",
		"Belial_Bullet", TEXT("boss/Belial/bullet.png"));
	for (int i = 0; i < 1; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_Bullet",
			Vector2(i * 13.f, 0), Vector2((i + 1) * 13.f, 13.f));
	}

	//Bulletfx
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_BulletFx");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Belial_BulletFx",
		"Belial_BulletFx", TEXT("boss/Belial/bullet_Fx.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Belial_BulletFx",
			Vector2(i * 31.f, 0), Vector2((i + 1) * 31.f, 31.f));
	}

	//Item


	m_pScene->GetResource()->CreateAnimationSequence2D("Gold");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Gold",
		"Gold", TEXT("object/gold/goldCoin.png"));
	for (int i = 0; i < 8; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Gold",
			Vector2(i * 7.f, 0), Vector2((i + 1) * 7.f, 7.f));
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("GoldBullion");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("GoldBullion",
		"GoldBullion", TEXT("object/gold/goldBullion.png"));
	for (int i = 0; i <7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("GoldBullion",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 9.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("HPFairy");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("HPFairy",
		"HPFairy", TEXT("object/hpFairy/Fairy.png"));
	for (int i = 0; i <16; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("HPFairy",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 20.f));
	}


	m_pScene->GetResource()->CreateAnimationSequence2D("Torch");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Torch",
		"Torch", TEXT("object/torch/torch.png"));
	for (int i = 0; i < 7; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Torch",
			Vector2(i * 20.f, 0), Vector2((i + 1) * 20.f, 30.f));
	}


	/*
	NPC
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("Shop");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Shop",
		"Shop", TEXT("NPC/shop.png"));
	for (int i = 0; i < 4; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Shop",
			Vector2(i * 49.f, 0), Vector2((i + 1) * 49.f, 48.f));
	}

	m_pScene->GetResource()->CreateAnimationSequence2D("Restaurant");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("Restaurant",
		"Restaurant", TEXT("NPC/restaurant.png"));
	for (int i = 0; i < 6; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("Restaurant",
			Vector2(i * 15.f, 0), Vector2((i + 1) * 15.f, 23.f));
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

	m_pScene->GetResource()->CreateAnimationSequence2D("RestaurantTable");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("RestaurantTable",
		"RestaurantTable", TEXT("UI/restaurant/RestaurantTable.png"));
	for (int i = 0; i < 3; ++i)
	{
		m_pScene->GetResource()->AddAnimationSequence2DFrame("RestaurantTable",
			Vector2(i * 191.f, 0), Vector2((i + 1) * 191.f, 130.f));
	}

	/*기타*/
	m_pScene->GetResource()->CreateAnimationSequence2D("SpawnEffect");
	m_pScene->GetResource()->SetAnimationSequence2DTexture("SpawnEffect",
		"SpawnEffect", TEXT("object/create.png"));
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			m_pScene->GetResource()->AddAnimationSequence2DFrame("SpawnEffect",
				Vector2(x * 31.f, 31.f*y), Vector2((x + 1) * 31.f, 31.f * (y+1)));
		}
	}

	m_pScene->GetResource()->AddAnimationSequence2DNotify("SpawnEffect", "Spawn", 10);

}

void CTestMainScene::CreateParticle()
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
	m_pScene->GetResource()->SetParticleMaxParticleCount("StageMapParticle", 1000);
	m_pScene->GetResource()->SetParticleStartColor("StageMapParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleEndColor("StageMapParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleStartScale("StageMapParticle", 4.f, 4.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("StageMapParticle", 4.f, 4.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("StageMapParticle", 2.f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("StageMapParticle", 2.f);
	m_pScene->GetResource()->SetParticleRange("StageMapParticle", 1000.f, 1000.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("StageMapParticle", 10.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("StageMapParticle", 10.f);
	m_pScene->GetResource()->SetParticleMoveEnable("StageMapParticle", true);
	m_pScene->GetResource()->SetParticle2D("StageMapParticle", true);
	//m_pScene->GetResource()->SetParticleMoveDir("StageMapParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("StageMapParticle", 0.f, 0.f, 360.f);

	CMaterial* StageMapMateria1l = m_pScene->GetResource()->FindMaterial("DoorParticle");

	m_pScene->GetResource()->CreateParticle("DoorParticle");
	m_pScene->GetResource()->SetParticleUpdateShader("DoorParticle", "ParticleDirUpdateShader");
	m_pScene->GetResource()->SetParticleMaterial("DoorParticle", StageMapMateria1l);
	m_pScene->GetResource()->SetParticleMaxParticleCount("DoorParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("DoorParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleEndColor("DoorParticle", 1.f, 1.f, 1.f, 0.7f);
	m_pScene->GetResource()->SetParticleStartScale("DoorParticle", 5.f, 5.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("DoorParticle", 5.f, 5.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("DoorParticle", 2.f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("DoorParticle", 2.f);
	m_pScene->GetResource()->SetParticleRange("DoorParticle", 100.f, 100.f, 0.f);
	m_pScene->GetResource()->SetParticleMinSpeed("DoorParticle", 10.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("DoorParticle", 10.f);
	m_pScene->GetResource()->SetParticleMoveEnable("DoorParticle", true);
	m_pScene->GetResource()->SetParticle2D("DoorParticle", true);
	m_pScene->GetResource()->SetParticleMoveDir("DoorParticle", 0.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveAngle("DoorParticle", 0.f, 0.f, 90.f);

	CMaterial* BossDieParticle = m_pScene->GetResource()->FindMaterial("BossDieParticle");

	m_pScene->GetResource()->CreateParticle("BossDieParticle");
	m_pScene->GetResource()->SetParticleUpdateShader("BossDieParticle", "ParticleAnimation2DShader");
	//m_pScene->GetResource()->SetParticleUpdateShader("BossDieParticle", "ParticleDirUpdateShader");
	m_pScene->GetResource()->SetParticleMaterial("BossDieParticle", BossDieParticle);
	m_pScene->GetResource()->SetParticleMaxParticleCount("BossDieParticle", 500);
	m_pScene->GetResource()->SetParticleStartColor("BossDieParticle", 1.f,1.f,1.f,1.f);
	m_pScene->GetResource()->SetParticleEndColor("BossDieParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleStartScale("BossDieParticle", 40.f, 40.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("BossDieParticle", 40.f, 40.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("BossDieParticle", 10.5f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("BossDieParticle", 10.8f);
	m_pScene->GetResource()->SetParticleRange("BossDieParticle", 200.f, 200.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveEnable("BossDieParticle", false);
	m_pScene->GetResource()->SetParticle2D("BossDieParticle", true);

	CMaterial* BossBackParticle = m_pScene->GetResource()->FindMaterial("BossBackParticle");

	m_pScene->GetResource()->CreateParticle("BossBackParticle");
	m_pScene->GetResource()->SetParticleUpdateShader("BossBackParticle", "ParticleAnimation2DShader");
	m_pScene->GetResource()->SetParticleMaterial("BossBackParticle", BossBackParticle);
	m_pScene->GetResource()->SetParticleMaxParticleCount("BossBackParticle", 100);
	m_pScene->GetResource()->SetParticleStartColor("BossBackParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleEndColor("BossBackParticle", 1.f, 1.f, 1.f, 1.f);
	m_pScene->GetResource()->SetParticleStartScale("BossBackParticle", 30.f, 30.f, 1.f);
	m_pScene->GetResource()->SetParticleEndScale("BossBackParticle", 30.f, 30.f, 1.f);
	//m_pScene->GetResource()->SetParticleLifeTimeMin("FlameParticle", 0.5f);
	//m_pScene->GetResource()->SetParticleLifeTimeMax("FlameParticle", 0.8f);
	m_pScene->GetResource()->SetParticleMinSpeed("BossBackParticle", 50.f);
	m_pScene->GetResource()->SetParticleMaxSpeed("BossBackParticle", 50.f);
	m_pScene->GetResource()->SetParticleLifeTimeMin("BossBackParticle", 10.5f);
	m_pScene->GetResource()->SetParticleLifeTimeMax("BossBackParticle", 10.8f);
	m_pScene->GetResource()->SetParticleRange("BossBackParticle", 1.f, 1.f, 0.f);
	m_pScene->GetResource()->SetParticleMoveEnable("BossBackParticle", true);
	m_pScene->GetResource()->SetParticle2D("BossBackParticle", true);
}

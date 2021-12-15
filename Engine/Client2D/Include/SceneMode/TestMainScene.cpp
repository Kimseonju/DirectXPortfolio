
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
#include "../UI/BasicMouse.h"
#include "../Object/BossTresure.h"
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
	CreateSound();

	CGlobalValue::MainMouse->SetScene(m_pScene);


	//CBossTresure* pEnemy = m_pScene->SpawnObject<CBossTresure>("BossTresure");

	//CBasicTresure* Tresure = m_pScene->SpawnObject<CBasicTresure>("Tresure");
	//CTorchLight* TorchLight = m_pScene->SpawnObject<CTorchLight>("TorchLight");
	//CShopNPC* ShopNPC = m_pScene->SpawnObject<CShopNPC>("ShopNPC");
	//벨리알테스트용
	//CBelial* pEnemy = m_pScene->SpawnObject<CBelial>("TestEnemy");
	//pEnemy->SetRelativePos(-300.f, 0.f, 0.f);

	//CCollisionObject* pCollisionObject = m_pScene->SpawnObject<CCollisionObject>("Collision1");
	
	//CTeemo* pTeemo = m_pScene->SpawnObject<CTeemo>("Teemo");
	//
	//pTeemo->SetRelativePos(500.f, 500.f, 0.f);
	
	//CPixelCollisionTest* pPixelCollisionTest = m_pScene->SpawnObject<CPixelCollisionTest>("PixelCollisionTest");
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

void CTestMainScene::Start()
{

	Resolution RS = CDevice::GetInst()->GetResolution();
	CPlayer* pPlayer = m_pScene->SpawnObject<CPlayer>("Player");
	CGlobalValue::MainPlayer = pPlayer;
	CStageManager::GetInst()->Init();
	CStageManager::GetInst()->Start();
	CUIManager::GetInst()->Init(m_pScene);
	CUIManager::GetInst()->GetStageMap()->StageMove();
	//CUIManager::GetInst()->GetFadeInOutUI()->StageBossIn();

	CStage1MapEffect* Stage1MapEffect = m_pScene->SpawnObject<CStage1MapEffect>("Stage1MapEffect");
	Stage1MapEffect->SetWorldPos(400.f, 200.f, 0.f);

}

void CTestMainScene::Update(float DeltaTime)
{
	CStageManager::GetInst()->Update(DeltaTime);
	CUIManager::GetInst()->MouseUIWorldCheck();
}

void CTestMainScene::PostUpdate(float DeltaTime)
{
}

void CTestMainScene::CreateMaterial()
{


	m_pScene->GetResource()->CreateMaterial("StageMapMaterial");


	m_pScene->GetResource()->CreateMaterial("DoorParticle");
	

	m_pScene->GetResource()->CreateMaterial("BossDieParticle");



	m_pScene->GetResource()->CreateMaterial("BossBackParticle");
	//임시
	//m_pScene->GetResource()->CreateMaterial("MainMap");
	//m_pScene->GetResource()->AddMaterialTexture("MainMap", "MainMap",
	//	TEXT("Diablos_Lair_Floor_TRS/Diablos_Lair_Floor.png"));
	//m_pScene->GetResource()->SetMaterialTransparency("MainMap", true);
	//m_pScene->GetResource()->SetMaterialShader("MainMap", "TileMapShader");

}

void CTestMainScene::CreateAnimationSequence2D()
{
	m_pScene->GetResource()->CreateAnimationSequence2D("Gate_Idle");

	m_pScene->GetResource()->CreateAnimationSequence2D("Gate_In");

	//m_pScene->GetResource()->AddAnimationSequence2DNotify("Gate_In", "Gate_InEnd", 3);
	/*
	Player
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerRun");

	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerJump");


	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerDie");

	m_pScene->GetResource()->CreateAnimationSequence2D("PlayerDustEffeect");

	m_pScene->GetResource()->CreateAnimationSequence2D("ReloadEffect");
	
	/*ShortSwordEfect*/
	m_pScene->GetResource()->CreateAnimationSequence2D("ShortSwordEffect");


	/*
	Revolver
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("RevolverEffect");
	m_pScene->GetResource()->CreateAnimationSequence2D("RevolverBullet");

	/*
	MetalBoomerang
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("MetalBoomerangEffect");

	m_pScene->GetResource()->CreateAnimationSequence2D("MetalBoomerangBullet");

	//CosmosSword

	m_pScene->GetResource()->CreateAnimationSequence2D("CosmosSwordIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("CosmosSwordEffect");
	m_pScene->GetResource()->CreateAnimationSequence2D("TAANAIdle");
	m_pScene->GetResource()->CreateAnimationSequence2D("TAANAShield");
	/*
	ObjectDieEffect
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("ObjectDieEffect");

	//m_pScene->GetResource()->AddAnimationSequence2DNotify("ObjectDieEffect", "CreateEffect", 5);

	/*
	Door
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorClose");
	m_pScene->GetResource()->AddAnimationSequence2DNotify("DoorClose", "DoorSound", 4);

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("DoorOpen");
	//m_pScene->GetResource()->AddAnimationSequence2DNotify("DoorOpen", "DoorSound", 4);


	//MainMapDoor
	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorClose");

	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorCloseIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorOpen");

	m_pScene->GetResource()->CreateAnimationSequence2D("MainDoorOpenIdle");
	/*
	Enemy
	*/


	/*
	Skel Small 
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyIdleShot");

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyMove");

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyMoveShot");

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyDaggerAttack");
	//m_pScene->GetResource()->AddAnimationSequence2DNotify("SmallEnemyDaggerAttack", "Attack", 7);

	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyDaggerIdle");



	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyBowIdle");
	m_pScene->GetResource()->CreateAnimationSequence2D("SmallEnemyBowAttack");

	//m_pScene->GetResource()->AddAnimationSequence2DNotify("SmallEnemyBowAttack", "Attack", 2);



	/*
	Ghost
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("GhostMove");

	m_pScene->GetResource()->CreateAnimationSequence2D("GhostAttack");

	//m_pScene->GetResource()->AddAnimationSequence2DNotify("GhostAttack", "Attack", 2);
	/*
	Banshee
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeAttack");

	//m_pScene->GetResource()->AddAnimationSequence2DNotify("BansheeAttack", "Attack", 5);

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeBullet");

	m_pScene->GetResource()->CreateAnimationSequence2D("BansheeBulletFX");


	/*
	Giant_Red
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedIdle");

	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedAttack");

	//m_pScene->GetResource()->AddAnimationSequence2DNotify("Giant_RedAttack", "Attack", 4);


	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedBullet");

	m_pScene->GetResource()->CreateAnimationSequence2D("Giant_RedBulletFX");


	/*
	
	Boss. Belial

	
	*/
	/*Head*/
	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHead_Idle");

	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHead_Attack");


	/*Hand*/
	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHand_Idle");

	m_pScene->GetResource()->CreateAnimationSequence2D("BelialHand_Attack");
	//Notify설정할부분
	//m_pScene->GetResource()->AddAnimationSequence2DNotify("PlayerAttack", "Attack", 8);

//	m_pScene->GetResource()->AddAnimationSequence2DNotify("BelialHand_Attack", "BelialHandAttack", 7);
	/*Back*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_Circle");

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_CircleParticle");

	/*Laser*/

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_LaserBody");

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_LaserHead");

	/*Weapon*/
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_WeaponCharge");

	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_WeaponHit");
	//Bullet
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_Bullet");

	//Bulletfx
	m_pScene->GetResource()->CreateAnimationSequence2D("Belial_BulletFx");

	//Item


	m_pScene->GetResource()->CreateAnimationSequence2D("Gold");


	m_pScene->GetResource()->CreateAnimationSequence2D("GoldBullion");

	m_pScene->GetResource()->CreateAnimationSequence2D("HPFairy");


	m_pScene->GetResource()->CreateAnimationSequence2D("Torch");


	/*
	NPC
	*/

	m_pScene->GetResource()->CreateAnimationSequence2D("Shop");

	m_pScene->GetResource()->CreateAnimationSequence2D("Restaurant");

	/*
	UI
	*/
	m_pScene->GetResource()->CreateAnimationSequence2D("LifeWave");

	m_pScene->GetResource()->CreateAnimationSequence2D("RestaurantTable");

	/*기타*/
	m_pScene->GetResource()->CreateAnimationSequence2D("SpawnEffect");

//	m_pScene->GetResource()->AddAnimationSequence2DNotify("SpawnEffect", "Spawn", 10);

}

void CTestMainScene::CreateParticle()
{

	CMaterial* StageMapMaterial = m_pScene->GetResource()->FindMaterial("StageMapMaterial");

	m_pScene->GetResource()->CreateParticle("StageMapParticle");

	CMaterial* StageMapMateria1l = m_pScene->GetResource()->FindMaterial("DoorParticle");

	m_pScene->GetResource()->CreateParticle("DoorParticle");

	CMaterial* BossDieParticle = m_pScene->GetResource()->FindMaterial("BossDieParticle");

	m_pScene->GetResource()->CreateParticle("BossDieParticle");

	CMaterial* BossBackParticle = m_pScene->GetResource()->FindMaterial("BossBackParticle");

	m_pScene->GetResource()->CreateParticle("BossBackParticle");
}

void CTestMainScene::CreateSound()
{

#pragma region BGMSound
	m_pScene->GetResource()->LoadSound("BGM", true, "Town",
		"bgm/0.Town.wav");
	m_pScene->GetResource()->LoadSound("BGM", true, "Boss",
		"bgm/1.JailBoss.wav");
	m_pScene->GetResource()->LoadSound("BGM", true, "Fleld",
		"bgm/1.JailField.wav");
	m_pScene->GetResource()->LoadSound("BGM", true, "Shop",
		"bgm/Shop.wav");

	m_pScene->GetResource()->LoadSound("BGM", true, "title",
		"bgm/title.wav");
	m_pScene->GetResource()->LoadSound("BGM", true, "Foodshop",
		"bgm/Foodshop.wav");
#pragma endregion

#pragma region BossSoud
	m_pScene->GetResource()->LoadSound("Enemy", false, "belial_laugh",
		"enemy/belial/belial_laugh.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "BelialLaser",
		"enemy/belial/Laser.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "BelialBullet",
		"enemy/belial/BelialBullet.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "BelialWeapon",
		"enemy/belial/BelialWeapon.wav");
#pragma endregion


#pragma region EnemySound
	m_pScene->GetResource()->LoadSound("Enemy", false, "BatDie",
		"enemy/Bat/BatDie.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "BansheeAttack",
		"enemy/Banshee/high_pitch_scream_gverb.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "SkelArrowDie",
		"enemy/skells/bow_crossbow_arrow_draw_stretch1_03.wav");

	m_pScene->GetResource()->LoadSound("Enemy", false, "SkelBowAttack",
		"enemy/skells/etc-sound0034_Bow.wav");

	m_pScene->GetResource()->LoadSound("Enemy", false, "SkelSwordAttack1",
		"enemy/skells/swish-1.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "SkelSwordAttack2",
		"enemy/skells/swish-5.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "SkelSwordAttack2",
		"enemy/skells/swish-6.wav");

	m_pScene->GetResource()->LoadSound("Enemy", false, "Hit_Enemy",
		"enemy/Effect/Hit_Enemy.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "EnemyDie",
		"enemy/Effect/EnemyDie.wav");
	m_pScene->GetResource()->LoadSound("Enemy", false, "SpawnEnemy",
		"enemy/Effect/SpawnEnemy.wav");
#pragma endregion

#pragma region PlayerSound
	m_pScene->GetResource()->LoadSound("Player", false, "Dash",
		"player/dash.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "Get_Fairy",
		"player/Get_Fairy.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "PlayerHit",
		"player/Hit_Player.wav");
	m_pScene->GetResource()->LoadSound("Player", false, "PlayerJumping",
		"player/Jumping.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "PlayerWeaponSwap",
		"player/swap.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "step_lth1",
		"player/step_lth1.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "step_lth2",
		"player/step_lth2.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "step_lth3",
		"player/step_lth3.wav");

	m_pScene->GetResource()->LoadSound("Player", false, "step_lth4",
		"player/step_lth4.wav");

	m_pScene->GetResource()->LoadSound("PlayerAttack", false, "SwordAttack",
		"weapon/Melee/generalAttack.wav");
	m_pScene->GetResource()->LoadSound("PlayerAttack", false, "SwordAttack2",
		"weapon/Melee/swing1.wav");
	m_pScene->GetResource()->LoadSound("PlayerAttack", false, "MetalBoomerangAttack",
		"weapon/Range/MetalBoomerang.wav");

	m_pScene->GetResource()->LoadSound("PlayerAttack", false, "RevolverAttack",
		"weapon/Range/RevolverFire.wav");

	m_pScene->GetResource()->LoadSound("PlayerAttack", false, "Reload",
		"weapon/Range/Reload.wav");
	m_pScene->GetResource()->LoadSound("PlayerAttack", false, "Reload2",
		"weapon/Range/Reload2.wav");
#pragma endregion

	m_pScene->GetResource()->LoadSound("UI", false, "GetItem",
		"object/GetItem.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "OpenInventory",
		"object/OpenInventory.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "ItemInputInventory",
		"object/ItemInputInventory.wav");
	m_pScene->GetResource()->LoadSound("UI", false, "ItemOutInventory",
		"object/ItemOutInventory.wav");

	m_pScene->GetResource()->LoadSound("UI", false, "restaurantEffect",
		"restaurantEffect.wav");

	m_pScene->GetResource()->LoadSound("Object", false, "GetGold",
		"object/GetGold.wav");

	m_pScene->GetResource()->LoadSound("Object", false, "TresureBoxOpen",
		"object/TresureBoxOpen.wav");

	m_pScene->GetResource()->LoadSound("Object", false, "DoorOnOff",
		"object/DoorOnOff.wav");

	m_pScene->GetResource()->LoadSound("Object", false, "BossTresureBox",
		"object/BossTresureBox.wav");

}

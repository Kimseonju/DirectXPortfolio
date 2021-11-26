#include "ClientManager.h"
#include "Scene/SceneManager.h"
#include "SceneMode/MainScene.h"
#include "SceneMode/StartScene.h"
#include "SceneMode/TestMainScene.h"
#include "Input.h"
#include "CollisionManager.h"
#include "IMGUIManager.h"
#include "Engine.h"
#include "TestWindow.h"
#include "IMGUIManager.h"
#include "UI/MouseWidget.h"
#include "Resource/ResourceManager.h"
#include "SceneMode/LoadingScene.h"
#include "SceneMode/EndingScene.h"

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
}

bool CClientManager::Init()
{
    //CTestWindow* Window = CIMGUIManager::GetInst()->AddWindow<CTestWindow>("TestWindow");
    //CEngine::GetInst()->OnDebugLog();
    //CEngine::GetInst()->OnLogFPS(true);
    //Window->AddWindowFlag(ImGuiWindowFlags_NoTitleBar);
    //Window->AddWindowFlag(ImGuiWindowFlags_NoMove);
    //Window->AddWindowFlag(ImGuiWindowFlags_NoResize);
    // 
    // 
    // 키 등록
	void LeftMove(float DeltaTime);
	void RightMove(float DeltaTime);
	void DownMove(float DeltaTime);
	void JumpMove(float DeltaTime);
    CInput::GetInst()->CreateKey("MoveUp", 'W');
    //CInput::GetInst()->CreateKey("MoveDown", 'S');
    CInput::GetInst()->CreateKey("Left", 'A');
    CInput::GetInst()->CreateKey("Right", 'D');
    CInput::GetInst()->CreateKey("Jump", VK_SPACE);
    CInput::GetInst()->CreateKey("Attack", VK_LBUTTON);
    CInput::GetInst()->CreateKey("Dash", VK_RBUTTON);
    CInput::GetInst()->CreateKey("InventoryOnOff", 'I');
    CInput::GetInst()->CreateKey("MapOnOff", VK_TAB);
    CInput::GetInst()->CreateKey("MouseWhell", DIK_MOUSEWHEEL);
    CInput::GetInst()->CreateKey("InteractionInputKey", 'F');
    CInput::GetInst()->CreateKey("ShopUI", 'R');
    CInput::GetInst()->CreateKey("StatusUI", 'T');
  
    CInput::GetInst()->CreateKey("Skill1", '1');
    CInput::GetInst()->CreateKey("Skill2", '2');
    CInput::GetInst()->SetControlKey("Skill2", true);
    //Object는 부셔지지않지만 중력을받을수있거나 플레이어와 키를통해 상호작용이 가능 
    //Objecct_Broken는 부셔지고, 중력과상호작용하고, 플레이어와 상호작용을한다.
    //적이있는맵은 Object_Broken이 스폰하지 않는다.
    CCollisionManager::GetInst()->CreateChannel("Static", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("Player", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Enemy", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("EnemyAttack", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Tile_Nopass", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Tile_pass", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("NextStage", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Item", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("InteractionInputKey", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("BossSpawn", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Object", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Object_Broken", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("TileCheckCollsion", Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->CreateChannel("Door", Collision_Interaction::Ignore);
    
    CCollisionManager::GetInst()->CreateProfile("Static", Collision_Channel::Static);
    CCollisionManager::GetInst()->CreateProfile("Player", Collision_Channel::Player);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", Collision_Channel::PlayerAttack);
    CCollisionManager::GetInst()->CreateProfile("Enemy", Collision_Channel::Enemy);
    CCollisionManager::GetInst()->CreateProfile("EnemyAttack", Collision_Channel::EnemyAttack);
    CCollisionManager::GetInst()->CreateProfile("Tile_Nopass", Collision_Channel::Tile_Nopass);
    CCollisionManager::GetInst()->CreateProfile("Tile_pass", Collision_Channel::Tile_pass);
    CCollisionManager::GetInst()->CreateProfile("NextStage", Collision_Channel::NextStage);
    CCollisionManager::GetInst()->CreateProfile("Item", Collision_Channel::Item);
    CCollisionManager::GetInst()->CreateProfile("InteractionInputKey", Collision_Channel::InteractionInputKey);
    CCollisionManager::GetInst()->CreateProfile("BossSpawn", Collision_Channel::BossSpawn);
    CCollisionManager::GetInst()->CreateProfile("Object", Collision_Channel::Object);
    CCollisionManager::GetInst()->CreateProfile("Object_Broken", Collision_Channel::Object_Broken);
    CCollisionManager::GetInst()->CreateProfile("TileCheckCollsion", Collision_Channel::TileCheckCollsion);
    CCollisionManager::GetInst()->CreateProfile("Door", Collision_Channel::Door);

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::EnemyAttack,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("EnemyAttack", Collision_Channel::Player,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::BossSpawn,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("BossSpawn", Collision_Channel::Player,
        Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Enemy", Collision_Channel::PlayerAttack,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::Enemy,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::Player,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::PlayerAttack,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Enemy,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("Enemy", Collision_Channel::Player,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::Player,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Tile_Nopass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::PlayerAttack,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::Tile_Nopass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Item", Collision_Channel::Tile_Nopass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::Item,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("Item", Collision_Channel::Tile_pass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Tile_pass", Collision_Channel::Item,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::InteractionInputKey,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("InteractionInputKey", Collision_Channel::Player,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("InteractionInputKey", Collision_Channel::InteractionInputKey,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::TileCheckCollsion,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Tile_pass", Collision_Channel::TileCheckCollsion,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Tile_Nopass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Tile_pass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Door,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Door", Collision_Channel::TileCheckCollsion,
       Collision_Interaction::Block);

   CCollisionManager::GetInst()->SetProfileChannelState("EnemyAttack", Collision_Channel::Tile_Nopass,
       Collision_Interaction::Block);
   CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::EnemyAttack,
       Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Object", Collision_Channel::Tile_Nopass,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::Object,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("Object", Collision_Channel::Tile_pass,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("Tile_pass", Collision_Channel::Object,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("Object", Collision_Channel::Object,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Object", Collision_Channel::InteractionInputKey,
        Collision_Interaction::Block);
    CCollisionManager::GetInst()->SetProfileChannelState("InteractionInputKey", Collision_Channel::Object,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Object,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Object", Collision_Channel::Player,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Object_Broken", Collision_Channel::Object_Broken,
        Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Object_Broken,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Object_Broken,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Object_Broken,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("TileCheckCollsion", Collision_Channel::Object_Broken,
        Collision_Interaction::Ignore);


    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::NextStage,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("NextStage", Collision_Channel::Player,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Item,
        Collision_Interaction::Block);

    CCollisionManager::GetInst()->SetProfileChannelState("Item", Collision_Channel::Player,
        Collision_Interaction::Block);
    CSceneManager::GetInst()->SetSceneMode<CLoadingScene>();
    //CSceneManager::GetInst()->SetSceneMode<CEndingScene>();
    
    CreateMouse();

    return true;
}

void CClientManager::CreateMouse()
{
    m_Mouse = CEngine::GetInst()->CreateMouseWidget<CBasicMouse>("Mouse");
    m_Mouse->SetTexture("BasicCursor", TEXT("UI/Cursor/BasicCursor.png"));
    m_Mouse->SetTexture("ShootingCursor", TEXT("UI/Cursor/ShootingCursor.png"));
    m_Mouse->SetSize(63.f, 63.f);
    CGlobalValue::MainMouse = m_Mouse;
}


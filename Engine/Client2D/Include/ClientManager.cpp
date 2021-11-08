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

DEFINITION_SINGLE(CClientManager)

CClientManager::CClientManager()
{
}

CClientManager::~CClientManager()
{
}

bool CClientManager::Init()
{
    CTestWindow* Window = CIMGUIManager::GetInst()->AddWindow<CTestWindow>("TestWindow");
    //CEngine::GetInst()->OnDebugLog();
    //CEngine::GetInst()->OnLogFPS(true);
    //Window->AddWindowFlag(ImGuiWindowFlags_NoTitleBar);
    Window->AddWindowFlag(ImGuiWindowFlags_NoMove);
    Window->AddWindowFlag(ImGuiWindowFlags_NoResize);
    // Å° µî·Ï
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

    CInput::GetInst()->CreateKey("Skill1", '1');
    CInput::GetInst()->CreateKey("Skill2", '2');
    CInput::GetInst()->SetControlKey("Skill2", true);

    CCollisionManager::GetInst()->CreateChannel("Static", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("Player", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("PlayerAttack", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("Enemy", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("EnemyAttack", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("Tile_Nopass", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("Tile_pass", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("NextStage", Collision_Interaction::Block);
    CCollisionManager::GetInst()->CreateChannel("Item", Collision_Interaction::Block);

    CCollisionManager::GetInst()->CreateProfile("Static", Collision_Channel::Static);
    CCollisionManager::GetInst()->CreateProfile("Player", Collision_Channel::Player);
    CCollisionManager::GetInst()->CreateProfile("PlayerAttack", Collision_Channel::PlayerAttack);
    CCollisionManager::GetInst()->CreateProfile("Enemy", Collision_Channel::Enemy);
    CCollisionManager::GetInst()->CreateProfile("EnemyAttack", Collision_Channel::EnemyAttack);
    CCollisionManager::GetInst()->CreateProfile("Tile_Nopass", Collision_Channel::Tile_Nopass);
    CCollisionManager::GetInst()->CreateProfile("Tile_pass", Collision_Channel::Tile_pass);
    CCollisionManager::GetInst()->CreateProfile("NextStage", Collision_Channel::NextStage);
    CCollisionManager::GetInst()->CreateProfile("Item", Collision_Channel::Item);

    CCollisionManager::GetInst()->SetProfileChannelState("Player", Collision_Channel::Player,
        Collision_Interaction::Ignore);
   CCollisionManager::GetInst()->SetProfileChannelState("Enemy", Collision_Channel::Enemy,
       Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::PlayerAttack,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("EnemyAttack", Collision_Channel::PlayerAttack,
        Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("Enemy", Collision_Channel::EnemyAttack,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("PlayerAttack", Collision_Channel::EnemyAttack,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("EnemyAttack", Collision_Channel::EnemyAttack,
        Collision_Interaction::Ignore);

    CCollisionManager::GetInst()->SetProfileChannelState("Tile_pass", Collision_Channel::Tile_pass,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Tile_pass", Collision_Channel::Tile_Nopass,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::Tile_pass,
        Collision_Interaction::Ignore);
    CCollisionManager::GetInst()->SetProfileChannelState("Tile_Nopass", Collision_Channel::Tile_Nopass,
        Collision_Interaction::Ignore);
    //CSceneManager::GetInst()->SetSceneMode<CStartScene>();
    //CSceneManager::GetInst()->SetSceneMode<CMainScene>();
    //CSceneManager::GetInst()->SetSceneMode<CLoadingScene>();
    CSceneManager::GetInst()->SetSceneMode<CTestMainScene>();

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


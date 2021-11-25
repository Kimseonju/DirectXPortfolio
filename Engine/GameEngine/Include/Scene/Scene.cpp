
#include "Scene.h"
#include "SceneResource.h"
#include "CameraManager.h"
#include "SceneCollision.h"
#include "Viewport.h"
#include "../Engine.h"
CScene::CScene()    :
    m_pSceneMode(nullptr),
    m_pSceneResource(nullptr),
    m_pCameraManager(nullptr),
    m_pCollision(nullptr),
    m_pViewport(nullptr),
    m_StartScene(false),
    m_StartTime(0.f)
{
}

CScene::~CScene()
{
    m_ObjList.clear();

    SAFE_DELETE(m_pViewport);
    SAFE_DELETE(m_pCollision);
    SAFE_DELETE(m_pCameraManager);
    SAFE_DELETE(m_pSceneMode);
    SAFE_DELETE(m_pSceneResource);
}

CGameObject* CScene::FindObject(const std::string& Name)
{
    auto    iter = m_ObjList.begin();
    auto    iterEnd = m_ObjList.end();

    for (; iter != iterEnd; ++iter)
    {
        if ((*iter)->GetName() == Name)
            return *iter;
    }

    return nullptr;
}

void CScene::Start()
{
    m_pSceneMode->Start();
    m_StartScene = true;

    auto    iter = m_ObjList.begin();
    auto    iterEnd = m_ObjList.end();

    for (; iter != iterEnd; ++iter)
    {
        (*iter)->Start();
    }

    m_pCameraManager->Start();

    m_pViewport->Start();

    m_pCollision->Start();
    m_StartTime = 3.f;
}

bool CScene::Init()
{
    m_pSceneMode = new CSceneMode;

    m_pSceneMode->m_pScene = this;

    if (!m_pSceneMode->Init())
        return false;

    m_pSceneResource = new CSceneResource;

    m_pSceneResource->m_pScene = this;

    if (!m_pSceneResource->Init())
        return false;

    m_pCameraManager = new CCameraManager;

    m_pCameraManager->m_pScene = this;

    if (!m_pCameraManager->Init())
        return false;

    m_pCollision = new CSceneCollision;

    m_pCollision->m_pScene = this;

    if (!m_pCollision->Init())
        return false;

    m_pViewport = new CViewport;

    m_pViewport->m_Scene = this;

    if (!m_pViewport->Init())
        return false;
    return true;
}

void CScene::Update(float DeltaTime)
{
    if (!CEngine::GetInst()->IsObjectPause())
    {
        auto    iter = m_ObjList.begin();
        auto    iterEnd = m_ObjList.end();
        {
            for (; iter != iterEnd; ++iter)
            {
                if (!(*iter)->IsActive())
                {
                    continue;
                }

                if ((*iter)->IsEnable())
                {
                    if (!(*iter)->IsStart())
                        (*iter)->Start();

                    (*iter)->Update(DeltaTime);
                }
            }
        }
    }

    m_pCameraManager->Update(DeltaTime);

    m_pViewport->Update(DeltaTime);
    if (m_pSceneMode)
        m_pSceneMode->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
    if (!CEngine::GetInst()->IsObjectPause())
    {
        auto    iter = m_ObjList.begin();
        auto    iterEnd = m_ObjList.end();

        for (; iter != iterEnd; ++iter)
        {
            if (!(*iter)->IsActive())
            {
                continue;
            }

            if ((*iter)->IsEnable())
            {
                if (!(*iter)->IsStart())
                    (*iter)->Start();

                (*iter)->PostUpdate(DeltaTime);
            }

        }
    }
    m_pCameraManager->PostUpdate(DeltaTime);

    m_pViewport->PostUpdate(DeltaTime);
}

void CScene::Collision(float DeltaTime)
{
    if (!CEngine::GetInst()->IsObjectPause())
    {
        m_pCollision->Collision(DeltaTime);
    }
    /*auto    iter = m_ObjList.begin();
    auto    iterEnd = m_ObjList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = m_ObjList.erase(iter);
            iterEnd = m_ObjList.end();
            continue;
        }

        if ((*iter)->IsEnable())
        {
            if (!(*iter)->IsStart())
                (*iter)->Start();

            (*iter)->Collision(DeltaTime);
        }

        ++iter;
    }*/
}

void CScene::Render(float DeltaTime)
{
    auto    iter = m_ObjList.begin();
    auto    iterEnd = m_ObjList.end();

    for (; iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            iter = m_ObjList.erase(iter);
            iterEnd = m_ObjList.end();
            continue;
        }

        if ((*iter)->IsEnable())
        {
            if (!(*iter)->IsStart())
                (*iter)->Start();

            (*iter)->PrevRender(DeltaTime);
        }

        ++iter;
    }
    m_pViewport->PrevRender(DeltaTime);
}

void CScene::Clear()
{
    auto    iter = m_ObjList.begin();
    auto    iterEnd = m_ObjList.end();

    for (; iter != iterEnd; ++iter)
    {
        (*iter)->ClearTransformState();
    }
}

#include "pch.h"
#include "InspectorWindow.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"

#include "IMGUITransformComponent.h"
#include "IMGUISpriteComponent.h"
#include "IMGUICollider2DComponent.h"
#include "IMGUICameraComponent.h"
#include "IMGUIObjectInfoComponent.h"
#include "GameObject.h"
CInspectorWindow::CInspectorWindow()
{
}

CInspectorWindow::~CInspectorWindow()
{
	SAFE_DELETE(m_Object);
	SAFE_DELETE(m_Transform);
	SAFE_DELETE(m_Sprite);
	SAFE_DELETE(m_Collider);
	SAFE_DELETE(m_Camera);
}

bool CInspectorWindow::Init()
{
	CreateObjectInfo();
	CreateTransform();
	CreateSprite();
	CreateCollider();
	CreateCamera();

	AllComponentClose();


	return true;
}

void CInspectorWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	if (m_Transform->IsEnable())
	{
		m_Transform->Update(DeltaTime);
	}

	if (m_Object->IsEnable())
	{
		m_Object->Update(DeltaTime);
	}
	
}

void CInspectorWindow::ObjectUpdateInfo(CGameObject* Obj)
{
	m_Object->UpdateInfo(Obj);

}

void CInspectorWindow::TransformUpdate(CSceneComponent* Component)
{
	m_Transform->SetComponent(Component);
	m_Transform->Enable(true);
}

void CInspectorWindow::SpriteUpdate(CSpriteComponent* Sprite)
{
	m_Sprite->UpdateInfo(Sprite);
}

void CInspectorWindow::ColliderUpdate(CCollider* Collider)
{
	m_Collider->UpdateInfo(Collider);
}

void CInspectorWindow::CameraUpdate(CCamera* Camera)
{
	m_Camera->UpdateInfo(Camera);
}
void CInspectorWindow::CreateObjectInfo()
{
	if (m_Object)
		return;
	m_Object = new CIMGUIObjectInfoComponent;
	m_Object->SetOwner(this);
	m_Object->Init();
}
void CInspectorWindow::CreateTransform()
{
	if (m_Transform)
		return;
	m_Transform = new CIMGUITransformComponent;
	m_Transform->SetOwner(this);
	m_Transform->Init();
}

void CInspectorWindow::CreateSprite()
{
	if (m_Sprite)
		return;
	m_Sprite = new CIMGUISpriteComponent;
	m_Sprite->SetOwner(this);
	m_Sprite->Init();
}

void CInspectorWindow::CreateCollider()
{
	if (m_Collider)
		return;
	m_Collider = new CIMGUICollider2DComponent;
	m_Collider->SetOwner(this);
	m_Collider->Init();
}

void CInspectorWindow::CreateCamera()
{
	if (m_Camera)
		return;
	m_Camera = new CIMGUICameraComponent;
	m_Camera->SetOwner(this);
	m_Camera->Init();
}

void CInspectorWindow::AllComponentClose()
{
	if(!m_Object->IsObject())
		m_Object->Enable(false);
	m_Transform->Enable(false);
	m_Sprite->Enable(false);
	m_Collider->Enable(false);
	m_Camera->Enable(false);
}


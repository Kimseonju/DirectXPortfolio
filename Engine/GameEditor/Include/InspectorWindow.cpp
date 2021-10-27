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
CInspectorWindow::CInspectorWindow()
{
}

CInspectorWindow::~CInspectorWindow()
{
	SAFE_DELETE(m_Transform);
	SAFE_DELETE(m_Sprite);
	SAFE_DELETE(m_Collider2D);
}

bool CInspectorWindow::Init()
{
	CIMGUIText* Text = AddWidget<CIMGUIText>("À§Ä¡");
	Text->SetFont("DefaultFont");
	CreateTransform();
	CreateSprite();
	CreateCollider2D();
	m_Transform->Enable(false);
	m_Sprite->Enable(false);
	m_Collider2D->Enable(false);

	return true;
}

void CInspectorWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	m_Transform->Update(DeltaTime);
}

void CInspectorWindow::TransformUpdate(CSceneComponent* Component)
{
	m_Transform->SetComponent(Component);
	m_Transform->Enable(true);
}

void CInspectorWindow::SpriteUpdate(CSpriteComponent* Sprite)
{
	m_Sprite->InfoUpdate(Sprite);
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

void CInspectorWindow::CreateCollider2D()
{
	if (m_Collider2D)
		return;
	m_Collider2D = new CIMGUICollider2DComponent;
	m_Collider2D->SetOwner(this);
	m_Collider2D->Init();
}


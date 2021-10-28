#include "pch.h"
#include "IMGUICollider2DComponent.h"
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
#include <Component/Collider.h>
CIMGUICollider2DComponent::CIMGUICollider2DComponent()
{
}

CIMGUICollider2DComponent::~CIMGUICollider2DComponent()
{
}

void CIMGUICollider2DComponent::InfoUpdate(CCollider* Collider)
{
	m_Collider = Collider;
	Collider_Shape Shape=m_Collider->GetColliderShape();
	Collider_Space Space = m_Collider->GetColliderSpace();

	switch (Shape)
	{
	case Collider_Shape::Box2D:
		m_ColliderType->SetText("Box2D");
		break;
	case Collider_Shape::Circle:
		m_ColliderType->SetText("Circle");
		break;
	case Collider_Shape::Pixel:
		m_ColliderType->SetText("Pixel");
		break;
	}

	switch (Space)
	{
	case Collider_Space::Collider2D:
		m_ColliderSpace->SetText("Collider2D");
		break;
	case Collider_Space::Collider3D:
		m_ColliderSpace->SetText("Collider3D");
		break;
	default:
		break;
	}
	Enable(true);

}

bool CIMGUICollider2DComponent::Init()
{
#pragma region Type

	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("##Type");
	Text->SetText("Type");
	m_vecWidget.push_back(Text);
	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ColliderType = m_Owner->AddWidget<CIMGUIText>("##ColliderType", 300.f, 100.f);
	
	m_vecWidget.push_back(m_ColliderType);

	Text = m_Owner->AddWidget<CIMGUIText>("##Space");
	Text->SetText("Space");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ColliderSpace = m_Owner->AddWidget<CIMGUIText>("##ColliderSpace", 300.f, 100.f);

	m_vecWidget.push_back(m_ColliderType);

#pragma endregion
	return true;
}

void CIMGUICollider2DComponent::Update(float DeltaTime)
{
}


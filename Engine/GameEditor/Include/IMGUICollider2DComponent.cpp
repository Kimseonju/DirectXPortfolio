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
#include "IMGUIDrag.h"
#include <Component/Collider.h>
#include <Component/ColliderBox2D.h>
#include <Component/ColliderCircle.h>
#include <CollisionManager.h>
#include "IMGUICollapsingHeader.h"
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
	{
		m_ColliderType->SetText("Box2D");
		Box2DInfo info = ((CColliderBox2D*)m_Collider)->GetInfo();
		m_ColliderLengthX->SetFloat(info.Length[0]);
		m_ColliderLengthY->SetFloat(info.Length[1]);
		break;
	}
	case Collider_Shape::Circle:
	{
		m_ColliderType->SetText("Circle");
		CircleInfo info = ((CColliderCircle*)m_Collider)->GetInfo();
		m_ColliderRadius->SetFloat(info.Radius);
		break;
	}
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


	m_ColliderProfileCombo = m_Owner->AddWidget<CIMGUIComboBox>("##TextureCombo", 100.f, 20.f);
	m_vecWidget.push_back(m_ColliderProfileCombo);
	m_ColliderProfileCombo->SetSelectCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::ProfileComboCallback);
	std::vector<std::string> Name;
	CCollisionManager::GetInst()->GetProfileName(Name);

	for (size_t i = 0; i < Name.size(); i++)
	{
		m_ColliderProfileCombo->AddItem(Name[i].c_str());
	}
	if (m_Collider->GetProfile())
	{
		m_ColliderProfileCombo->SetPrevName(m_Collider->GetProfile()->Name);
	}
	Enable(true);

}

bool CIMGUICollider2DComponent::Init()
{
	CIMGUIWidgetComponent::Init();

	m_Header = m_Owner->AddWidget<CIMGUICollapsingHeader>("Collider2D");
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
#pragma region Input

	Text = m_Owner->AddWidget<CIMGUIText>("Length", 100.f, 20.f);
	Text->SetText("Length");
	SameLine->SetSize(20.f, 20.f);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(Text);
	m_vecWidget.push_back(SameLine);

	m_ColliderLengthX = m_Owner->AddWidget<CIMGUIDrag>("##ColliderLengthX", 100.f, 20.f);
	m_ColliderLengthX->SetNumberFloat(true);
	m_ColliderLengthX->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputLength);
	m_vecWidget.push_back(m_ColliderLengthX);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_ColliderLengthY = m_Owner->AddWidget<CIMGUIDrag>("##ColliderLengthY", 100.f, 20.f);
	m_ColliderLengthY->SetNumberFloat(true);
	m_ColliderLengthY->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputLength);
	m_vecWidget.push_back(m_ColliderLengthY);


	m_ColliderRadius = m_Owner->AddWidget<CIMGUIDrag>("##ColliderRadius", 100.f, 20.f);
	m_ColliderRadius->SetNumberFloat(true);
	m_ColliderRadius->SetInputCallback<CIMGUICollider2DComponent>(this, &CIMGUICollider2DComponent::InputRadius);
	m_vecWidget.push_back(m_ColliderRadius);
#pragma endregion
	m_Header->WidgetPush(m_vecWidget);
	m_vecWidget.push_back(m_Header);
	return true;
}

void CIMGUICollider2DComponent::Update(float DeltaTime)
{
}

void CIMGUICollider2DComponent::Enable(bool Enable)
{
	CIMGUIWidgetComponent::Enable(Enable);

	if (!m_Collider)
		return;
	Collider_Shape Shape = m_Collider->GetColliderShape();
	switch (Shape)
	{
	case Collider_Shape::Box2D:
	{
		m_ColliderRadius->Enable(false);
		break;
	}
	case Collider_Shape::Circle:
	{
		m_ColliderLengthX->Enable(false);
		m_ColliderLengthY->Enable(false);
		break;
	}
	case Collider_Shape::Pixel:
	{
		m_ColliderLengthX->Enable(false);
		m_ColliderLengthY->Enable(false);
		m_ColliderRadius->Enable(false);
		break;
	}
	}
}

void CIMGUICollider2DComponent::InputLength()
{
	float X = m_ColliderLengthX->GetValueFloat();
	float Y = m_ColliderLengthY->GetValueFloat();

	((CColliderBox2D*)m_Collider)->SetExtent(X, Y);
}

void CIMGUICollider2DComponent::InputRadius()
{
	float Radius = m_ColliderRadius->GetValueFloat();
	((CColliderCircle*)m_Collider)->SetRadius(Radius);
}

void CIMGUICollider2DComponent::ProfileComboCallback(int SelectIndex, const char* Item)
{
	m_Collider->SetCollisionProfile(Item);
	m_ColliderProfileCombo->SetPrevName(Item);
}


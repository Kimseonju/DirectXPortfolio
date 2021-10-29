#include "pch.h"
#include "PrefabWindow.h"
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
CPrefabWindow::CPrefabWindow()
{
}

CPrefabWindow::~CPrefabWindow()
{
	
}

bool CPrefabWindow::Init()
{
	m_ObjListBox = AddWidget<CIMGUIListBox>("ObjectListBox", 300.f, 100.f);

	m_ObjListBox->SetSelectCallback<CPrefabWindow>(this, &CPrefabWindow::ListCallback);
	m_ObjListBox->SetBorder(false);
	return true;
}

void CPrefabWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
	m_ObjListBox->Clear();
	for (size_t i = 0; i < m_VecPrefab.size(); i++)
	{
		m_ObjListBox->AddItem(m_VecPrefab[i]->GetName().c_str());
	}
}

void CPrefabWindow::ListCallback(int SelectIndex, const char* Item)
{
	m_SelectPrefab = m_VecPrefab[SelectIndex];
}

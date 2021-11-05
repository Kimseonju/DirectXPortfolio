#include "pch.h"
#include "IMGUITileCollisionCmponent.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "IMGUITabBar.h"
#include "IMGUITabItem.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Scene/SceneResource.h"
#include "GameObject.h"
#include "Component/TileMapComponent.h"
#include <IMGUIImageButton.h>
#include <IMGUITabItemEnd.h>

#include "PathManager.h"
#include "IMGUIImage.h"
CIMGUITileCollisionCmponent::CIMGUITileCollisionCmponent()
{
}

CIMGUITileCollisionCmponent::~CIMGUITileCollisionCmponent()
{
}


bool CIMGUITileCollisionCmponent::Init()
{
	CIMGUIWidgetComponent::Init();
	CIMGUIText* Text;
	CIMGUISameLine* SameLine;

	return true;
}

void CIMGUITileCollisionCmponent::Update(float DeltaTime)
{
}


#include "Ability.h"
#include "UI/Image.h"
#include "UI/Button.h"
#include "UI/Text.h"
#include <Device.h>
#include "InventoryButton.h"
#include <Scene/SceneManager.h>

#include "../Object/ShortSword.h"
#include "../Object/MetalBoomerang.h"
#include "../Object/Item.h"
CAbility::CAbility()
{
}

CAbility::CAbility(const CAbility& widget) :
	CWidgetWindow(widget)
{
}

CAbility::~CAbility()
{
}

bool CAbility::Init()
{
	CWidgetWindow::Init();

	return true;
}

void CAbility::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

}

void CAbility::PostUpdate(float DeltaTime)
{
	CWidgetWindow::PostUpdate(DeltaTime);
}

void CAbility::Render()
{
	CWidgetWindow::Render();
}

CAbility* CAbility::Clone()
{
	return new CAbility(*this);
}


#pragma once
#include "IMGUIWidgetComponent.h"
#include <IMGUIImageButton.h>
#include <IMGUITabItem.h>
class CIMGUITileCollisionCmponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUITileCollisionCmponent();
	virtual ~CIMGUITileCollisionCmponent();

private:

	CIMGUITabItem* m_TileMapTabItem;
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
public:

	CIMGUITabItem* GetTabItem()
	{
		return m_TileMapTabItem;
	}

};

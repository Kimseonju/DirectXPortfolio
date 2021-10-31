#pragma once
#include "IMGUIWidgetComponent.h"
#include <IMGUIImageButton.h>
#include <IMGUITabItem.h>
class CIMGUITileComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUITileComponent();
	virtual ~CIMGUITileComponent();

private:
	CIMGUIImageButton* m_ImageButton;
	Vector2		m_ImageFrame;


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	CIMGUITabItem* m_TileMapTabItem;
public:

	Vector2 GetImageFrame()	const
	{
		return m_ImageFrame;
	}

	CIMGUITabItem* GetTabItem()
	{
		return m_TileMapTabItem;
	}
public:
	void SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTexture(class CTexture* Texture);
	void SetFrameMax(int x, int y);
private:
	void ImageButton();
	void TestButtonClick();
};

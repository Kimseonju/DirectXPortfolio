#pragma once

#include "IMGUIWindow.h"
#include <IMGUIImageButton.h>

class CTileWindow :
	public CIMGUIWindow
{
public:
	CTileWindow();
	virtual ~CTileWindow();
private:
	CIMGUIImageButton* m_ImageButton;
	Vector2		m_ImageFrame;
	
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

	Vector2 GetImageFrame()	const
	{
		return m_ImageFrame;
	}

private:
	void ImageButton();
	void TestButtonClick();
	void ListCallback(int SelectIndex, const char* Item);
};


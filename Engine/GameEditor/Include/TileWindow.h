#pragma once

#include "IMGUIWindow.h"

class CTileWindow :
	public CIMGUIWindow
{
public:
	CTileWindow();
	virtual ~CTileWindow();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void TestButtonClick();
	void ListCallback(int SelectIndex, const char* Item);
};


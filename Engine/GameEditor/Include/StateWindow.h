#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
class CStateWindow :
	public CIMGUIWindow
{
public:
	CStateWindow();
	virtual ~CStateWindow();

private:

	class CIMGUIRadioButton* m_MosueStateRadioButton;
	class CIMGUIText* m_FPS;
public:
public:

	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void MouseRadioCallback(int SelectIndex, const char* Item);
};

#pragma once
#include "IMGUIWindow.h"
#include "GameObject.h"
class CSaveLoadWindow :
	public CIMGUIWindow
{
public:
	CSaveLoadWindow();
	virtual ~CSaveLoadWindow();

private:

	class CIMGUIButton* m_SaveButton;
	class CIMGUIButton* m_LoadButton;
	class CIMGUIButton* m_ClientSaveButton;
public:
public:

	virtual bool Init();
	virtual void Update(float DeltaTime);

public:


	void SaveButton();
	void Save(const TCHAR* FullPath);
	void LoadButton();
	void Load(const TCHAR* FullPath);
	void ClientSaveButton();
	void ClientSave(const TCHAR* FullPath);
};

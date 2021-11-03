#include "pch.h"
#include "SaveLoadWindow.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIRadioButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "ObjectWindow.h"
#include "TileMapToolWindow.h"
#include "IMGUIManager.h"

#include "IMGUITransformComponent.h"
#include "IMGUISpriteComponent.h"
#include "IMGUICollider2DComponent.h"
#include "IMGUICameraComponent.h"
#include "Editor.h"
#include "GlobalValue.h"
#include "IMGUITileMapComponent.h"
CSaveLoadWindow::CSaveLoadWindow()
{
}

CSaveLoadWindow::~CSaveLoadWindow()
{

}

bool CSaveLoadWindow::Init()
{
	m_SaveButton = AddWidget<CIMGUIButton>("SaveButton");
	m_SaveButton->SetText("Save");
	m_SaveButton->SetClickCallback<CSaveLoadWindow>(this, &CSaveLoadWindow::SaveButton);
	CIMGUISameLine* SameLine = AddWidget<CIMGUISameLine>("SameLine");

	m_LoadButton = AddWidget<CIMGUIButton>("LoadButton");
	m_LoadButton->SetText("Load");
	m_LoadButton->SetClickCallback<CSaveLoadWindow>(this, &CSaveLoadWindow::LoadButton);
	SameLine = AddWidget<CIMGUISameLine>("SameLine");


	m_ClientSaveButton = AddWidget<CIMGUIButton>("ClientSaveButton");
	m_ClientSaveButton->SetText("ClientSave");
	m_ClientSaveButton->SetClickCallback<CSaveLoadWindow>(this, &CSaveLoadWindow::ClientSaveButton);

	return true;
}

void CSaveLoadWindow::Update(float DeltaTime)
{
	CIMGUIWindow::Update(DeltaTime);
}

void CSaveLoadWindow::SaveButton()
{

	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(FALSE, TEXT("*.txt"), TEXT(""), OFN_OVERWRITEPROMPT,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();
		Save(Path);
	}

}

void CSaveLoadWindow::Save(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};
#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "wb");

	if (!pFile)
		return;

	CObjectWindow* objWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	CTileMapToolWindow* TielMapToolWindow = (CTileMapToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("TileMapToolWindow");
	CIMGUITileMapComponent* TileMapComponent = TielMapToolWindow->GetTileMapComponent();
	objWindow->SaveAllObject(pFile);
	TileMapComponent->SaveTile(pFile);

	fclose(pFile);
}

void CSaveLoadWindow::LoadButton()
{
	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(TRUE, TEXT("*.txt"), TEXT(""), OFN_HIDEREADONLY,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();
		Load(Path);
	}


}

void CSaveLoadWindow::Load(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "rb");

	if (!pFile)
		return;


	CObjectWindow* objWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	CTileMapToolWindow* TielMapToolWindow = (CTileMapToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("TileMapToolWindow");
	CIMGUITileMapComponent* TileMapComponent = TielMapToolWindow->GetTileMapComponent();
	objWindow->LoadAllObject(pFile);
	TileMapComponent->LoadTile(pFile);
	//Load(pFile);


	fclose(pFile);
}

void CSaveLoadWindow::ClientSaveButton()
{
	static TCHAR Filter[] = TEXT("텍스트 파일(*.txt)|*.txt|모든파일(*.*)|*.*||");
	CFileDialog	dlg(FALSE, TEXT("*.txt"), TEXT(""), OFN_OVERWRITEPROMPT,
		Filter);

	if (dlg.DoModal() == IDOK)
	{
		CString	Path = dlg.GetPathName();
		ClientSave(Path);
	}
}

void CSaveLoadWindow::ClientSave(const TCHAR* FullPath)
{
	char	FullPathMultibyte[MAX_PATH] = {};
#ifdef UNICODE

	int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FullPath, -1, nullptr, 0, nullptr, nullptr);
	WideCharToMultiByte(CP_ACP, 0, FullPath, -1, FullPathMultibyte, ConvertLength, nullptr, nullptr);

#else

	strcpy_s(FullPathMultibyte, FullPath);

#endif // UNICODE

	FILE* pFile = nullptr;

	fopen_s(&pFile, FullPathMultibyte, "wb");

	if (!pFile)
		return;

	CObjectWindow* objWindow = (CObjectWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("ObjectWindow");
	CTileMapToolWindow* TielMapToolWindow = (CTileMapToolWindow*)CIMGUIManager::GetInst()->FindIMGUIWindow("TileMapToolWindow");
	CIMGUITileMapComponent* TileMapComponent = TielMapToolWindow->GetTileMapComponent();
	objWindow->ClientSaveObject(pFile);
	TileMapComponent->SaveTile(pFile);

	fclose(pFile);
}

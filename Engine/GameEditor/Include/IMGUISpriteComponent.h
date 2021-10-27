#pragma once
#include "IMGUIWidgetComponent.h"
#include "Component/SpriteComponent.h"

class CIMGUISpriteComponent :
	public CIMGUIWidgetComponent
{
public:
	CIMGUISpriteComponent();
	virtual ~CIMGUISpriteComponent();

private:
	
	class CIMGUIText* m_MaterialName;
	class CIMGUIComboBox* m_TextureCombo;
	class CIMGUIButton* m_LoadTextureButton;

	class CIMGUIText* m_Animation2DName;
	class CIMGUIButton* m_LoadAnimation2DButton;
	class CIMGUIButton* m_Animation2DInfoButton;
	CSpriteComponent* m_Sprite;

public:

	virtual bool Init();
	virtual void Update(float DeltaTime);
	
public:
	void InfoUpdate(CSpriteComponent* Sprite);
	void SetMaterialName(const std::string& Name);
	void TextureComboCallback(int SelectIndex, const char* Item);

	void LoadTextureButtonClick();
	void LoadAnimation2DButtonClick();
	void Animation2DInfoButtonClick();


};


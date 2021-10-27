#include "pch.h"
#include "IMGUISpriteComponent.h"
#include "TestWindow.h"
#include "IMGUIButton.h"
#include "IMGUIConsole.h"
#include "IMGUISameLine.h"
#include "IMGUILabel.h"
#include "IMGUIText.h"
#include "IMGUIListBox.h"
#include "IMGUIComboBox.h"
#include "IMGUITextInput.h"
#include "ObjectWindow.h"
#include "IMGUIManager.h"
#include "Resource/ResourceManager.h"
CIMGUISpriteComponent::CIMGUISpriteComponent()
{
}

CIMGUISpriteComponent::~CIMGUISpriteComponent()
{
}
bool CIMGUISpriteComponent::Init()
{
	CIMGUIText* Text = m_Owner->AddWidget<CIMGUIText>("위치");
	m_vecWidget.push_back(Text);
	Text->SetFont("DefaultFont");

	Text = m_Owner->AddWidget<CIMGUIText>("Text_Title", 100.f, 20.f);
	m_vecWidget.push_back(Text);
	Text->SetText("SpriteComponent");

#pragma region Material


	Text = m_Owner->AddWidget<CIMGUIText>("Text_Material", 100.f, 20.f);
	m_vecWidget.push_back(Text);
	Text->SetText("Material");
	CIMGUISameLine* SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_MaterialName = m_Owner->AddWidget<CIMGUIText>("##MaterialName", 100.f, 20.f);
	m_vecWidget.push_back(m_MaterialName);

#pragma endregion

#pragma region Texture

	Text = m_Owner->AddWidget<CIMGUIText>("Text_Texture", 100.f, 20.f);
	Text->SetText("Texture");
	m_vecWidget.push_back(Text);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_TextureCombo = m_Owner->AddWidget<CIMGUIComboBox>("##TextureCombo", 100.f, 20.f);
	m_vecWidget.push_back(m_TextureCombo);
	m_TextureCombo->SetSelectCallback<CIMGUISpriteComponent>(this, &CIMGUISpriteComponent::TextureComboCallback);

	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_LoadTextureButton = m_Owner->AddWidget<CIMGUIButton>("LoadTexture", 100.f, 20.f);
	m_vecWidget.push_back(m_LoadTextureButton);
	m_LoadTextureButton->SetFont("DefaultFont");
	m_LoadTextureButton->SetClickCallback<CIMGUISpriteComponent>(this, &CIMGUISpriteComponent::LoadTextureButtonClick);
#pragma endregion

#pragma region Animation

	Text = m_Owner->AddWidget<CIMGUIText>("Text_Texture", 100.f, 20.f);
	m_vecWidget.push_back(Text);
	Text->SetText("Animation");
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_Animation2DName = m_Owner->AddWidget<CIMGUIText>("##TextureName", 100.f, 20.f);
	m_vecWidget.push_back(m_Animation2DName);

	m_LoadAnimation2DButton = m_Owner->AddWidget<CIMGUIButton>("LoadAnimation", 100.f, 20.f);
	m_vecWidget.push_back(m_LoadAnimation2DButton);
	m_LoadAnimation2DButton->SetFont("DefaultFont");
	m_LoadAnimation2DButton->SetClickCallback<CIMGUISpriteComponent>(this, &CIMGUISpriteComponent::LoadAnimation2DButtonClick);
	SameLine = m_Owner->AddWidget<CIMGUISameLine>("SameLine");
	m_vecWidget.push_back(SameLine);

	m_Animation2DInfoButton = m_Owner->AddWidget<CIMGUIButton>("AnimationInfo", 100.f, 20.f);
	m_vecWidget.push_back(m_Animation2DInfoButton);
	m_Animation2DInfoButton->SetFont("DefaultFont");
	m_Animation2DInfoButton->SetClickCallback<CIMGUISpriteComponent>(this, &CIMGUISpriteComponent::Animation2DInfoButtonClick);

#pragma endregion

	return true;
}

void CIMGUISpriteComponent::Update(float DeltaTime)
{
}

void CIMGUISpriteComponent::InfoUpdate(CSpriteComponent* Sprite)
{
	m_Sprite = Sprite;
	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	m_MaterialName->SetText(SpriteMtrl->GetName().c_str());
	SpriteMtrl->AddTexture("PlayerTex", TEXT("teemo.png"));
	Enable(true);
}

void CIMGUISpriteComponent::SetMaterialName(const std::string& Name)
{
}

void CIMGUISpriteComponent::TextureComboCallback(int SelectIndex, const char* Item)
{
	//텍스트설정 

	CSharedPtr<CMaterial>   SpriteMtrl = m_Sprite->GetMaterial(0);
	CTexture* Texture = CResourceManager::GetInst()->FindTexture(Item);
	SpriteMtrl->AddTexture(Item, Texture);
}

void CIMGUISpriteComponent::LoadTextureButtonClick()
{
	m_TextureCombo->DeleteAllItem();
	std::unordered_map<std::string, class CTexture*>& MapTexture = CResourceManager::GetInst()->GetMapTexture();
	auto iter = MapTexture.begin();
	auto iterEnd = MapTexture.end();
	for (; iter != iterEnd; ++iter)
	{
		m_TextureCombo->AddItem(iter->first.c_str());
	}

}

void CIMGUISpriteComponent::LoadAnimation2DButtonClick()
{
}

void CIMGUISpriteComponent::Animation2DInfoButtonClick()
{
}

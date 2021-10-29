#pragma once
#include "IMGUIWidget.h"
#include "Resource/Texture.h"
class CIMGUIImageButton :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIImageButton();
	virtual ~CIMGUIImageButton();

protected:
	std::function<void()>	m_ClickCallback;
	bool					m_Click;
	CSharedPtr<CTexture> m_Texture;
	Vector2 m_Size;
	Vector2 m_SelectImageIdx;
	wchar_t	m_Text[1024];
	char	m_TextUTF8[1024];
	bool	m_Align;
public:

	void SetAlign(bool Align)
	{
		m_Align = Align;
	}

	void SetImageSize(Vector2& Size)
	{
		m_Size = Size;
	}
	void SetImageSize(float x, float y)
	{
		m_Size = Vector2(x, y);
	}
public:
	void SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTexture(class CTexture* Texture);
public:
	virtual bool Init();
	virtual void Render();

};

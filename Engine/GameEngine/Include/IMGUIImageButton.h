#pragma once
#include "IMGUIWidget.h"
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
	class CTexture* m_Image;
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

	void SetImage(CTexture* Image)
	{
		m_Image = Image;
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
	virtual bool Init();
	virtual void Render();

};

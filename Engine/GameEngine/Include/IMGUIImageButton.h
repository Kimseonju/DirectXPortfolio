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
	CSharedPtr<CTexture> m_Texture;
	Vector2		m_Size;
	Vector2     m_TileImageSize;
	Vector2		m_SelectImageFrame;
	ImVec2		m_UVStart;
	ImVec2		m_UVEnd;
	ImVec4		m_Tint;
	ImVec4		m_BorderColor;
	int			m_FrameMaxX;
	int			m_FrameMaxY;

	wchar_t	m_Text[1024];
	char	m_TextUTF8[1024];
	bool	m_Align;
public:

	void SetFrameMax(int x, int y);
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

	void SetStartUV(float x, float y)
	{
		m_UVStart = ImVec2(x, y);
	}

	void SetEndUV(float x, float y)
	{
		m_UVEnd = ImVec2(x, y);
	}

	void SetTint(float r, float g, float b, float a)
	{
		m_Tint = ImVec4(r, g, b, a);
	}

	void SetBorderColor(float r, float g, float b, float a)
	{
		m_BorderColor = ImVec4(r, g, b, a);
	}

public:
	Vector2 GetImageFrame() const
	{
		return m_SelectImageFrame;
	}
public:
	void SetTexture(const std::string& Name, const TCHAR* FileName,
		const std::string& PathName = TEXTURE_PATH);
	void SetTextureFullPath(const std::string& Name, const TCHAR* FullPath);
	void SetTexture(class CTexture* Texture);
public:
	virtual bool Init();
	virtual void Render();
public:
	template <typename T>
	void SetClickCallback(T* pObj, void(T::* pFunc)())
	{
		m_ClickCallback = std::bind(pFunc, pObj);
	}
};

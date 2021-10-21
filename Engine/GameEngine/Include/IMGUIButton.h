#pragma once
#include "IMGUIWidget.h"
class CIMGUIButton :
	public CIMGUIWidget
{
	friend class CIMGUIWindow;

protected:
	CIMGUIButton();
	virtual ~CIMGUIButton();

protected:
	std::function<void()>	m_ClickCallback;
	bool					m_Click;

	wchar_t	m_Text[1024];
	char	m_TextUTF8[1024];
	bool	m_Align;
public:
	void SetText(const char* Text)
	{
		// ��ȯ�� ���ڿ� ���� ���´�.
		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, m_Text, Length);

		// UTF8�� ��ȯ�Ѵ�.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, m_TextUTF8, Length, 0, 0);
	}

	void AddText(const char* Text)
	{
		// ��ȯ�� ���ڿ� ���� ���´�.
		wchar_t	WideText[1024] = {};
		int	Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
		MultiByteToWideChar(CP_ACP, 0, Text, -1, WideText, Length);
		lstrcat(m_Text, WideText);

		// UTF8�� ��ȯ�Ѵ�.
		Length = WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, 0, 0, 0, 0);
		WideCharToMultiByte(CP_UTF8, 0, m_Text, -1, m_TextUTF8, Length, 0, 0);
	}

	void SetAlign(bool Align)
	{
		m_Align = Align;
	}
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

#pragma once
#include "IMGUIWindow.h"

//���� ������
//�ٲ�� Ÿ��
//����Ÿ��
//LT
//Size
//�̸�
//����
class CAnimation2DWindow :
	public CIMGUIWindow
{
public:
	CAnimation2DWindow();
	virtual ~CAnimation2DWindow();

private:
	class CIMGUIText* m_AnimationName;

	class CIMGUITextInput* m_InputFrameIdx;
	class CIMGUITextInput* m_InputFrameTime;

	class CIMGUITextInput* m_Loop;

	class CIMGUIButton* m_LoadAnimationButton;
	void SetAnimationName(const std::string& Name);
	void SetFrameIdx(float Idx);
	void SetFrameTime(float Time);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

public:
	void InputFrameIdx();
	void InpuFrameTime();
public:
};

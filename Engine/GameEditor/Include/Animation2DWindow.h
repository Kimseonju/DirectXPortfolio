#pragma once
#include "IMGUIWindow.h"

//현재 프레임
//바뀌는 타임
//현재타임
//LT
//Size
//이름
//루프
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

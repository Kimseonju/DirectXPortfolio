#pragma once

#include "../Ref.h"
#include "AnimationSequence2D.h"

struct UISequence2DInfo
{
	CSharedPtr<CAnimationSequence2D>	Sequence;
	bool				Loop;
	float				PlayRate;

	UISequence2DInfo() :
		Loop(true),
		PlayRate(1.f)
	{
	}
};

//공유를 하지않지만 일단 Ref함
//하나만들어지면 하나 100개 만들어지면 100개만들어야댐
//따로 노는 객체
class CUIAnimation2D :
	public CRef
{
protected:
	CUIAnimation2D();
	CUIAnimation2D(const CUIAnimation2D& anim);
	virtual ~CUIAnimation2D();

protected:
	class CScene* m_pScene;
	class CUIAnimation2DConstantBuffer* m_pCBuffer;
	std::unordered_map<std::string, UISequence2DInfo*>	m_mapSequence;
	UISequence2DInfo* m_CurrentSequence;
	float		m_FrameTime;
	float		m_Frame;
	bool m_End;
protected:
	std::function<void(const std::string&)>	m_FrameEndFunction;

public:
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	std::string GetCurrentSequenceName()	const
	{
		return m_CurrentSequence->Sequence->GetName();
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CUIAnimation2D* Clone();
	void SetShader();
	void ResetShader();

public:
	void AddAnimationSequence2D(const std::string& Name, bool Loop = true);
	void AddAnimationSequence2D(CAnimationSequence2D* Sequence, bool Loop = true);
	void SetSequencePlayRate(const std::string& Name, float PlayRate);
	void AddSequencePlayRate(const std::string& Name, float PlayRate);
	void ChangeAnimation(const std::string& Name);
	void ChangeAnimation(UISequence2DInfo* Info);

	bool GetFrameEnd()
	{
		return m_End;
	}
protected:
	UISequence2DInfo* FindSequence(const std::string& Name);

public:
	template <typename T>
	void SetFrameEndFunction(T* pObj, void(T::* pFunc)(const std::string&))
	{
		m_FrameEndFunction = std::bind(pFunc, pObj, std::placeholders::_1);
	}

};


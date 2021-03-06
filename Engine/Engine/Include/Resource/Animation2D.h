#pragma once

#include "../Ref.h"
#include "AnimationSequence2D.h"

struct Sequence2DInfo
{
	CSharedPtr<CAnimationSequence2D>	Sequence;
	bool				Loop;
	float				PlayRate;

	Sequence2DInfo() :
		Loop(true),
		PlayRate(1.f)
	{
	}
};

//공유를 하지않지만 일단 Ref함
//하나만들어지면 하나 100개 만들어지면 100개만들어야댐
//따로 노는 객체
class CAnimation2D :
	public CRef
{
	friend class CSpriteComponent;
	friend class CMouseWidget;
	friend class CImage;
protected:
	CAnimation2D();
	CAnimation2D(const CAnimation2D& anim);
	virtual ~CAnimation2D();

protected:
	class CScene* m_pScene;
	class CSpriteComponent* m_Owner;
	class CWidget* m_OwnerWidget;
	class CAnimation2DConstantBuffer* m_pCBuffer;
	std::unordered_map<std::string, Sequence2DInfo*>	m_mapSequence;
	Sequence2DInfo* m_CurrentSequence;
	float		m_FrameTime;
	int		m_Frame;
	bool	m_End;
	bool	m_Play;
protected:
	std::function<void(const std::string&)>	m_FrameEndFunction;

public:

	void StopPlay()
	{
		m_Play = false;
	}
	void Play()
	{
		m_Play = true;
	}

	std::unordered_map<std::string, Sequence2DInfo*>& GetMapSequence()
	{
		return m_mapSequence;
	}
	void SetScene(class CScene* pScene)
	{
		m_pScene = pScene;
	}

	void SetOwner(class CSpriteComponent* Owner)
	{
		m_Owner = Owner;
	}

	void SetOwner(class CWidget* Owner)
	{
		m_OwnerWidget = Owner;
	}

	std::string GetCurrentSequenceName()	const
	{
		return m_CurrentSequence->Sequence->GetName();
	}
	int GetFrame()
	{
		return m_Frame;
	}

	int GetFrameSize()
	{
		return (int)m_CurrentSequence->Sequence->m_vecAnimFrame.size();
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CAnimation2D* Clone();
	void SetShader();
	void ResetShader();
	virtual bool IsEnable();
public:
	Sequence2DInfo* AddAnimationSequence2D(const std::string& Name, bool Loop = true);
	Sequence2DInfo* AddAnimationSequence2D(CAnimationSequence2D* Sequence, bool Loop = true);
	void SetSequencePlayRate(const std::string& Name, float PlayRate);
	void AddSequencePlayRate(const std::string& Name, float PlayRate);
	void ChangeAnimation(const std::string& Name);
	void ChangeAnimation(Sequence2DInfo* Info);

	bool GetFrameEnd()
	{
		return m_End;
	}
public:
public:
	void Animation2DRestart();
public:
	Sequence2DInfo* FindSequence(const std::string& Name);
	Sequence2DInfo* FindSequence(CAnimationSequence2D* Sequence);

public:
	template <typename T>
	void SetFrameEndFunction(T* pObj, void(T::* pFunc)(const std::string&))
	{
		m_FrameEndFunction = std::bind(pFunc, pObj, std::placeholders::_1);
	}

};


#pragma once
#include "../Ref.h"
#include "Texture.h"

struct Animation2DFrame
{
	Vector2		Start;
	Vector2		End;
};

struct Animation2DNotify :
	public CRef
{
	std::string		Name;
	class CAnimationSequence2D* pOwner;
	int				Frame;
	bool			Call;

	Animation2DNotify()
	{
		Call = false;
	}
};
//시퀀스 하나가 모션 하나를 표현한다.
class CAnimationSequence2D :
	public CRef
{
	friend class CResourceManager;
	friend class CSceneResource;
	friend class CAnimation2D;
	friend class CUIAnimation2D;

private:
	CAnimationSequence2D();
	CAnimationSequence2D(const CAnimationSequence2D& Sequence);
	~CAnimationSequence2D();

private:
	class CScene* m_pScene;
	CSharedPtr<CTexture>    m_Texture;
	Animation2D_Type         m_Type;
	bool					m_Loop;
	float                   m_PlayRate;
	float					m_PlayTime;
	float					m_FrameTime;
	std::vector<Animation2DFrame>	m_vecAnimFrame;
	//몇프레임때 총알발사등
	std::vector<CSharedPtr<Animation2DNotify>> m_vecNotify;

public:
	Animation2D_Type GetAnimation2DType()	const
	{
		return m_Type;
	}

	const Animation2DFrame& GetAnimation2DFrame(int Index = 0)	const
	{
		return m_vecAnimFrame[Index];
	}

	Animation2DFrame GetAnimation2DFrameUV(int Index)	const
	{
		Animation2DFrame	Frame = {};

		unsigned int Width = m_Texture->GetWidth();
		unsigned int Height = m_Texture->GetHeight();

		Frame.Start = m_vecAnimFrame[Index].Start / Vector2((float)Width, (float)Height);
		Frame.End = m_vecAnimFrame[Index].End / Vector2((float)Width, (float)Height);
		
		return Frame;
	}

public:
	void SetTexture(CTexture* pTexture);
	void SetPlayTime(float PlayTime);
	void SetPlayRate(float PlayRate);
	void AddFrame(const Vector2& Start, const Vector2& End);
	void AddFrame(const Vector2& Start, const Vector2& End, int Count);
	void AddNotify(const std::string& Name, int Frame);
	CAnimationSequence2D* Clone();
};


	
#include "AnimationSequence2D.h"

CAnimationSequence2D::CAnimationSequence2D()	:
	m_Type(Animation2D_Type::Atlas),
	m_Loop(true),
	m_PlayRate(1.f),
	m_PlayTime(1.f),
	m_FrameTime(1.f),
	m_pScene(nullptr)	
{
}

CAnimationSequence2D::CAnimationSequence2D(const CAnimationSequence2D& Sequence)
{

	m_pScene = Sequence.m_pScene;
	m_Name = Sequence.m_Name;
	m_Texture = Sequence.m_Texture;
	m_Type = Sequence.m_Type;
	m_vecAnimFrame = Sequence.m_vecAnimFrame;
	m_PlayRate = Sequence.m_PlayRate;
	m_PlayTime = Sequence.m_PlayTime;
	m_FrameTime = Sequence.m_FrameTime;
	
	auto iter = Sequence.m_vecNotify.begin();
	auto iterEnd = Sequence.m_vecNotify.end();
	
	for (; iter != iterEnd; ++iter)
	{
		Animation2DNotify* pNotify = new Animation2DNotify;

		pNotify->Name = (*iter)->Name;
		pNotify->Frame = (*iter)->Frame;
		pNotify->pOwner = this;

		m_vecNotify.push_back(pNotify);
		pNotify->Release();
	}
	//다른곳으로 바로 복사가됨 카운트++
	m_RefCount = 0;
}

CAnimationSequence2D::~CAnimationSequence2D()
{
	m_vecNotify.clear();
}

void CAnimationSequence2D::SetTexture(CTexture* pTexture)
{
	m_Texture = pTexture;

	switch (pTexture->GetImageType())
	{
	case Image_Type::Atlas:
		m_Type = Animation2D_Type::Atlas;
		break;
	case Image_Type::Frame:
		m_Type = Animation2D_Type::Frame;
		break;
	case Image_Type::Array:
		m_Type = Animation2D_Type::Array;
		break;
	}
}

void CAnimationSequence2D::SetPlayTime(float PlayTime)
{
	m_PlayTime = PlayTime;
}

void CAnimationSequence2D::SetPlayRate(float PlayRate)
{
	m_PlayRate = PlayRate;
}

void CAnimationSequence2D::AddFrame(const Vector2& Start, const Vector2& End)
{
	Animation2DFrame	Frame;
	Frame.Start = Start;
	Frame.End = End;
	m_vecAnimFrame.push_back(Frame);

	m_FrameTime = m_PlayTime / (float)m_vecAnimFrame.size();
}

void CAnimationSequence2D::AddFrame(const Vector2& Start, const Vector2& End, int Count)
{
	m_vecAnimFrame.resize(Count);

	for (int i = 0; i < Count; ++i)
	{
		m_vecAnimFrame[i].Start = Start;
		m_vecAnimFrame[i].End = End;
	}

	m_FrameTime = m_PlayTime / (float)Count;
}

void CAnimationSequence2D::AddNotify(const std::string& Name, int Frame)
{
	Animation2DNotify* pNotify = new Animation2DNotify;

	pNotify->Name = Name;
	pNotify->Frame = Frame;
	pNotify->pOwner = this;

	m_vecNotify.push_back(pNotify);
	pNotify->Release();
}

CAnimationSequence2D* CAnimationSequence2D::Clone()
{
	return new CAnimationSequence2D(*this);
}

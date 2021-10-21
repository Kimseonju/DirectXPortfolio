#pragma once

#include "Resource/Animation2D.h"

class CEnemyShotAnimation2D :
	public CAnimation2D
{
public:
	CEnemyShotAnimation2D();
	CEnemyShotAnimation2D(const CEnemyShotAnimation2D& anim);
	virtual ~CEnemyShotAnimation2D();
protected:

	bool m_Die;

	Sequence2DInfo* m_SequenceIdle;
	Sequence2DInfo* m_SequenceMove;
	Sequence2DInfo* m_SequenceJump;
	Sequence2DInfo* m_SequenceAttack;
	Sequence2DInfo* m_SequenceDie;

public:

	void IsDie()
	{
		m_Die = true;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CEnemyShotAnimation2D* Clone();
};


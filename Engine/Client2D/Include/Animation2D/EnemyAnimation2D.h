#pragma once

#include "Resource/Animation2D.h"

class CEnemyAnimation2D :
	public CAnimation2D
{
public:
	CEnemyAnimation2D();
	CEnemyAnimation2D(const CEnemyAnimation2D& anim);
	virtual ~CEnemyAnimation2D();
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
	virtual CEnemyAnimation2D* Clone();
};


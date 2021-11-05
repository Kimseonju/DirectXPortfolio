#pragma once

#include "Resource/Animation2D.h"

class CAnimation2D_FSM :
	public CAnimation2D
{
public:
	CAnimation2D_FSM();
	CAnimation2D_FSM(const CAnimation2D_FSM& anim);
	virtual ~CAnimation2D_FSM();
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
	void SetIdleAnimation2D(const std::string& Name, bool Loop = true);
	void SetMoveAnimation2D(const std::string& Name, bool Loop = true);
	void SetJumpAnimation2D(const std::string& Name, bool Loop = true);
	void SetAttackAnimation2D(const std::string& Name, bool Loop = true);
	void SetDieAnimation2D(const std::string& Name, bool Loop = true);


	void ChangeIdleAnimation2D();
	void ChangeMoveAnimation2D();
	void ChangeJumpAnimation2D();
	void ChangeAttackAnimation2D();
	void ChangeDieAnimation2D();
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual CAnimation2D_FSM* Clone();


};


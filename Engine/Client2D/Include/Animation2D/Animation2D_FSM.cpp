#include "Animation2D_FSM.h"
#include "Component/SpriteComponent.h"
#include "Animation2D_FSM.h"

CAnimation2D_FSM::CAnimation2D_FSM() :
	m_Die(false),
	m_SequenceIdle(nullptr),
	m_SequenceMove(nullptr),
	m_SequenceJump(nullptr),
	m_SequenceAttack(nullptr),
	m_SequenceDie(nullptr)
{
}

CAnimation2D_FSM::CAnimation2D_FSM(const CAnimation2D_FSM& anim) :
	CAnimation2D(anim)
{
	m_SequenceIdle = nullptr;
	m_SequenceMove = nullptr;
	m_SequenceJump = nullptr;
	m_SequenceAttack = nullptr;
	m_SequenceDie = nullptr;
	m_Die = false;
}

CAnimation2D_FSM::~CAnimation2D_FSM()
{
}

void CAnimation2D_FSM::Start()
{
	CAnimation2D::Start();
}

bool CAnimation2D_FSM::Init()
{
	if (!CAnimation2D::Init())
		return false;

	return true;
}

void CAnimation2D_FSM::Update(float DeltaTime)
{
	CAnimation2D::Update(DeltaTime);
}

CAnimation2D_FSM* CAnimation2D_FSM::Clone()
{
	return new CAnimation2D_FSM(*this);
}

void CAnimation2D_FSM::SetIdleAnimation2D(const std::string& Name, bool Loop)
{
	m_SequenceIdle =AddAnimationSequence2D(Name, Loop);
}

void CAnimation2D_FSM::SetMoveAnimation2D(const std::string& Name, bool Loop)
{
	m_SequenceMove = AddAnimationSequence2D(Name, Loop);
}

void CAnimation2D_FSM::SetJumpAnimation2D(const std::string& Name, bool Loop)
{
	m_SequenceJump = AddAnimationSequence2D(Name, Loop);
}

void CAnimation2D_FSM::SetAttackAnimation2D(const std::string& Name, bool Loop)
{
	m_SequenceAttack = AddAnimationSequence2D(Name, Loop);
}

void CAnimation2D_FSM::SetDieAnimation2D(const std::string& Name, bool Loop)
{
	m_SequenceDie = AddAnimationSequence2D(Name, Loop);
}

void CAnimation2D_FSM::ChangeIdleAnimation2D()
{
	ChangeAnimation(m_SequenceIdle);
}

void CAnimation2D_FSM::ChangeMoveAnimation2D()
{
	ChangeAnimation(m_SequenceMove);
}

void CAnimation2D_FSM::ChangeJumpAnimation2D()
{
	ChangeAnimation(m_SequenceJump);
}

void CAnimation2D_FSM::ChangeAttackAnimation2D()
{
	ChangeAnimation(m_SequenceAttack);
	
}

void CAnimation2D_FSM::ChangeDieAnimation2D()
{
	ChangeAnimation(m_SequenceDie);
}

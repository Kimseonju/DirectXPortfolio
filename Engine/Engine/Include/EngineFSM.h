#pragma once
#include <map>
#include "Timer.h"
#include "Engine.h"


template<typename EventTarget>
class CEngineFSM
{
	class State
	{
	public:
		EventTarget* m_Obj;
		void(EventTarget::* m_StartFunc)();
		void(EventTarget::* m_EndFunc)();
		void(EventTarget::* m_StayFunc)();

	public:
		void Start()
		{
			if (nullptr == m_StartFunc)
			{
				return;
			}
			(m_Obj->*m_StartFunc)();
		}


		void End()
		{
			if (nullptr == m_EndFunc)
			{
				return;
			}
			(m_Obj->*m_EndFunc)();
		}

		void Update()
		{
			if (nullptr == m_StayFunc)
			{
				return;
			}
			(m_Obj->*m_StayFunc)();
		}

	public:
		State() :m_Obj(nullptr), m_StartFunc(nullptr), m_EndFunc(nullptr), m_StayFunc(nullptr)
		{
		}
		~State()
		{
		}



	};



private:
	std::map<std::string, State>m_State;
	State* m_CurState;


public:
	void CreateState(std::string _StateName, 
		EventTarget* _Obj,
		void(EventTarget::* _StayFunc)(),
		void(EventTarget::* _StartFunc)() = nullptr, 
		void(EventTarget::* _EndFunc)() = nullptr)
	{

		if (m_State.end() != m_State.find(_StateName))
		{
			return;
		}

		m_State[_StateName].m_Obj = _Obj;
		m_State[_StateName].m_StartFunc = _StartFunc;
		m_State[_StateName].m_EndFunc = _EndFunc;
		m_State[_StateName].m_StayFunc = _StayFunc;
	}

	void ChangeState(std::string _StateName)
	{
		if (m_State.end() == m_State.find(_StateName))
		{
			return;
		}
		if (nullptr != m_CurState)
		{
			m_CurState->End();
		}
		m_CurState = &m_State[_StateName];
		m_CurState->Start();
	}

	void Update()
	{
		if (nullptr == m_CurState)
		{
			return;
		}
		m_CurState->Update();
	}

public:
	CEngineFSM() :m_CurState(nullptr) {}
	~CEngineFSM() {}
};
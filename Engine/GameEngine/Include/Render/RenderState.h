#pragma once

#include "../GameEngine.h"

class CRenderState
{
	friend class CRenderStateManager;

protected:
	CRenderState();
	virtual ~CRenderState();

protected:
	RenderState_Type	m_Type;
	ID3D11DeviceChild* m_State;
	ID3D11DeviceChild* m_PrevState;

public:
	RenderState_Type GetType()	const
	{
		return m_Type;
	}

public:
	virtual void SetState() = 0;
	virtual void ResetState() = 0;
};

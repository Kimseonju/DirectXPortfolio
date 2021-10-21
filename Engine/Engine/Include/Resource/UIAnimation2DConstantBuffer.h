#pragma once
#include "ConstantBufferData.h"
class CUIAnimation2DConstantBuffer :
	public CConstantBufferData
{
public:
	CUIAnimation2DConstantBuffer();
	CUIAnimation2DConstantBuffer(const CUIAnimation2DConstantBuffer& buffer);
	virtual ~CUIAnimation2DConstantBuffer();

protected:
	UIAnimation2DCBuffer    m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CUIAnimation2DConstantBuffer* Clone();

public:
	void SetAnimation2DType(Animation2D_Type Type)
	{
		m_BufferData.Animation2DType = (int)Type;
	}

	void SetStartUV(const Vector2& UV)
	{
		m_BufferData.StartUV = UV;
	}

	void SetEndUV(const Vector2& UV)
	{
		m_BufferData.EndUV = UV;
	}

};


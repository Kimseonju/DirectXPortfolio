#pragma once
#include "ConstantBufferData.h"
class CMiniMapCBuffer :
	public CConstantBufferData
{
public:
	CMiniMapCBuffer();
	CMiniMapCBuffer(const CMiniMapCBuffer& buffer);
	virtual ~CMiniMapCBuffer();

protected:
	MiniMapCBuffer    m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CMiniMapCBuffer* Clone();

public:
	void SetSize(float x, float y)
	{
		m_BufferData.Size = Vector2(x, y);
	}

	void SetSize(const Vector2& Size)
	{
		m_BufferData.Size = Size;
	}

};



#include "MiniMapCBuffer.h"
#include "ConstantBuffer.h"

CMiniMapCBuffer::CMiniMapCBuffer() :
    m_BufferData{}
{
}

CMiniMapCBuffer::CMiniMapCBuffer(const CMiniMapCBuffer& buffer) :
    CConstantBufferData(buffer)
{
    m_BufferData = buffer.m_BufferData;
}

CMiniMapCBuffer::~CMiniMapCBuffer()
{
}

bool CMiniMapCBuffer::Init()
{
    SetConstantBuffer("MiniMapCBuffer");

    return true;
}

void CMiniMapCBuffer::UpdateCBuffer()
{
    m_pBuffer->UpdateBuffer(&m_BufferData);
}

CMiniMapCBuffer* CMiniMapCBuffer::Clone()
{
    return new CMiniMapCBuffer(*this);
}

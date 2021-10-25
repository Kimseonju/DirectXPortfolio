#pragma once
#include "GameEngine.h"

class CRef
{
protected:
	CRef();
	virtual ~CRef() = 0;

protected:
	std::string	m_Name;
	int			m_RefCount;
	bool		m_Enable;
	bool		m_Active;
public:

	virtual void Enable(bool bEnable)
	{
		m_Enable = bEnable;
	}
	virtual bool IsEnable()
	{
		return m_Enable;
	}
	virtual void Active(bool bActive)
	{
		m_Active = bActive;
	}
	bool IsActive()
	{
		return m_Active;
	}
	void SetName(const std::string& Name)
	{
		m_Name = Name;
	}

	const std::string& GetName() const
	{
		return m_Name;
	}

	int GetRefCount() const
	{
		return m_RefCount;
	}
	int AddRef();
	int Release();


};

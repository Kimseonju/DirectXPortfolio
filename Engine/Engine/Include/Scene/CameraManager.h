#pragma once

#include "../GameEngine.h"
#include "../Component/Camera.h"

//현재 선택되어있는 카메라와 UI카메라, 카메라 목록 관리
class CCameraManager
{
	friend class CScene;

private:
	CCameraManager();
	~CCameraManager();

private:
	class CScene* m_pScene;

private:
	std::list<CSharedPtr<CCamera>>	m_CameraList;
	CSharedPtr<CCamera>	m_CurrentCamera;
	CSharedPtr<CCamera>	m_UICamera;

public:
	CCamera* GetCurrentCamera()	const
	{
		return m_CurrentCamera;
	}

	CCamera* GetUICamera()	const
	{
		return m_UICamera;
	}

	void SetCurrentCamera(const std::string& Name);
	void AddCamera(CCamera* Camera);

private:
	CCamera* FindCamera(const std::string& Name);

public:
	void Start();
	bool Init();
	void Update(float DeltaTime);
	void PostUpdate(float DeltaTime);
};

#pragma once

#include "GameObject.h"
#include <Component/Camera.h>
class CEndingCamera :
	public CGameObject
{
	friend class CScene;

protected:
	CEndingCamera();
	CEndingCamera(const CEndingCamera& obj);
	virtual ~CEndingCamera();

protected:
	CSharedPtr<CCamera> m_Camera;
protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEndingCamera* Clone();
};

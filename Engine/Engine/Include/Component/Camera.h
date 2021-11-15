#pragma once

#include "SceneComponent.h"


class CCamera :
    public CSceneComponent
{
    friend class CGameObject;
	friend class CCameraManager;
	friend class CViewport;

protected:
    CCamera();
    CCamera(const CCamera& com);
    virtual ~CCamera();

protected:
	Camera_Type m_CameraType;
	Matrix  m_matView;
	Matrix  m_matProj;
	float   m_ViewAngle;
	float   m_Distance;
	float	m_CameraBottom; //2D
	float	m_CameraLeft;	//2D
	Resolution	m_RS;
	float	m_CameraZoom;

	float	m_MinX;
	float	m_MinY;

	float	m_MaxX;
	float	m_MaxY;

	std::queue<CameraShake> m_qCameraShake;

	std::queue<CameraMove> m_qCameraMove;
	float	m_ShakeTime;
	float	m_MoveTime;
	bool	m_CameraMove;
	bool	m_CameraMoveEnd;
	Vector2 m_VRS;
public:
	bool IsCameraMove() const
	{
		return m_CameraMove;
	}
	bool IsCameraMoveEnd() const
	{
		return m_CameraMoveEnd;
	}
	Vector2 GetVRS()
	{
		return m_VRS;
	}
	Vector2 GetCameraZoomSize()
	{
		Vector2 Size;
		Size.x = m_VRS.x / m_CameraZoom;
		Size.y = m_VRS .y/ m_CameraZoom;
		return Size;
	}
	void SetMin(float x, float y)
	{
		m_MinX = x;
		m_MinY = y;
	}
	void SetMinX(float x)
	{
		m_MinX = x;
	}
	void SetMinY(float y)
	{
		m_MinY = y;
	}
	void SetMax(float x, float y)
	{
		m_MaxX = x;
		m_MaxY = y;
	}
	void SetMaxX(float x)
	{
		m_MaxX = x;
	}
	void SetMaxY(float y)
	{
		m_MaxY = y;
	}
	Vector2 GetMin()
	{
		Vector2 vec2;
		vec2.x = m_MinX;
		vec2.y = m_MinY;
		return vec2;
	}
	Vector2 GetMax()
	{
		Vector2 vec2;
		vec2.x = m_MaxX;
		vec2.y = m_MaxY;
		return vec2;
	}

	float GetCameraZoom() const
	{
		return m_CameraZoom;
	}
	Resolution GetResolution()	const
	{
		return m_RS;
	}

	float GetCameraBottom() const
	{
		return m_CameraBottom;
	}

	float GetCameraLeft()	const
	{
		return m_CameraLeft;
	}

	Camera_Type GetCameraType() const
	{
		return m_CameraType;
	}

	Matrix GetViewMatrix()  const
	{
		return m_matView;
	}

	Matrix GetProjMatrix()  const
	{
		return m_matProj;
	}

public:
	void SetCameraZoom(float Zoom)
	{
		m_CameraZoom = Zoom;
		CreateProjectionMatrix();
	}

	void SetViewAngle(float Angle)
	{
		m_ViewAngle = Angle;

		if (m_CameraType == Camera_Type::Cam3D)
			CreateProjectionMatrix();
	}

	void SetDistance(float Distance)
	{
		m_Distance = Distance;

		CreateProjectionMatrix();
	}

	void SetCameraType(Camera_Type Type)
	{
		m_CameraType = Type;

		CreateProjectionMatrix();
	}

private:
	void CreateProjectionMatrix();
public:

	void AddCameraShake(float x, float y, float Time);
	void AddCameraShake(const Vector2& Pos, float Time);
	void AddCameraMove2D(float x, float y, float Time);
	void AddCameraMove2D(const Vector2& Pos, float Time);
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCamera* Clone();
};

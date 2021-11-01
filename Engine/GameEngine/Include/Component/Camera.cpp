
#include "Camera.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Device.h"

CCamera::CCamera()
{
	m_SceneComponentType = SceneComponent_Type::Camera;
	m_CameraType = Camera_Type::Cam2D;

	m_ViewAngle = 90.f;
	m_Distance = 1000.f;
	m_CameraLeft = 0.f;
	m_CameraBottom = 0.f;
	m_CameraZoom = 1.f;
	m_MinX = INT_MIN;
	m_MinY = INT_MIN;

	m_MaxX = INT_MAX;
	m_MaxY = INT_MAX;
}

CCamera::CCamera(const CCamera& com) :
	CSceneComponent(com)
{
	m_CameraType = com.m_CameraType;
	m_ViewAngle = com.m_ViewAngle;
	m_Distance = com.m_Distance;
	m_matView = com.m_matView;
	m_matProj = com.m_matProj;
	m_CameraLeft = com.m_CameraLeft;
	m_CameraBottom = com.m_CameraBottom;
}

CCamera::~CCamera()
{
}

void CCamera::CreateProjectionMatrix()
{
	Resolution  RS = CDevice::GetInst()->GetResolution();

	switch (m_CameraType)
	{
	case Camera_Type::Cam3D:
	{
		float	Angle = XMConvertToRadians(m_ViewAngle);

		m_matProj = XMMatrixPerspectiveFovLH(Angle,
			RS.Width / (float)RS.Height, 0.1f, m_Distance);
	}
		break;
	case Camera_Type::Cam2D:
	{
		float percent = (1.f / m_CameraZoom);
		Vector2 Size = { 640,320 };
		Size.x = Size.x / m_CameraZoom -640.f;
		Size.y = Size.y / m_CameraZoom -320.f;


		m_matProj = XMMatrixOrthographicOffCenterLH(-Size.x, (float)RS.Width+ Size.x,
			-Size.y, (float)RS.Height+ Size.y,
			0.f, m_Distance);
	}
		break;
	case Camera_Type::CamUI:
	{
		m_matProj = XMMatrixOrthographicOffCenterLH(0.f, (float)RS.Width, 0.f, (float)RS.Height,
			0.f, m_Distance);
	}
		break;
	}
}

void CCamera::Start()
{
	CSceneComponent::Start();

	CreateProjectionMatrix();

	m_RS = CDevice::GetInst()->GetResolution();
}

bool CCamera::Init()
{
	if (!CSceneComponent::Init())
		return false;

	return true;
}

void CCamera::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);

	Resolution  RS = CDevice::GetInst()->GetResolution();

	m_CameraBottom = GetWorldPos().y - RS.Height / 2.f;
	m_CameraLeft = GetWorldPos().x - RS.Width / 2.f;
}

void CCamera::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	m_matView.Identity();

	for (int i = 0; i < AXIS_END; ++i)
	{
		Vector3	Axis = GetAxis((AXIS)i);
		memcpy(&m_matView[i][0], &Axis, sizeof(Vector3));
	}

	// 회전부분을 전치해서 최종 View의 회전으로 만들어준다.
	m_matView.Transpose();

	for (int i = 0; i < AXIS_END; ++i)
	{
		Vector3	Axis = GetAxis((AXIS)i);
		Vector3	Pos = GetWorldPos();
		if (Pos.x < m_MinX)
		{
			Pos.x = m_MinX;
		}
		if (Pos.x > m_MaxX)
		{
			Pos.x = m_MaxX;
		}
		if (Pos.y < m_MinY)
		{
			Pos.x = m_MinY;
		}
		if (Pos.y > m_MaxY)
		{
			Pos.y = m_MaxY;
		}
		Pos = Pos * -1.f;
		//임시값 (Object에붙으면 Z알아서계산되기때문
		Pos.z = 0.f;
		m_matView[3][i] = Axis.Dot(Pos);
	}

	/* 이동
	1 0 0 0
	0 1 0 0
	0 0 1 0
	-x -y -z 1
	  뷰행렬(회전)
	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1
	  이동*회전
	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	-P.X -P.Y -P.Z 1


	WorldCameraAxisX * ViewMatrix = 1, 0, 0
	WorldCameraAxisY * ViewMatrix = 0, 1, 0
	WorldCAmeraAxisZ * ViewMatrix = 0, 0, 1

	Xx Xy Xz   Xx Yx Zx    1 0 0
	Yx Yy Yz * Xy Yy Zy = 0 1 0
	Zx Zy Zz   Xz Yz Zz    0 0 1

	서로 정직교 하는 행렬을 직교행렬이라고 한다.
	직교행렬은 전치행렬과 역행렬이 같다.
	*/
}

void CCamera::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CCamera::PrevRender(float DeltaTime)
{
	CSceneComponent::PrevRender(DeltaTime);
}

void CCamera::Render(float DeltaTime)
{
	CSceneComponent::Render(DeltaTime);
}

CCamera* CCamera::Clone()
{
	return new CCamera(*this);
}
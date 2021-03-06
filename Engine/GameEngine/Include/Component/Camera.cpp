
#include "Camera.h"
#include "../Render/RenderManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Device.h"

CCamera::CCamera()
{
	m_SceneComponentType = SceneComponent_Type::Camera;
	m_CameraType = Camera_Type::Cam2D;
	m_ComponentClassType = Component_Class_Type::Camera;

	m_ViewAngle = 90.f;
	m_Distance = 1000.f;
	m_CameraLeft = 0.f;
	m_CameraBottom = 0.f;
	m_CameraZoom = 1.f;
	m_MinX = (float)INT_MIN;
	m_MinY = (float)INT_MIN;
	m_RS = { 0,0 };
	m_MaxX = (float)INT_MAX;
	m_MaxY = (float)INT_MAX;
	m_ShakeTime = 0.f;
	m_MoveTime = 0.f;
	m_CameraMove = false;
	m_CameraMoveEnd = false;
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
	m_RS = com.m_RS;
	m_MinX = com.m_MinX;
	m_MinY = com.m_MinY;
	m_MaxX = com.m_MaxX;
	m_MaxY = com.m_MaxY;
	m_ShakeTime = com.m_ShakeTime;
	m_MoveTime = com.m_MoveTime;
	m_CameraMove = com.m_CameraMove;
	m_CameraMoveEnd = com.m_CameraMoveEnd;
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
		Resolution RS = CDevice::GetInst()->GetResolution();
		Vector2 ResolutionRatio = CDevice::GetInst()->GetResolutionRatio();
		
		if (ResolutionRatio.x == 0.f)
		{
			m_VRS.x = (float)RS.Width;
			m_VRS.y = (float)RS.Height;
		}
		else
		{
			m_VRS.x = (float)RS.Width * ResolutionRatio.x;
			m_VRS.y = (float)RS.Height * ResolutionRatio.y;
		}
		Vector2 Size = { m_VRS.x / 2.f, m_VRS.y / 2.f };
		Size.x = Size.x / m_CameraZoom - Size.x;
		Size.y = Size.y / m_CameraZoom - Size.y;

		m_matProj = XMMatrixOrthographicOffCenterLH(-Size.x, (float)m_VRS.x+ Size.x,
			-Size.y, m_VRS.y+ Size.y,
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


void CCamera::AddCameraShake(float x, float y, float Time)
{
	AddCameraShake({ x,y }, Time);
}

void CCamera::AddCameraShake(const Vector2& Pos, float Time)
{
	CameraShake Shake;
	Shake.Pos = Pos;
	Shake.Time = Time;
	m_qCameraShake.push(Shake);
}

void CCamera::CameraCurrentShakeStop()
{
	m_ShakeTime = 99999999.f;
	
}

void CCamera::AddCameraMove2D(float x, float y, float Time)
{
	AddCameraShake({ x,y }, Time);
}

void CCamera::AddCameraMove2D(const Vector2& Pos, float Time)
{
	CameraMove Move;
	Move.Pos = Pos;
	Move.WaitTime = Time;
	m_qCameraMove.push(Move);
}

void CCamera::CameraCurrentMoveStop()
{
	m_MoveTime = 99999999.f;
}


void CCamera::Save(FILE* pFile)
{
	CSceneComponent::Save(pFile);
	fwrite(&m_CameraType, sizeof(Camera_Type), 1, pFile);
	fwrite(&m_ViewAngle, sizeof(float), 1, pFile);
	fwrite(&m_Distance, sizeof(float), 1, pFile);
	fwrite(&m_CameraZoom, sizeof(float), 1, pFile);
	fwrite(&m_MinX, sizeof(float), 1, pFile);
	fwrite(&m_MinY, sizeof(float), 1, pFile);
	fwrite(&m_MaxX, sizeof(float), 1, pFile);
	fwrite(&m_MaxY, sizeof(float), 1, pFile);
}

void CCamera::Load(FILE* pFile)
{
	CSceneComponent::Load(pFile);
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
	m_CameraMove = false;
	for (int i = 0; i < AXIS_END; ++i)
	{
		Vector3	Axis = GetAxis((AXIS)i);
		memcpy(&m_matView[i][0], &Axis, sizeof(Vector3));
	}

	// ?????????? ???????? ???? View?? ???????? ??????????.
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
			Pos.y = m_MinY;
		}
		if (Pos.y > m_MaxY)
		{
			Pos.y = m_MaxY;
		}
		if (m_qCameraMove.size() != 0)
		{
			//??????
			if (m_MoveTime < m_qCameraMove.front().WaitTime)
			{
				Vector2 EndMovePos = m_qCameraMove.front().Pos;
				EndMovePos.x -= 640.f;
				EndMovePos.y -= 360.f;
				Vector2 CameraPos = Vector2(GetWorldPos().x, GetWorldPos().y);
				CameraPos = EndMovePos.Lerp2DMax(CameraPos, EndMovePos, m_MoveTime);
				Pos.x = CameraPos.x;
				Pos.y = CameraPos.y;
				m_MoveTime += DeltaTime;
				m_CameraMove = true;
			}
			else
			{
				m_MoveTime = 0.f;
				m_qCameraMove.pop();
				m_CameraMoveEnd = true;
			}
		}
		else
		{
			m_MoveTime = 0.f;
		}

		if (m_qCameraShake.size() != 0)
		{
			//??????
			if (m_ShakeTime < m_qCameraShake.front().Time)
			{
				int x = GetRandom(-(int)m_qCameraShake.front().Pos.x, (int)m_qCameraShake.front().Pos.x);
				int y = GetRandom(-(int)m_qCameraShake.front().Pos.y, (int)m_qCameraShake.front().Pos.y);
				Pos.x += (float)x;
				Pos.y += (float)y;
				m_ShakeTime += DeltaTime;
			}
			else
			{
				m_qCameraShake.pop();
			}
		}
		else
		{
			m_ShakeTime = 0.f;
		}
		m_CameraMoveEnd = false;

		Pos = Pos * -1.f;
		//?????? (Object???????? Z??????????????????
		Pos.z = 0.f;
		m_matView[3][i] = Axis.Dot(Pos);
	}
}

void CCamera::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CCamera::PrevRender(float DeltaTime)
{
	CSceneComponent::PrevRender(DeltaTime);

	

	/* ????
	1 0 0 0
	0 1 0 0
	0 0 1 0
	-x -y -z 1
	  ??????(????)
	Xx Yx Zx 0
	Xy Yy Zy 0
	Xz Yz Zz 0
	0  0  0  1
	  ????*????
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

	???? ?????? ???? ?????? ?????????????? ????.
	?????????? ?????????? ???????? ????.
	*/
}

void CCamera::Render(float DeltaTime)
{
	CSceneComponent::Render(DeltaTime);
}

CCamera* CCamera::Clone()
{
	return new CCamera(*this);
}
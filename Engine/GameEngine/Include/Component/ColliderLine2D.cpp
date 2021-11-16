
#include "ColliderLine2D.h"
#include "../Scene/Scene.h"
#include "../Collision.h"
#include "../Scene/SceneResource.h"
#include "ColliderCircle.h"
#include "ColliderPixel.h"
#include "ColliderBox2D.h"

CColliderLine2D::CColliderLine2D()
{
	m_ColliderShape = Collider_Shape::Box2D;
	m_ColliderSpace = Collider_Space::Collider2D;
	m_PrimitiveType = PrimitiveComponent_Type::Primitive2D;
	m_ComponentClassType = Component_Class_Type::ColliderBox2D;
	SetRender2DType(RT2D_Default);
}

CColliderLine2D::CColliderLine2D(const CColliderLine2D& com) :
	CCollider(com)
{
	m_Info = com.m_Info;
}

CColliderLine2D::~CColliderLine2D()
{
}

void CColliderLine2D::Start()
{
	CCollider::Start();
	SetWorldScale(m_Info.Length[0] * 2.f, m_Info.Length[1] * 2.f, 1.f);

	m_DebugMesh = m_pScene->GetResource()->FindMesh("ColliderBox2D");
}

bool CColliderLine2D::Init()
{
	if (!CCollider::Init())
		return false;

	m_Info.Axis[AXIS_X] = Vector2(1.f, 0.f);
	m_Info.Axis[AXIS_Y] = Vector2(0.f, 1.f);

	SetInheritRotZ(true);
	return true;
}

void CColliderLine2D::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);
}

void CColliderLine2D::PostUpdate(float DeltaTime)
{
	CCollider::PostUpdate(DeltaTime);

	//월드정점을 센터로 기준삼는다.
	m_Info.Center.x = GetWorldPos().x;
	m_Info.Center.y = GetWorldPos().y;

	//x축의 x,y y축의 x,y 가져온다.
	m_Info.Axis[AXIS_X].x = GetAxis(AXIS_X).x;
	m_Info.Axis[AXIS_X].y = GetAxis(AXIS_X).y;

	m_Info.Axis[AXIS_Y].x = GetAxis(AXIS_Y).x;
	m_Info.Axis[AXIS_Y].y = GetAxis(AXIS_Y).y;

	Vector2	Pos[4] = {};

	//일반 사각형을 기준으로
	//Axis_x, y 방향축에 길이를 곱해서 움직여준다. 그러면 꼭짓점으로 이동하게됨
	//이러한 작업으로 네개의 꼭짓점을 구해준다.
	Pos[0] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0] +
		m_Info.Axis[AXIS_Y] * m_Info.Length[1];
	Pos[1] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0] +
		m_Info.Axis[AXIS_Y] * m_Info.Length[1];

	Pos[2] = m_Info.Center - m_Info.Axis[AXIS_X] * m_Info.Length[0] -
		m_Info.Axis[AXIS_Y] * m_Info.Length[1];
	Pos[3] = m_Info.Center + m_Info.Axis[AXIS_X] * m_Info.Length[0] -
		m_Info.Axis[AXIS_Y] * m_Info.Length[1];

	m_Min.x = Pos[0].x;
	m_Min.y = Pos[0].y;

	m_Max.x = Pos[0].x;
	m_Max.y = Pos[0].y;

	//네개의 꼭짓점중에서 x,y가 작은것과 x,y가 큰것을 구한다. 렉트충돌처럼
	for (int i = 1; i < 4; ++i)
	{
		if (m_Min.x > Pos[i].x)
			m_Min.x = Pos[i].x;

		if (m_Min.y > Pos[i].y)
			m_Min.y = Pos[i].y;

		if (m_Max.x < Pos[i].x)
			m_Max.x = Pos[i].x;

		if (m_Max.y < Pos[i].y)
			m_Max.y = Pos[i].y;
	}
	m_Info.Min = m_Min;
	m_Info.Max = m_Max;
}

void CColliderLine2D::Collision(float DeltaTime)
{
	CCollider::Collision(DeltaTime);
}

void CColliderLine2D::PrevRender(float DeltaTime)
{
	CCollider::PrevRender(DeltaTime);
}

void CColliderLine2D::Render(float DeltaTime)
{
	CCollider::Render(DeltaTime);
}

CColliderLine2D* CColliderLine2D::Clone()
{
	return new CColliderLine2D(*this);
}

bool CColliderLine2D::Collision(CCollider* Dest)
{
	bool	result = false;

	switch (Dest->GetColliderShape())
	{
	case Collider_Shape::Box2D:
	{

		HitResult	DestResult = {};
		//result = CCollision::CollisionBox2DToBox2D(m_HitResult, DestResult,
		//	this, (CColliderBox2D*)Dest);
		Dest->SetHitResult(DestResult);
		break;
	}

	case Collider_Shape::Circle:
	{
		HitResult	DestResult = {};
		//result = CCollision::CollisionBox2DToCircle(m_HitResult, DestResult,
		//	this, (CColliderCircle*)Dest);
		Dest->SetHitResult(DestResult);
	}
	break;
	case Collider_Shape::Pixel:
	{
		HitResult	DestResult = {};
		//result = CCollision::CollisionBox2DToPixel(m_HitResult, DestResult,
		//	this, (CColliderPixel*)Dest);
		Dest->SetHitResult(DestResult);
	}
	break;
	}

	return result;
}

bool CColliderBox2D::CollisionMouse(const Vector2& MousePos)
{
	//HitResult	SrcResult = {};
	//HitResult	DestResult = {};
	//
	//m_MouseCollision = CCollision::CollisionLine2DToPoint(SrcResult, DestResult,
	//	m_Info, MousePos);
	//
	return 0;
}
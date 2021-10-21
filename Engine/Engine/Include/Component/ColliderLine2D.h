#pragma once
#include "Collider.h"
class CColliderLine2D :
	public CCollider
{
	friend class CGameObject;

protected:
	CColliderLine2D();
	CColliderLine2D(const CColliderLine2D& com);
	virtual ~CColliderLine2D();

protected:
	Line2DInfo	m_Info;

public:
	Line2DInfo GetInfo()	const
	{
		return m_Info;
	}

public:
	void SetExtent(float Width, float Height)
	{
		m_Info.Length[0] = Width;
		m_Info.Length[1] = Height;

		SetWorldScale(m_Info.Length[0] * 2.f, m_Info.Length[1] * 2.f, 1.f);
	}
	void SetLine(const Vector2& src, const Vector2& Dest)
	{
		float length=src.Distance(Dest);
		float angle=src.GetAngle(Dest);
		Vector2 vec = Dest - src;
		vec.Normalize(); 
		angle=DegreeToRadian(angle);

		SetRelativeRotationZ(angle);
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CColliderLine2D* Clone();
public:
	virtual bool Collision(CCollider* Dest);
	virtual bool CollisionMouse(const Vector2& MousePos);
};

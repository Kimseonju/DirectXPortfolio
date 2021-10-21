#pragma once

#include "../GameEngine.h"

//충돌처리는 공간분할기법을 사용하는데 그 공간을 정의한 클래스
class CCollisionSection
{
	friend class CSceneCollision;

private:
	CCollisionSection();
	~CCollisionSection();

private:
	std::vector<class CCollider*>	m_vecCollider;
	//세션 하나 크기
	Vector3			m_SectionSize;
	//세션 전체 크기
	Vector3			m_SectionTotalSize;
	Vector3			m_Min;
	Vector3			m_Max;
	int				m_IndexX;
	int				m_IndexY;
	int				m_IndexZ;
	int				m_Index;

public:
	bool Init(int IndexX, int IndexY, int IndexZ, int Index,
		const Vector3& SectionSize, const Vector3& SectionTotalSize);
	void SetSectionMin(const Vector3& Min);
	void SetSectionMax(const Vector3& Max);
	void AddCollider(class CCollider* Collider);
	void Clear();
	void Collision(float DeltaTime);
	class CCollider* CollisionMouse(bool Is2D, float DeltaTime);

private:
	static int SortY(const void* Src, const void* Dest);
	static int SortZ(const void* Src, const void* Dest);
};
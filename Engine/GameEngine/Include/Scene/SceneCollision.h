#pragma once

#include "../GameEngine.h"
#include "../Component/Collider.h"
#include "../UI/Widget.h"
//충돌 처리를 공간을 나눠서 처리하는것
struct CollisionSectionInfo
{
	
	std::vector<class CCollisionSection*>	vecSection;
	Vector3	SectionSize;
	Vector3	Center;
	Vector3	SectionTotalSize;
	Vector3	Min;
	Vector3	Max;
	int		CountX;
	int		CountY;
	int		CountZ;

	CollisionSectionInfo() :
		CountX(1),
		CountY(1),
		CountZ(1)
	{
	}
};

//씬콜리전 관리
class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_pScene;

	//충돌체 리스트
	std::list<CSharedPtr<CCollider>>	m_ColliderList;

	//충돌세션 정보
	CollisionSectionInfo* m_Section2D;
	CollisionSectionInfo* m_Section3D;
	Vector3		m_Center;
	Vector3		m_SectionTotalSize;
	Vector3		m_SectionSize;
	bool		m_Move;
	std::vector<CSharedPtr<CWidget>>	m_vecWidget;
	CSharedPtr<CCollider>	m_MouseCollisionCollider;
	CSharedPtr<CWidget>		m_MouseCollisionWidget;

public:
	void AddCollider(class CCollider* Collider);
	void AddWidget(CWidget* Widget);

	//움직였다면 호출
	void SetCenter(const Vector3& Center)
	{
		if (m_Center != Center)
		{
			m_Move = true;
			m_Center = Center;
		}

		if (m_Section2D)
			m_Section2D->Center = Center;

		else if (m_Section3D)
			m_Section3D->Center = Center;
	}

private:
	//충돌체위치에따라 충돌체세션에 넣어준다.
	void CheckCollisionSection();
	void CreateSection2D();
	void CreateSection3D();
	//세션정보 전체 다시계산하기 (센터이동시)
	void CalculateSectionInfo();

public:
	void Start();
	bool Init();
	void Collision(float DeltaTime);

private:
	void CollisionMouse(float DeltaTime);

	// UI 및 World 물체 정렬함수.
private:
	static int SortZOrder(CSharedPtr<CWidget> Src, CSharedPtr<CWidget> Dest);
};

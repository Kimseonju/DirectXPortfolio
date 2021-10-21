#pragma once

#include "../GameEngine.h"
#include "../Component/Collider.h"
#include "../UI/Widget.h"
//�浹 ó���� ������ ������ ó���ϴ°�
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

//���ݸ��� ����
class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	class CScene* m_pScene;

	//�浹ü ����Ʈ
	std::list<CSharedPtr<CCollider>>	m_ColliderList;

	//�浹���� ����
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

	//�������ٸ� ȣ��
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
	//�浹ü��ġ������ �浹ü���ǿ� �־��ش�.
	void CheckCollisionSection();
	void CreateSection2D();
	void CreateSection3D();
	//�������� ��ü �ٽð���ϱ� (�����̵���)
	void CalculateSectionInfo();

public:
	void Start();
	bool Init();
	void Collision(float DeltaTime);

private:
	void CollisionMouse(float DeltaTime);

	// UI �� World ��ü �����Լ�.
private:
	static int SortZOrder(CSharedPtr<CWidget> Src, CSharedPtr<CWidget> Dest);
};

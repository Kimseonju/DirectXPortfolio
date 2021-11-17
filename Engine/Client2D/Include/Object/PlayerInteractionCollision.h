#pragma once

#include "GameObject.h"
#include "Component/ColliderBox2D.h"
class CPlayerInteractionCollision :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayerInteractionCollision();
	CPlayerInteractionCollision(const CPlayerInteractionCollision& obj);
	virtual ~CPlayerInteractionCollision();

protected:
	CSharedPtr<CColliderBox2D> m_Collider2D;
	float m_LifeCount;
protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerInteractionCollision* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
};



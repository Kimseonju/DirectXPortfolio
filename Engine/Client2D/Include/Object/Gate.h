#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
class CGate :
	public CGameObject
{
	friend class CScene;

protected:
	CGate();
	CGate(const CGate& obj);
	virtual ~CGate();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CAnimation2D> m_Animation2D;
	CSharedPtr<CColliderBox2D> m_ColliderBox2D;
	CSharedPtr<CGameObject> m_SpawnObject;
	class CKeyboardUIObject* m_KeyUIObject;
	bool m_Spawn;
	Vector2 m_NextGateStagePos;
protected:
public:
public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CGate* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);
	void CollisionEnd(const HitResult& result, CCollider* Collider);
public:
	virtual void Animation2DNotify(const std::string& Name);
	void StageGateMove(Vector2 Pos);
	void StageGateEnd();
};

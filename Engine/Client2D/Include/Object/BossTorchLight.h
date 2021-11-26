#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
class CBossTorchLight :
	public CGameObject
{
	friend class CScene;

protected:
	CBossTorchLight();
	CBossTorchLight(const CBossTorchLight& obj);
	virtual ~CBossTorchLight();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CSpriteComponent> m_SpriteBlend;
	CSharedPtr<CAnimation2D> m_Animation2D;
protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBossTorchLight* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);

};

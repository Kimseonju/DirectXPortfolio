#pragma once

#include "../GlobalValue.h"
#include "GameObject.h"

#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
class CTorchLight :
	public CGameObject
{
	friend class CScene;

protected:
	CTorchLight();
	CTorchLight(const CTorchLight& obj);
	virtual ~CTorchLight();

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
	virtual CTorchLight* Clone();
	void CollisionBegin(const HitResult& result, CCollider* Collider);

};

#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderBox2D.h"
#include "../Animation2D/Animation2D_FSM.h"
class CEffectObject :
	public CGameObject
{
	friend class CScene;

protected:
	CEffectObject();
	CEffectObject(const CEffectObject& obj);
	virtual ~CEffectObject();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CColliderBox2D> m_Collider2D;
	CSharedPtr<CAnimation2D_FSM> m_Animation2D;

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEffectObject* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	virtual void AnimationFrameEnd(const std::string& Name);
};



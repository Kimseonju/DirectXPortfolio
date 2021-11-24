#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
class CSpawnEffect :
	public CGameObject
{
	friend class CScene;

protected:
	CSpawnEffect();
	CSpawnEffect(const CSpawnEffect& obj);
	virtual ~CSpawnEffect();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CAnimation2D* m_Animation2D;
	CSharedPtr<CGameObject> m_Obj;
	
public:
	virtual void Enable(bool bEnable);
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSpawnEffect* Clone();
public:
	void Spawn();
	virtual void AnimationFrameEnd(const std::string& Name);
	virtual void Animation2DNotify(const std::string& Name);
};

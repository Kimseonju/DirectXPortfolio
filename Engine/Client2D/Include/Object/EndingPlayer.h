#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
class CEndingPlayer :
	public CGameObject
{
	friend class CScene;

protected:
	CEndingPlayer();
	CEndingPlayer(const CEndingPlayer& obj);
	virtual ~CEndingPlayer();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	CAnimation2D* m_Animation2D;
protected:
public:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CEndingPlayer* Clone();
};

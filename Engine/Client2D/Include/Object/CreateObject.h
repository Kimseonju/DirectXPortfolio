#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
class CCreateObject :
	public CGameObject
{
	friend class CScene;

protected:
	CCreateObject();
	CCreateObject(const CCreateObject& obj);
	virtual ~CCreateObject();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_Animation2D;

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCreateObject* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	bool GetFrameEnd();
	bool SpawnStart();


};

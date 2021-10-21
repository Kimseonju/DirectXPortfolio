#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderPixel.h"

class CBackGround :
	public CGameObject
{
	friend class CScene;

protected:
	CBackGround();
	CBackGround(const CBackGround& obj);
	virtual ~CBackGround();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
public:
	//Material 첫번째 Add해주는 함수
	void AddTexture(const std::string& Name, const TCHAR* FileName);

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBackGround* Clone();
};


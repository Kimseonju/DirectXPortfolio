#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderPixel.h"

class CBackGround_Tree :
	public CGameObject
{
	friend class CScene;

protected:
	CBackGround_Tree();
	CBackGround_Tree(const CBackGround_Tree& obj);
	virtual ~CBackGround_Tree();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	Vector2 m_Pos;
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
	virtual CBackGround_Tree* Clone();
};


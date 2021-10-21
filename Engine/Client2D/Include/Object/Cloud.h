#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "Component/ColliderPixel.h"

class CCloud :
	public CGameObject
{
	friend class CScene;

protected:
	CCloud();
	CCloud(const CCloud& obj);
	virtual ~CCloud();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	float m_Speed;

public:
	class CSpriteComponent* GetSprite();

	void SetSpeed(float Speed)
	{
		m_Speed = Speed;
	}

	//Material 첫번째 Add해주는 함수
	void AddTexture(const std::string& Name, const TCHAR* FileName);
		
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCloud* Clone();
};


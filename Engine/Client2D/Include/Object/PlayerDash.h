#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "../GlobalValue.h"
//시간이지날수록 알파블렌딩으로 천천히사라지도록 만들기
class CPlayerDash :
	public CGameObject
{
	friend class CScene;

protected:
	CPlayerDash();
	CPlayerDash(const CPlayerDash& obj);
	virtual ~CPlayerDash();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_Animation2D;

	Object_Dir m_Dir;
public:
	void SetDir(Object_Dir Dir)
	{
		m_Dir = Dir;
	}
protected:
	bool    m_Fire;
	float   m_FireTime;
	float   m_FireTimeMax;
	bool    m_OneAttack;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerDash* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void Fire(float DeltaTime);

};

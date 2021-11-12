#pragma once

#include "GameObject.h"
#include "Component/SpriteComponent.h"
#include "../GlobalValue.h"
class CWeaponArm :
	public CGameObject
{
	friend class CScene;

protected:
	CWeaponArm();
	CWeaponArm(const CWeaponArm& obj);
	virtual ~CWeaponArm();

protected:
	CSharedPtr<CSpriteComponent> m_Sprite;
	class CAnimation2D* m_Animation2D;

	Object_Dir m_Dir;
public:
	void SetDir(Object_Dir Dir)
	{
		m_Dir = Dir;
		if (m_Dir == Object_Dir::Left)
		{
			m_Sprite->SetRelativePos(-20.f, 0.f, 0.f);
		}
		else if (m_Dir == Object_Dir::Right)
		{
			m_Sprite->SetRelativePos(20.f, 0.f, 0.f);
		}
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CWeaponArm* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void Fire(float DeltaTime);

};

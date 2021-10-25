#pragma once
#include "GameObject.h"
#include "Component/SpriteComponent.h"
class CBelialWeaponCharge :
	public CGameObject
{
	friend class CScene;

protected:
	CBelialWeaponCharge();
	CBelialWeaponCharge(const CBelialWeaponCharge& obj);
	virtual ~CBelialWeaponCharge();
private:

	CSharedPtr<CSpriteComponent> m_Sprite;
	CSharedPtr<CAnimation2D> m_Animation2D;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialWeaponCharge* Clone();
};


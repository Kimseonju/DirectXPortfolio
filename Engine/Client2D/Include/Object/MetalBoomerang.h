#pragma once
#include "Weapon.h"
#include "Component/SpriteComponent.h"
class CMetalBoomerang :
	public CWeapon
{
	friend class CScene;

protected:
	CMetalBoomerang();
	CMetalBoomerang(const CMetalBoomerang& obj);
	virtual ~CMetalBoomerang();


protected:
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMetalBoomerang* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	virtual bool Attack(float Angle);
	virtual void Dash(CPlayer* player);
	virtual void Reload(CPlayer* player);
	// 피격
	virtual void GetHit();
	// 아이템 장착
	virtual void Equip();

};


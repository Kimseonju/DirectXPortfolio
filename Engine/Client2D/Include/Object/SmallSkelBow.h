#pragma once

#include "Weapon.h"
#include "Component/SpriteComponent.h"

/*

무기공격시 90도 움직이면서 공격한다.
한번 공격할때 90도 플러스 마이너스 해주면 됨 Arm에서만
즉 바라보는방향 45도+-
무기위치는 캐릭터위치에서 조금 앞,뒤로
*/
class CSmallSkelBow :
	public CWeapon
{
	friend class CScene;

protected:
	CSmallSkelBow();
	CSmallSkelBow(const CSmallSkelBow& obj);
	virtual ~CSmallSkelBow();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSmallSkelBow* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	virtual bool Attack(float Angle);
	virtual void Dash(CPlayer* player);
	virtual void Reload(CPlayer* player);
	// 피격
	virtual void GetHit();
	// 아이템 장착
	virtual void Equip();
public:
	void AnimationFrameEnd(const std::string& Name);
};

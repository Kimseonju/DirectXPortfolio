#pragma once

#include "Weapon.h"
#include "Component/SpriteComponent.h"

/*

//���ݽ� ���� ���� ����ȸ���ߴٰ� ������� ���ƿ´�.
*/
class CRevolver :
	public CWeapon
{
	friend class CScene;

protected:
	CRevolver();
	CRevolver(const CRevolver& obj);
	virtual ~CRevolver();


protected:
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CRevolver* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	virtual bool Attack(float Angle);
	virtual void Dash(CPlayer* player);
	virtual void Reload(CPlayer* player);
	// �ǰ�
	virtual void GetHit();
	// ������ ����
	virtual void Equip();

};

#pragma once

#include "Weapon.h"
#include "Component/SpriteComponent.h"

/*

������ݽ� 90�� �����̸鼭 �����Ѵ�.
�ѹ� �����Ҷ� 90�� �÷��� ���̳ʽ� ���ָ� �� Arm������
�� �ٶ󺸴¹��� 45��+-
������ġ�� ĳ������ġ���� ���� ��,�ڷ�
*/
class CSkelSmallDagger :
	public CWeapon
{
	friend class CScene;

protected:
	CSkelSmallDagger();
	CSkelSmallDagger(const CSkelSmallDagger& obj);
	virtual ~CSkelSmallDagger();

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CSkelSmallDagger* Clone();
	virtual void Animation2DNotify(const std::string& Name);

	virtual bool Attack(float Angle);
	virtual void Dash(CPlayer* player);
	virtual void Reload(CPlayer* player);
	// �ǰ�
	virtual void GetHit();
	// ������ ����
	virtual void Equip();
public:
	void AnimationFrameEnd(const std::string& Name);
};

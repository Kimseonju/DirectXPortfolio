#pragma once
#include <GameObject.h>
#include "Component/SpriteComponent.h"
#include "Component/SpringArm2D.h"
#include "Component/ColliderBox2D.h"
#include <Component/RigidBodyComponent.h>
#include "Component/WidgetComponent.h"
class CBelialHand :
	public CGameObject
{
	friend class CScene;

protected:
	CBelialHand();
	CBelialHand(const CBelialHand& obj);
	virtual ~CBelialHand();
private:

	CSharedPtr<CSpriteComponent> m_Sprite;
	bool m_Attacking;
	class CBelial* m_Belial;
	bool m_AttackMove;
	class CAnimation2D* m_Animation2D;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialHand* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	bool GetHorizontalReverse2DEnable();
	void SetBelial(class CBelial* Belial);
	bool Attack();
	void SetOpaacity(float Opacity);
	void SetHorizontalReverse2DEnable(bool Enable);
	CMaterial* GetMaterial(int Index=0);
	void StopAnimation();

public:
	virtual void AnimationFrameEnd(const std::string& Name);
};


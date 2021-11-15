#pragma once
#include "EffectObject.h"
class CBelialBulletEffect :
	public CEffectObject
{
	friend class CScene;

protected:
	CBelialBulletEffect();
	CBelialBulletEffect(const CBelialBulletEffect& obj);
	virtual ~CBelialBulletEffect();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialBulletEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimationFrameEnd(const std::string& Name);
};
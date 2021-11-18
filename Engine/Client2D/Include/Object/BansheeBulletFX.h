#pragma once
#include "EffectObject.h"
class CBansheeBulletFX :
	public CEffectObject
{
	friend class CScene;

protected:
	CBansheeBulletFX();
	CBansheeBulletFX(const CBansheeBulletFX& obj);
	virtual ~CBansheeBulletFX();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBansheeBulletFX* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimationFrameEnd(const std::string& Name);
};
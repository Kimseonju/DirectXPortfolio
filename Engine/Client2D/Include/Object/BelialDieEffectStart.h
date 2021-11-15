#pragma once
#include "EffectObject.h"
class CBelialDieEffectStart :
	public CEffectObject
{
	friend class CScene;

protected:
	CBelialDieEffectStart();
	CBelialDieEffectStart(const CBelialDieEffectStart& obj);
	virtual ~CBelialDieEffectStart();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBelialDieEffectStart* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimationFrameEnd(const std::string& Name);
};
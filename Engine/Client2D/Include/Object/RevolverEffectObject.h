#pragma once
#include "EffectObject.h"
class CRevolverEffectObject :
    public CEffectObject
{
	friend class CScene;

protected:
	CRevolverEffectObject();
	CRevolverEffectObject(const CRevolverEffectObject& obj);
	virtual ~CRevolverEffectObject();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CRevolverEffectObject* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimationFrameEnd(const std::string& Name);
};
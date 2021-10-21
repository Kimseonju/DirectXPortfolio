#pragma once
#include "EffectObject.h"
class CMetalBoomerangEffectObject :
	public CEffectObject
{
	friend class CScene;

protected:
	CMetalBoomerangEffectObject();
	CMetalBoomerangEffectObject(const CMetalBoomerangEffectObject& obj);
	virtual ~CMetalBoomerangEffectObject();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMetalBoomerangEffectObject* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void AnimationFrameEnd(const std::string& Name);
};
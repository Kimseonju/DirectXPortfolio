#pragma once
#include "EffectObject.h"
class CObjectDieEffectObject :
	public CEffectObject
{
	friend class CScene;

protected:
	CObjectDieEffectObject();
	CObjectDieEffectObject(const CObjectDieEffectObject& obj);
	virtual ~CObjectDieEffectObject();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CObjectDieEffectObject* Clone();
	virtual void Animation2DNotify(const std::string& Name);

};
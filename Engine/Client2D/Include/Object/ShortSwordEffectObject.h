#pragma once
#include "EffectObject.h"
class CShortSwordEffectObject :
    public CEffectObject
{
	friend class CScene;

protected:
	CShortSwordEffectObject();
	CShortSwordEffectObject(const CShortSwordEffectObject& obj);
	virtual ~CShortSwordEffectObject();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CShortSwordEffectObject* Clone();

};


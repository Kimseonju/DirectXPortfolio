#pragma once
#include "EffectObject.h"
class CTaanaShieldEffect :
	public CEffectObject
{
	friend class CScene;

protected:
	CTaanaShieldEffect();
	CTaanaShieldEffect(const CTaanaShieldEffect& obj);
	virtual ~CTaanaShieldEffect();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PrevRender(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CTaanaShieldEffect* Clone();

};


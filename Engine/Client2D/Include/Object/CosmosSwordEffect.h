#pragma once
#include "EffectObject.h"
class CCosmosSwordEffect :
	public CEffectObject
{
	friend class CScene;

protected:
	CCosmosSwordEffect();
	CCosmosSwordEffect(const CCosmosSwordEffect& obj);
	virtual ~CCosmosSwordEffect();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCosmosSwordEffect* Clone();

};


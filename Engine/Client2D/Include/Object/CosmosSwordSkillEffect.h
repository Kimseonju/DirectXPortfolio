#pragma once
#include "EffectObject.h"
class CCosmosSwordSkillEffect :
	public CEffectObject
{
	friend class CScene;

protected:
	CCosmosSwordSkillEffect();
	CCosmosSwordSkillEffect(const CCosmosSwordSkillEffect& obj);
	virtual ~CCosmosSwordSkillEffect();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CCosmosSwordSkillEffect* Clone();

};


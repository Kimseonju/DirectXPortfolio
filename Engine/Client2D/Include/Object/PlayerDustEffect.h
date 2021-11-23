#pragma once
#include "EffectObject.h"
class CPlayerDustEffect :
	public CEffectObject
{
	friend class CScene;

protected:
	CPlayerDustEffect();
	CPlayerDustEffect(const CPlayerDustEffect& obj);
	virtual ~CPlayerDustEffect();

protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CPlayerDustEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);
	void SetHorizontalReverse2DEnable(bool Enable);

};
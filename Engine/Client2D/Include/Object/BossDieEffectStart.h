#pragma once
#include "EffectObject.h"
class CBossDieEffectStart :
	public CEffectObject
{
	friend class CScene;

protected:
	CBossDieEffectStart();
	CBossDieEffectStart(const CBossDieEffectStart& obj);
	virtual ~CBossDieEffectStart();

protected:
	class CBelial* m_Belial;

public:
	void SetBelial(class CBelial* Belial)
	{
		m_Belial = Belial;
	}
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBossDieEffectStart* Clone();
	virtual void Animation2DNotify(const std::string& Name);
public:
	void AnimationFrameEnd(const std::string& Name);
};
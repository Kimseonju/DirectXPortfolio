#pragma once
#include "EffectObject.h"
class CBossDieEffect :
	public CEffectObject
{
	friend class CScene;

protected:
	CBossDieEffect();
	CBossDieEffect(const CBossDieEffect& obj);
	virtual ~CBossDieEffect();

protected:
	int m_SpawnCount;
	int m_SpawnCountMax;
	class CBelial* m_Belial;
public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CBossDieEffect* Clone();
	virtual void Animation2DNotify(const std::string& Name);

public:
	void SetBelial(class CBelial* Belial)
	{
		m_Belial = Belial;
	}
	void SetSpawnCount(int Count)
	{
		m_SpawnCount = Count;
	}
public:
	void AnimationFrameEnd(const std::string& Name);
};
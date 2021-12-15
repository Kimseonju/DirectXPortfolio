#pragma once

#include "Weapon.h"
#include "Component/SpriteComponent.h"


class CDaisyRing :
	public CItem
{
	friend class CScene;

protected:
	CDaisyRing();
	CDaisyRing(const CDaisyRing& obj);
	virtual ~CDaisyRing();


protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CDaisyRing* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};

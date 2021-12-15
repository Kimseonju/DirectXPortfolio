#pragma once

#include "Weapon.h"
#include "Component/SpriteComponent.h"


class CMiniEarth :
	public CItem
{
	friend class CScene;

protected:
	CMiniEarth();
	CMiniEarth(const CMiniEarth& obj);
	virtual ~CMiniEarth();


protected:

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(float DeltaTime);
	virtual CMiniEarth* Clone();
	virtual void Animation2DNotify(const std::string& Name);
};
